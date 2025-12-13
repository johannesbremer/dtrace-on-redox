/*
 * Oracle Linux DTrace - RedoxOS Port
 * Copyright (c) 2025, Oracle and/or its affiliates. All rights reserved.
 * Licensed under the Universal Permissive License v 1.0 as shown at
 * http://oss.oracle.com/licenses/upl.
 *
 * RedoxOS-specific portability definitions
 *
 * This header provides RedoxOS-specific definitions and stubs for
 * functionality that differs from Linux.
 */

#ifndef _PORT_REDOX_H
#define _PORT_REDOX_H

#ifdef __redox__

#include <stdint.h>
#include <stddef.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>

/*
 * RedoxOS doesn't have these Linux-specific headers
 */
#define __USE_GNU 1

/*
 * Time unit definitions (for dt_consume.c, etc.)
 */
#ifndef NANOSEC
#define NANOSEC		1000000000LL
#endif
#ifndef MILLISEC
#define MILLISEC	1000
#endif

/*
 * hrtime_t - high-resolution time type
 */
typedef int64_t hrtime_t;

/*
 * Get high-resolution time in nanoseconds
 */
static inline hrtime_t gethrtime(void)
{
	struct timespec ts;
	if (clock_gettime(CLOCK_MONOTONIC, &ts) == 0)
		return (hrtime_t)ts.tv_sec * 1000000000LL + ts.tv_nsec;
	return 0;
}

/*
 * processorid_t - CPU identifier type
 */
#ifndef _PROCESSORID_T
#define _PROCESSORID_T
typedef int processorid_t;
#endif

/*
 * CPU online check - on RedoxOS, assume single CPU for now
 */
static inline int p_online(int cpun)
{
	return (cpun == 0) ? 1 : -1;
}

/*
 * strlcpy/strlcat - should be available in relibc
 */
#ifndef HAVE_STRLCPY
size_t strlcpy(char *dst, const char *src, size_t size);
size_t strlcat(char *dst, const char *src, size_t size);
#endif

/*
 * gmatch - glob pattern matching
 */
int gmatch(const char *s, const char *p);

/*
 * Daemon functions - minimal stubs for RedoxOS
 */
static inline int daemonize(int close_fds)
{
	(void)close_fds;
	/* RedoxOS doesn't support traditional daemonization */
	return 0;
}

static inline int systemd_notify(const char *message)
{
	(void)message;
	/* No systemd on RedoxOS */
	return 0;
}

/*
 * Linux version code - not applicable on RedoxOS
 */
static inline unsigned long linux_version_code(void)
{
	return 0;
}

/*
 * close_range - close file descriptors in a range
 */
#ifndef HAVE_CLOSE_RANGE
static inline int close_range(unsigned int first, unsigned int last,
			      unsigned int flags)
{
	(void)flags;
	for (unsigned int i = first; i <= last; i++)
		close(i);
	return 0;
}
#endif

/*
 * gettid - get thread ID
 * On RedoxOS, just return the process ID for now
 */
#ifndef HAVE_GETTID
static inline pid_t gettid(void)
{
	return getpid();
}
#endif

/*
 * ptrace is not available on RedoxOS for now
 */
#define PTRACE_SEIZE		0x4206
#define PTRACE_INTERRUPT	0x4207
#define PTRACE_LISTEN		0x4208
#define PTRACE_GETMAPFD		0x42A5
#define PTRACE_EVENT_STOP	128

/*
 * BPF-related definitions
 */
#ifndef EM_BPF
#define EM_BPF			247
#endif
#ifndef R_BPF_NONE
#define R_BPF_NONE		0
#endif
#ifndef R_BPF_64_64
#define R_BPF_64_64		1
#endif
#ifndef R_BPF_64_ABS64
#define R_BPF_64_ABS64		2
#endif
#ifndef R_BPF_64_ABS32
#define R_BPF_64_ABS32		3
#endif
#ifndef R_BPF_64_32
#define R_BPF_64_32		10
#endif

/*
 * O_PATH - not standard, provide a stub
 */
#ifndef O_PATH
#define O_PATH 0
#endif

/*
 * MUTEX_HELD macro - pthread mutex check
 * This is a simplified version for RedoxOS
 */
#define MUTEX_HELD(x) (1)  /* Assume held if called in context */

/*
 * Compiler attributes
 */
#ifndef _dt_noreturn_
#define _dt_noreturn_ __attribute__((__noreturn__))
#endif

#ifndef _dt_printflike_
#define _dt_printflike_(f, a) __attribute__((__format__(__printf__, f, a)))
#endif

/*
 * Daemon logging stubs
 */
_dt_noreturn_ void daemon_perr(int fd, const char *err, int err_no);
_dt_printflike_(2, 3) void daemon_log(int fd, const char *fmt, ...);

#endif /* __redox__ */

#endif /* _PORT_REDOX_H */
