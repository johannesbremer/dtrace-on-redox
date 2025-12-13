/*
 * Oracle Linux DTrace - RedoxOS Port
 * Copyright (c) 2025, Oracle and/or its affiliates. All rights reserved.
 * Licensed under the Universal Permissive License v 1.0 as shown at
 * http://oss.oracle.com/licenses/upl.
 *
 * RedoxOS configuration header
 *
 * This header provides configuration for building DTrace on RedoxOS.
 * It defines feature flags and platform-specific settings.
 */

#ifndef _CONFIG_REDOX_H
#define _CONFIG_REDOX_H

#ifdef __redox__

/*
 * Platform identification
 */
#define DT_PLATFORM_REDOX	1
#define DT_PLATFORM_NAME	"RedoxOS"

/*
 * Force rbpf backend on RedoxOS
 */
#define DT_BPF_BACKEND_RBPF	1

/*
 * Disable Linux-specific features
 */
#undef HAVE_LIBSYSTEMD
#undef HAVE_PERF_EVENT_OPEN
#undef HAVE_TRACEFS
#undef HAVE_KPROBES
#undef HAVE_UPROBES
#undef HAVE_BTF

/*
 * Feature flags for RedoxOS
 */
#define HAVE_CLOCK_MONOTONIC	1
#define HAVE_POSIX_TIMERS	1

/*
 * RedoxOS uses relibc which provides these
 */
#define HAVE_STRLCPY		1
#define HAVE_STRLCAT		1
#define HAVE_FNMATCH		1

/*
 * No ELF getshdrstrndx in older libraries
 */
#undef HAVE_ELF_GETSHDRSTRNDX

/*
 * close_range availability
 */
#undef HAVE_CLOSE_RANGE

/*
 * gettid availability
 */
#undef HAVE_GETTID

/*
 * Self-trace only mode
 * On RedoxOS, DTrace can only trace itself for now
 */
#define DT_SELF_TRACE_ONLY	1

/*
 * No kernel tracing support
 */
#define DT_NO_KERNEL_TRACING	1

/*
 * User ID definitions
 */
#ifndef USER_UID
#define USER_UID	1000
#endif

#ifndef UNPRIV_UID
#define UNPRIV_UID	65534
#endif

/*
 * Path definitions for RedoxOS
 */
#define DTRACE_LIBDIR		"/usr/lib/dtrace"
#define DTRACE_INCDIR		"/usr/include/dtrace"

/*
 * Disable features that require kernel support
 */
#define DT_DISABLE_FBT		1
#define DT_DISABLE_SDT		1
#define DT_DISABLE_SYSCALL	1
#define DT_DISABLE_SCHED	1
#define DT_DISABLE_IO		1
#define DT_DISABLE_IP		1
#define DT_DISABLE_TCP		1
#define DT_DISABLE_UDP		1
#define DT_DISABLE_PROC		1
#define DT_DISABLE_LOCKSTAT	1
#define DT_DISABLE_CPC		1
#define DT_DISABLE_RAWTP	1

/*
 * Enable user-space only providers
 */
#define DT_ENABLE_DTRACE	1	/* BEGIN, END, ERROR */
#define DT_ENABLE_PROFILE	1	/* tick-*, profile-* (emulated) */

#endif /* __redox__ */

#endif /* _CONFIG_REDOX_H */
