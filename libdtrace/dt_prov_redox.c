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
 *   - profile:::tick-* - timer-based probes (emulated)
 *   - pid$target:::entry/return - self function tracing
 */

#include <errno.h>
#include <signal.h>
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
	
	/* Timer for profile probes */
	timer_t		timer_id;
	int		timer_active;
	uint64_t	tick_interval_ns;
	
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
 * Signal handler for timer-based probes
 */
static void
timer_signal_handler(int sig, siginfo_t *si, void *uc)
{
	(void)sig;
	(void)si;
	(void)uc;
	
	if (g_trace_ctx.active && g_trace_ctx.probe_callback) {
		g_trace_ctx.probe_count++;
		g_trace_ctx.probe_callback(REDOX_PROBE_TICK,
					   g_trace_ctx.callback_arg);
	}
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
	if (g_trace_ctx.timer_active) {
		timer_delete(g_trace_ctx.timer_id);
		g_trace_ctx.timer_active = 0;
	}
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
	
	if (g_trace_ctx.timer_active) {
		timer_delete(g_trace_ctx.timer_id);
		g_trace_ctx.timer_active = 0;
	}
	
	return 0;
}

/*
 * Enable a profile/tick probe with the specified interval
 */
int
redox_trace_enable_tick(uint64_t interval_ns)
{
	struct sigevent sev;
	struct itimerspec its;
	struct sigaction sa;
	
	if (g_trace_ctx.timer_active)
		return -EBUSY;
	
	/* Set up signal handler */
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = timer_signal_handler;
	sigemptyset(&sa.sa_mask);
	if (sigaction(SIGRTMIN, &sa, NULL) == -1)
		return -errno;
	
	/* Create timer */
	sev.sigev_notify = SIGEV_SIGNAL;
	sev.sigev_signo = SIGRTMIN;
	sev.sigev_value.sival_ptr = &g_trace_ctx.timer_id;
	
	if (timer_create(CLOCK_MONOTONIC, &sev, &g_trace_ctx.timer_id) == -1)
		return -errno;
	
	/* Set timer interval */
	its.it_value.tv_sec = interval_ns / 1000000000;
	its.it_value.tv_nsec = interval_ns % 1000000000;
	its.it_interval = its.it_value;
	
	if (timer_settime(g_trace_ctx.timer_id, 0, &its, NULL) == -1) {
		timer_delete(g_trace_ctx.timer_id);
		return -errno;
	}
	
	g_trace_ctx.timer_active = 1;
	g_trace_ctx.tick_interval_ns = interval_ns;
	
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
