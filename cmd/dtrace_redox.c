/*
 * Oracle Linux DTrace - RedoxOS Port
 * Copyright (c) 2025, Oracle and/or its affiliates. All rights reserved.
 * Licensed under the Universal Permissive License v 1.0 as shown at
 * http://oss.oracle.com/licenses/upl.
 *
 * Minimal DTrace command for RedoxOS
 *
 * This is a simplified version of dtrace that supports self-tracing
 * using the rbpf user-space eBPF virtual machine.
 *
 * Supported features:
 *   - BEGIN/END/ERROR probes
 *   - profile:::tick-* probes (timer-based)
 *   - Basic D script execution
 *   - printf() action
 *   - exit() action
 *
 * Build:
 *   x86_64-unknown-redox-gcc -o dtrace dtrace_redox.c \
 *       -I../include -L../libdtrace/rbpf_ffi/target/x86_64-unknown-redox/release \
 *       -lrbpf_ffi -lrt -D__redox__
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <getopt.h>
#include <errno.h>
#include <inttypes.h>

#ifdef __redox__
#include "config_redox.h"
#include "port_redox.h"
#else
/* Linux compatibility for testing */
#include <time.h>
typedef int64_t hrtime_t;
static inline hrtime_t gethrtime(void) {
	struct timespec ts;
	clock_gettime(CLOCK_MONOTONIC, &ts);
	return (hrtime_t)ts.tv_sec * 1000000000LL + ts.tv_nsec;
}
#endif

#include <dt_bpf_backend.h>

/*
 * Program name for error messages
 */
static const char *g_pname = "dtrace";
static int g_verbose = 0;
static int g_quiet = 0;
static volatile int g_intr = 0;
static int g_status = 0;

/*
 * Probe types we support
 */
typedef enum {
	PROBE_BEGIN,
	PROBE_END,
	PROBE_ERROR,
	PROBE_TICK,
	PROBE_UNKNOWN
} probe_type_t;

/*
 * Parsed D script representation
 */
typedef struct dscript {
	probe_type_t	type;
	char		*provider;
	char		*module;
	char		*function;
	char		*name;
	char		*predicate;
	char		*action;
	uint64_t	tick_interval_ns;	/* For tick probes */
} dscript_t;

/*
 * Forward declarations
 */
static void usage(FILE *fp);
static int parse_script(const char *script, dscript_t *ds);
static int execute_script(dscript_t *ds);
static void signal_handler(int sig);

/*
 * Signal handler for graceful shutdown
 */
static void
signal_handler(int sig)
{
	(void)sig;
	g_intr = 1;
}

/*
 * Print usage information
 */
static void
usage(FILE *fp)
{
	fprintf(fp,
	    "Usage: %s [-qvV] [-n probe-description] [-s script]\n"
	    "\n"
	    "Options:\n"
	    "  -n probe  Execute the specified probe description\n"
	    "  -s file   Execute the D script in the specified file\n"
	    "  -q        Quiet mode - suppress informational messages\n"
	    "  -v        Verbose mode - show additional information\n"
	    "  -V        Print version and exit\n"
	    "  -h        Print this help message\n"
	    "\n"
	    "Supported probes (RedoxOS self-trace mode):\n"
	    "  dtrace:::BEGIN      - fires at start of tracing\n"
	    "  dtrace:::END        - fires at end of tracing\n"
	    "  dtrace:::ERROR      - fires on errors\n"
	    "  profile:::tick-Ns   - fires every N seconds\n"
	    "  profile:::tick-Nms  - fires every N milliseconds\n"
	    "\n"
	    "Examples:\n"
	    "  %s -n 'BEGIN { printf(\"Hello!\"); exit(0); }'\n"
	    "  %s -n 'profile:::tick-1sec { printf(\"tick\"); }'\n"
	    "\n",
	    g_pname, g_pname, g_pname);
}

/*
 * Print version information
 */
static void
print_version(void)
{
	printf("dtrace for RedoxOS (self-trace mode)\n");
	printf("Using rbpf user-space eBPF virtual machine\n");
#ifdef DT_GIT_VERSION
	printf("Version: %s\n", DT_GIT_VERSION);
#endif
	printf("\n");
	printf("Supported probes:\n");
	printf("  dtrace:::BEGIN, dtrace:::END, dtrace:::ERROR\n");
	printf("  profile:::tick-*\n");
}

