/*
 * Oracle Linux DTrace - RedoxOS Port
 * Copyright (c) 2025, Oracle and/or its affiliates. All rights reserved.
 * Licensed under the Universal Permissive License v 1.0 as shown at
 * http://oss.oracle.com/licenses/upl.
 *
 * Autoconf-style config.h for RedoxOS build
 */

#ifndef _CONFIG_H
#define _CONFIG_H

/* RedoxOS-specific configuration */
#define __redox__ 1

/* Use rbpf backend instead of Linux kernel BPF */
#define USE_RBPF_BACKEND 1

/* Self-trace only mode */
#define DT_SELF_TRACE_ONLY 1

/* No kernel tracing support */
#define DT_NO_KERNEL_TRACING 1

/* Features available in relibc */
#define HAVE_STRLCPY 1
#define HAVE_STRLCAT 1
#define HAVE_FNMATCH 1

/* Features NOT available on RedoxOS */
#undef HAVE_LIBSYSTEMD
#undef HAVE_PERF_EVENT_OPEN
#undef HAVE_TRACEFS
#undef HAVE_KPROBES
#undef HAVE_UPROBES
#undef HAVE_BTF
#undef HAVE_ELF_GETSHDRSTRNDX
#undef HAVE_CLOSE_RANGE
#undef HAVE_GETTID
#undef HAVE_LIBCTF

/* Don't include valgrind support */
#undef HAVE_VALGRIND

/* Path definitions */
#define DTRACE_LIBDIR "/usr/lib/dtrace"
#define DTRACE_INCDIR "/usr/include/dtrace"

/* User ID definitions */
#ifndef USER_UID
#define USER_UID 1000
#endif

#ifndef UNPRIV_UID
#define UNPRIV_UID 65534
#endif

#ifndef DUMPCAP_GROUP
#define DUMPCAP_GROUP "dumpcap"
#endif

#ifndef UNPRIV_HOME
#define UNPRIV_HOME "/tmp"
#endif

/* Package version */
#define PACKAGE_VERSION "2.0.0-redox"

#endif /* _CONFIG_H */
