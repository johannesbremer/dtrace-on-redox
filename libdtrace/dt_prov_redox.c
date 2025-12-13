/*
 * Oracle Linux DTrace - RedoxOS Port
 * Copyright (c) 2025, Oracle and/or its affiliates. All rights reserved.
 * Licensed under the Universal Permissive License v 1.0 as shown at
 * http://oss.oracle.com/licenses/upl.
 *
 * RedoxOS Self-Trace Provider
 *
 * This provider enables DTrace to trace its own execution on RedoxOS.
 * Since RedoxOS doesn't have kernel tracing capabilities like Linux,
 * this provider focuses on user-space self-tracing.
 *
 * Supported probes:
 *   - dtrace:::BEGIN - fires at start of tracing
 *   - dtrace:::END   - fires at end of tracing
 *   - dtrace:::ERROR - fires on errors
 *   - profile:::tick-* - timer-based probes (polling-based)
 *
 * Note: This implementation uses polling instead of POSIX timers
 * since relibc doesn't fully support timer_create/sigevent.
 */

#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#ifdef __redox__

#include <dt_bpf_backend.h>

/*
 * Self-trace context for RedoxOS
 */
typedef struct redox_trace_ctx {
	pid_t		pid;		/* Process being traced (self) */
	int		active;		/* Is tracing active? */
	uint64_t	start_time;	/* Tracing start time */
	uint64_t	probe_count;	/* Number of probes fired */
	
	/* Timer for profile probes (polling-based) */
	int		timer_active;
	uint64_t	tick_interval_ns;
	uint64_t	last_tick_time;
	
	/* Callback for probe firing */
	void		(*probe_callback)(int probe_id, void *arg);
	void		*callback_arg;
} redox_trace_ctx_t;

static redox_trace_ctx_t g_trace_ctx;

/*
 * Probe IDs for built-in probes
 */
#define REDOX_PROBE_BEGIN	1
#define REDOX_PROBE_END		2
#define REDOX_PROBE_ERROR	3
#define REDOX_PROBE_TICK	4

/*
 * Get current time in nanoseconds
 */
static uint64_t
get_time_ns(void)
{
	struct timespec ts;
	if (clock_gettime(CLOCK_MONOTONIC, &ts) == 0)
		return (uint64_t)ts.tv_sec * 1000000000ULL + ts.tv_nsec;
	return 0;
}

/*
 * Initialize the RedoxOS self-trace provider
 */
int
redox_trace_init(void)
{
	memset(&g_trace_ctx, 0, sizeof(g_trace_ctx));
	g_trace_ctx.pid = getpid();
	g_trace_ctx.start_time = get_time_ns();
	
	return 0;
}

/*
 * Clean up the RedoxOS self-trace provider
 */
void
redox_trace_fini(void)
{
	g_trace_ctx.timer_active = 0;
	g_trace_ctx.active = 0;
}

/*
 * Start tracing
 */
int
redox_trace_start(void (*callback)(int, void *), void *arg)
{
	g_trace_ctx.probe_callback = callback;
	g_trace_ctx.callback_arg = arg;
	g_trace_ctx.active = 1;
	g_trace_ctx.probe_count = 0;
	
	/* Fire BEGIN probe */
	if (callback)
		callback(REDOX_PROBE_BEGIN, arg);
	
	return 0;
}

/*
 * Stop tracing
 */
int
redox_trace_stop(void)
{
	/* Fire END probe */
	if (g_trace_ctx.active && g_trace_ctx.probe_callback)
		g_trace_ctx.probe_callback(REDOX_PROBE_END,
					   g_trace_ctx.callback_arg);
	
	g_trace_ctx.active = 0;
	g_trace_ctx.timer_active = 0;
	
	return 0;
}

/*
 * Enable a profile/tick probe with the specified interval
 *
 * Note: This uses a polling model instead of POSIX timers.
 * The caller must periodically call redox_trace_poll() to
 * fire tick probes.
 */
int
redox_trace_enable_tick(uint64_t interval_ns)
{
	if (g_trace_ctx.timer_active)
		return -EBUSY;
	
	g_trace_ctx.tick_interval_ns = interval_ns;
	g_trace_ctx.last_tick_time = get_time_ns();
	g_trace_ctx.timer_active = 1;
	
	return 0;
}

/*
 * Poll for tick probes - call this periodically from the main loop
 */
int
redox_trace_poll(void)
{
	uint64_t now;
	
	if (!g_trace_ctx.active || !g_trace_ctx.timer_active)
		return 0;
	
	now = get_time_ns();
	
	if (now - g_trace_ctx.last_tick_time >= g_trace_ctx.tick_interval_ns) {
		g_trace_ctx.last_tick_time = now;
		g_trace_ctx.probe_count++;
		
		if (g_trace_ctx.probe_callback)
			g_trace_ctx.probe_callback(REDOX_PROBE_TICK,
						   g_trace_ctx.callback_arg);
		return 1;
	}
	
	return 0;
}

/*
 * Fire the ERROR probe
 */
void
redox_trace_error(int error_code, const char *message)
{
	(void)error_code;
	(void)message;
	
	if (g_trace_ctx.active && g_trace_ctx.probe_callback)
		g_trace_ctx.probe_callback(REDOX_PROBE_ERROR,
					   g_trace_ctx.callback_arg);
}

/*
 * Get trace statistics
 */
void
redox_trace_stats(uint64_t *probe_count, uint64_t *elapsed_ns)
{
	if (probe_count)
		*probe_count = g_trace_ctx.probe_count;
	if (elapsed_ns)
		*elapsed_ns = get_time_ns() - g_trace_ctx.start_time;
}

/*
 * Execute a BPF program for a probe using the rbpf backend
 *
 * This is the main entry point for running BPF programs on RedoxOS.
 * Since we're in user-space, we control the execution context.
 */
int
redox_trace_exec_bpf(dt_bpf_prog_t prog, void *ctx, size_t ctx_len,
		     uint64_t *result)
{
	if (dt_bpf_backend == NULL)
		return -ENOENT;
	
	if (dt_bpf_backend->prog_exec == NULL)
		return -ENOTSUP;
	
	*result = dt_bpf_backend->prog_exec(prog, ctx, ctx_len);
	return 0;
}

#endif /* __redox__ */