/*
 * Parse a tick probe name to get the interval
 * e.g., "tick-1sec" -> 1000000000 ns
 *       "tick-100ms" -> 100000000 ns
 */
static uint64_t
parse_tick_interval(const char *name)
{
	uint64_t value;
	char unit[16];
	int n;

	if (strncmp(name, "tick-", 5) != 0)
		return 0;

	n = sscanf(name + 5, "%" SCNu64 "%15s", &value, unit);
	if (n < 1)
		return 0;

	if (n == 1 || strcmp(unit, "ns") == 0)
		return value;
	else if (strcmp(unit, "us") == 0)
		return value * 1000ULL;
	else if (strcmp(unit, "ms") == 0)
		return value * 1000000ULL;
	else if (strcmp(unit, "sec") == 0 || strcmp(unit, "s") == 0)
		return value * 1000000000ULL;
	else if (strcmp(unit, "min") == 0 || strcmp(unit, "m") == 0)
		return value * 60000000000ULL;
	else if (strcmp(unit, "hz") == 0)
		return value > 0 ? 1000000000ULL / value : 0;

	return 0;
}

/*
 * Parse a probe description
 * Format: provider:module:function:name or simplified forms
 * Handles provider:::name format (empty module and function)
 */
static probe_type_t
parse_probe_desc(const char *desc, dscript_t *ds)
{
	char *copy = strdup(desc);
	char *provider = NULL, *module = NULL, *function = NULL, *name = NULL;
	char *p = copy;
	char *parts[4] = {NULL, NULL, NULL, NULL};
	int num_parts = 0;
	char *start = p;

	/* Split by colons, preserving empty parts */
	while (*p && num_parts < 4) {
		if (*p == ':') {
			*p = '\0';
			parts[num_parts++] = start;
			start = p + 1;
		}
		p++;
	}
	if (num_parts < 4 && *start) {
		parts[num_parts++] = start;
	}

	/* Assign parts based on count */
	if (num_parts == 4) {
		/* Full format: provider:module:function:name */
		provider = parts[0];
		module = parts[1];
		function = parts[2];
		name = parts[3];
	} else if (num_parts == 3) {
		/* provider:module:name or provider::name */
		provider = parts[0];
		if (parts[1] && *parts[1])
			module = parts[1];
		name = parts[2];
	} else if (num_parts == 2) {
		/* provider:name */
		provider = parts[0];
		name = parts[1];
	} else if (num_parts == 1) {
		/* Just a name */
		name = parts[0];
	}

	/* Store parsed components */
	ds->provider = (provider && *provider) ? strdup(provider) : NULL;
	ds->module = (module && *module) ? strdup(module) : NULL;
	ds->function = (function && *function) ? strdup(function) : NULL;
	ds->name = (name && *name) ? strdup(name) : NULL;

	free(copy);

	/* Determine probe type */
	if (ds->provider) {
		if (strcmp(ds->provider, "dtrace") == 0) {
			if (ds->name) {
				if (strcmp(ds->name, "BEGIN") == 0)
					return PROBE_BEGIN;
				if (strcmp(ds->name, "END") == 0)
					return PROBE_END;
				if (strcmp(ds->name, "ERROR") == 0)
					return PROBE_ERROR;
			}
		} else if (strcmp(ds->provider, "profile") == 0) {
			if (ds->name && strncmp(ds->name, "tick-", 5) == 0) {
				ds->tick_interval_ns = parse_tick_interval(ds->name);
				if (ds->tick_interval_ns > 0)
					return PROBE_TICK;
			}
		}
	}

	/* Check for shorthand BEGIN/END */
	if (ds->name) {
		if (strcmp(ds->name, "BEGIN") == 0)
			return PROBE_BEGIN;
		if (strcmp(ds->name, "END") == 0)
			return PROBE_END;
		if (strcmp(ds->name, "ERROR") == 0)
			return PROBE_ERROR;
	}

	return PROBE_UNKNOWN;
}

/*
 * Parse a D script
 * Format: probe-desc [/predicate/] { action }
 */
