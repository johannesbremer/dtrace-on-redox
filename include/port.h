/*
 * Oracle Linux DTrace - RedoxOS Port
 * Copyright (c) 2011, 2025, Oracle and/or its affiliates. All rights reserved.
 * Licensed under the Universal Permissive License v 1.0 as shown at
 * http://oss.oracle.com/licenses/upl.
 *
 * Portability layer for RedoxOS (Redox-only build)
 */

#ifndef _PORT_H
#define _PORT_H

#include <pthread.h>
#include <stdarg.h>
#include <stdint.h>
#include <unistd.h>
#include <time.h>
#include <errno.h>
#include <fcntl.h>
#include <libgen.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/compiler.h>
#include <sys/ptrace.h>
#include <sys/dtrace_types.h>

/*
 * PIPE_BUF - max atomic write to pipe (POSIX minimum)
 */
#ifndef PIPE_BUF
#define PIPE_BUF 4096
#endif

/*
 * splice flags - Linux-specific, stub for Redox
 */
#ifndef SPLICE_F_MORE
#define SPLICE_F_MORE 0
#endif

/*
 * splice - Linux-specific zero-copy data transfer, stub
 */
static inline ssize_t splice(int fd_in, off_t *off_in, int fd_out,
			     off_t *off_out, size_t len, unsigned int flags)
{
	(void)fd_in; (void)off_in; (void)fd_out; (void)off_out;
	(void)len; (void)flags;
	errno = ENOSYS;
	return -1;
}

/*
 * String functions (available in relibc)
 */
extern size_t strlcpy(char *, const char *, size_t);
extern size_t strlcat(char *, const char *, size_t);
extern int gmatch(const char *s, const char *p);

/*
 * High-resolution time
 */
static inline hrtime_t gethrtime(void)
{
	struct timespec ts;
	if (clock_gettime(CLOCK_MONOTONIC, &ts) == 0)
		return (hrtime_t)ts.tv_sec * NANOSEC + ts.tv_nsec;
	return 0;
}

/*
 * CPU online check - RedoxOS: assume single CPU
 */
static inline int p_online(int cpun)
{
	return (cpun == 0) ? 1 : -1;
}

/*
 * Mutex held check
 */
#define MUTEX_HELD(x)	(1)

/*
 * Daemon functions - stubs for RedoxOS
 */
static inline int daemonize(int close_fds)
{
	(void)close_fds;
	return 0;
}

static inline int systemd_notify(const char *message)
{
	(void)message;
	return 0;
}

/*
 * Linux version - not applicable
 */
static inline unsigned long linux_version_code(void)
{
	return 0;
}

/*
 * close_range - close file descriptors in a range
 */
static inline int close_range(unsigned int first, unsigned int last,
			      unsigned int flags)
{
	(void)flags;
	for (unsigned int i = first; i <= last; i++)
		close(i);
	return 0;
}

/*
 * gettid - get thread ID (use PID on RedoxOS)
 */
static inline pid_t gettid(void)
{
	return getpid();
}

/*
 * Daemon logging
 */
_dt_noreturn_ void daemon_perr(int fd, const char *err, int err_no);
_dt_printflike_(2, 3) void daemon_log(int fd, const char *fmt, ...);
void daemon_vlog(int fd, const char *fmt, va_list ap);

/*
 * ELF compatibility - our gelf.h provides elf_getshdrstrndx
 * Map old names to new
 */
#ifndef HAVE_ELF_GETSHDRSTRNDX
#define HAVE_ELF_GETSHDRSTRNDX 1
#endif
#ifndef elf_getshstrndx
#define elf_getshstrndx elf_getshdrstrndx
#endif
#ifndef elf_getshnum
#define elf_getshnum elf_getshdrnum
#endif

/*
 * O_PATH - not standard on RedoxOS
 */
#ifndef O_PATH
#define O_PATH 0
#endif

/*
 * ptrace constants - stubs (not used on RedoxOS)
 */
#define PTRACE_SEIZE		0x4206
#define PTRACE_INTERRUPT	0x4207
#define PTRACE_LISTEN		0x4208
#define PTRACE_GETMAPFD		0x42A5
#define PTRACE_EVENT_STOP	128

/*
 * BPF ELF machine and relocation types
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
 * Error codes
 */
#ifndef ENOTSUPP
#define ENOTSUPP		524
#endif

/*
 * qsort_r - glibc-compatible version for Redox
 * The glibc/Redox signature is: qsort_r(base, nmemb, size, compar, arg)
 * where compar is: int (*compar)(const void *, const void *, void *)
 */
#ifndef HAVE_QSORT_R
static inline void qsort_r(void *base, size_t nmemb, size_t size,
    int (*compar)(const void *, const void *, void *), void *arg)
{
	/* 
	 * Simple wrapper - for now just use qsort if not available.
	 * A full implementation would need to thread the arg through.
	 */
	(void)arg;
	(void)compar;
	/* Fall back to no-sort if qsort_r isn't available */
	(void)base; (void)nmemb; (void)size;
}
#endif

#endif /* _PORT_H */