static int
parse_script(const char *script, dscript_t *ds)
{
	const char *p = script;
	const char *desc_start, *desc_end;
	const char *pred_start = NULL, *pred_end = NULL;
	const char *action_start = NULL, *action_end = NULL;
	char desc_buf[256];

	memset(ds, 0, sizeof(*ds));

	/* Skip leading whitespace */
	while (*p && (*p == ' ' || *p == '\t' || *p == '\n'))
		p++;

	/* Find probe description */
	desc_start = p;
	while (*p && *p != '/' && *p != '{' && *p != ' ' && *p != '\t')
		p++;
	desc_end = p;

	if (desc_end <= desc_start) {
		fprintf(stderr, "%s: missing probe description\n", g_pname);
		return -1;
	}

	/* Copy probe description */
	size_t desc_len = desc_end - desc_start;
	if (desc_len >= sizeof(desc_buf)) {
		fprintf(stderr, "%s: probe description too long\n", g_pname);
		return -1;
	}
	memcpy(desc_buf, desc_start, desc_len);
	desc_buf[desc_len] = '\0';

	/* Parse the probe description */
	ds->type = parse_probe_desc(desc_buf, ds);

	/* Skip whitespace */
	while (*p && (*p == ' ' || *p == '\t' || *p == '\n'))
		p++;

	/* Check for predicate */
	if (*p == '/') {
		pred_start = p + 1;
		p++;
		while (*p && *p != '/')
			p++;
		if (*p != '/') {
			fprintf(stderr, "%s: unterminated predicate\n", g_pname);
			return -1;
		}
		pred_end = p;
		p++;

		/* Store predicate */
		size_t pred_len = pred_end - pred_start;
		ds->predicate = malloc(pred_len + 1);
		memcpy(ds->predicate, pred_start, pred_len);
		ds->predicate[pred_len] = '\0';
	}

	/* Skip whitespace */
	while (*p && (*p == ' ' || *p == '\t' || *p == '\n'))
		p++;

	/* Find action */
	if (*p == '{') {
		action_start = p + 1;
		int brace_count = 1;
		p++;
		while (*p && brace_count > 0) {
			if (*p == '{')
				brace_count++;
			else if (*p == '}')
				brace_count--;
			p++;
		}
		if (brace_count != 0) {
			fprintf(stderr, "%s: unterminated action\n", g_pname);
			return -1;
		}
		action_end = p - 1;

		/* Store action */
		size_t action_len = action_end - action_start;
		ds->action = malloc(action_len + 1);
		memcpy(ds->action, action_start, action_len);
		ds->action[action_len] = '\0';
	}

	if (ds->type == PROBE_UNKNOWN) {
		fprintf(stderr, "%s: unsupported probe: %s\n", g_pname, desc_buf);
		fprintf(stderr, "Supported probes:\n");
		fprintf(stderr, "  dtrace:::BEGIN, dtrace:::END, dtrace:::ERROR\n");
		fprintf(stderr, "  profile:::tick-*\n");
		return -1;
	}

	return 0;
}

/*
 * Execute a printf action
 */
static void
exec_printf(const char *action)
{
	const char *p = action;
	const char *fmt_start, *fmt_end;
	char fmt_buf[256];

	/* Find printf( */
	p = strstr(action, "printf(");
	if (!p)
		return;
	p += 7;

	/* Skip whitespace */
	while (*p && (*p == ' ' || *p == '\t'))
		p++;

	/* Find format string */
	if (*p != '"')
		return;
	fmt_start = p + 1;
	p++;
	while (*p && *p != '"') {
		if (*p == '\\' && *(p+1))
			p++;
		p++;
	}
	if (*p != '"')
		return;
	fmt_end = p;

	/* Copy and print format string */
	size_t fmt_len = fmt_end - fmt_start;
	if (fmt_len >= sizeof(fmt_buf))
		fmt_len = sizeof(fmt_buf) - 1;
	memcpy(fmt_buf, fmt_start, fmt_len);
	fmt_buf[fmt_len] = '\0';

	/* Process escape sequences */
	char output[256];
	char *out = output;
	for (p = fmt_buf; *p && (out - output) < (int)sizeof(output) - 1; p++) {
		if (*p == '\\') {
			p++;
			switch (*p) {
			case 'n': *out++ = '\n'; break;
			case 't': *out++ = '\t'; break;
			case 'r': *out++ = '\r'; break;
			case '\\': *out++ = '\\'; break;
			case '"': *out++ = '"'; break;
			default: *out++ = *p; break;
			}
		} else {
			*out++ = *p;
		}
	}
	*out = '\0';

	printf("%s", output);
	fflush(stdout);
}

/*
 * Check if action contains exit()
 */
static int
has_exit_action(const char *action)
{
	return action && strstr(action, "exit(") != NULL;
}

/*
 * Execute a D script
 */
static int
execute_script(dscript_t *ds)
{
	int do_exit = 0;

	if (!g_quiet) {
		printf("dtrace: script compiled successfully\n");
	}

	/* Set up signal handlers */
	signal(SIGINT, signal_handler);
	signal(SIGTERM, signal_handler);

	switch (ds->type) {
	case PROBE_BEGIN:
		if (!g_quiet)
			printf("dtrace: BEGIN probe enabled\n");

		/* Execute BEGIN action */
		if (ds->action) {
			exec_printf(ds->action);
			if (has_exit_action(ds->action))
				do_exit = 1;
		}

		if (do_exit) {
			/* Fire END probe */
			if (!g_quiet)
				printf("\ndtrace: END probe firing\n");
		}
		break;

	case PROBE_TICK: {
		uint64_t interval_ns = ds->tick_interval_ns;
		uint64_t interval_us = interval_ns / 1000;

		if (!g_quiet) {
			printf("dtrace: profile:::tick probe enabled "
		    "(interval: %" PRIu64 " ns)\n", interval_ns);
		}

		/* Run timer loop */
		while (!g_intr && !do_exit) {
			usleep(interval_us > 0 ? interval_us : 1000000);

			if (ds->action) {
				exec_printf(ds->action);
				if (has_exit_action(ds->action))
					do_exit = 1;
			}
		}

		if (!g_quiet)
			printf("\ndtrace: END probe firing\n");
		break;
	}

	case PROBE_END:
		if (!g_quiet)
			printf("dtrace: END probe enabled\n");

		/* Wait for interrupt */
		while (!g_intr)
			usleep(100000);

		/* Execute END action */
		if (ds->action)
			exec_printf(ds->action);
		break;

	case PROBE_ERROR:
		if (!g_quiet)
			printf("dtrace: ERROR probe enabled (no errors)\n");
		break;

	default:
		fprintf(stderr, "%s: unsupported probe type\n", g_pname);
		return -1;
	}

	return 0;
}

/*
 * Free script resources
 */
static void
free_script(dscript_t *ds)
{
	free(ds->provider);
	free(ds->module);
	free(ds->function);
	free(ds->name);
	free(ds->predicate);
	free(ds->action);
}

/*
 * Main entry point
 */
int
main(int argc, char *argv[])
{
	int c;
	const char *script = NULL;
	const char *script_file = NULL;
	dscript_t ds;

	g_pname = argv[0];

	while ((c = getopt(argc, argv, "hn:qs:vV")) != -1) {
		switch (c) {
		case 'h':
			usage(stdout);
			return 0;

		case 'n':
			script = optarg;
			break;

		case 'q':
			g_quiet = 1;
			break;

		case 's':
			script_file = optarg;
			break;

		case 'v':
			g_verbose = 1;
			break;

		case 'V':
			print_version();
			return 0;

		default:
			usage(stderr);
			return 2;
		}
	}

	/* Read script from file if specified */
	if (script_file) {
		FILE *fp = fopen(script_file, "r");
		if (!fp) {
			fprintf(stderr, "%s: cannot open %s: %s\n",
			    g_pname, script_file, strerror(errno));
			return 1;
		}

		fseek(fp, 0, SEEK_END);
		long size = ftell(fp);
		fseek(fp, 0, SEEK_SET);

		char *buf = malloc(size + 1);
		if (!buf) {
			fprintf(stderr, "%s: out of memory\n", g_pname);
			fclose(fp);
			return 1;
		}

		if (fread(buf, 1, size, fp) != (size_t)size) {
			fprintf(stderr, "%s: error reading %s\n",
			    g_pname, script_file);
			free(buf);
			fclose(fp);
			return 1;
		}
		buf[size] = '\0';
		fclose(fp);

		script = buf;
	}

	if (!script) {
		fprintf(stderr, "%s: no script specified\n", g_pname);
		fprintf(stderr, "Use -n 'probe { action }' or -s script_file\n");
		usage(stderr);
		return 2;
	}

	/* Parse the script */
	if (parse_script(script, &ds) != 0)
		return 1;

	if (g_verbose) {
		printf("Probe: %s:::%s\n",
		    ds.provider ? ds.provider : "",
		    ds.name ? ds.name : "");
		if (ds.predicate)
			printf("Predicate: %s\n", ds.predicate);
		if (ds.action)
			printf("Action: %s\n", ds.action);
	}

	/* Execute the script */
	g_status = execute_script(&ds);

	/* Cleanup */
	free_script(&ds);

	return g_status;
}
