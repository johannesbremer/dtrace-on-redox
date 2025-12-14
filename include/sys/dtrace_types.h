/*
 * Oracle Linux DTrace - RedoxOS Port
 * Copyright (c) 2011, 2025, Oracle and/or its affiliates. All rights reserved.
 * Licensed under the Universal Permissive License v 1.0 as shown at
 * http://oss.oracle.com/licenses/upl.
 *
 * Symlink/copy of uts/common/sys/dtrace_types.h for include path
 */

#ifndef DTRACE_SYS_TYPES_H
#define DTRACE_SYS_TYPES_H

#include <sys/types.h>
#include <stdint.h>
#include <unistd.h>

/* RedoxOS uses little-endian x86_64 */
#ifndef __BYTE_ORDER
#define __BYTE_ORDER __LITTLE_ENDIAN
#endif
#ifndef __LITTLE_ENDIAN
#define __LITTLE_ENDIAN 1234
#endif
#ifndef __BIG_ENDIAN
#define __BIG_ENDIAN 4321
#endif

typedef enum { B_FALSE, B_TRUE } boolean_t;

/*
 * POSIX Extensions
 */
typedef unsigned char	uchar_t;
typedef unsigned short	ushort_t;
typedef unsigned int	uint_t;
typedef unsigned long	ulong_t;

typedef long long	offset_t;
typedef unsigned long long hrtime_t;

#define	SHT_SUNW_dof		0x6ffffff4
#define	STV_ELIMINATE		6

#if !defined(PN_XNUM)
#define PN_XNUM 0xffff
#endif

/*
 * Time resolutions
 */
#define SEC		1
#define MILLISEC	1000
#define MICROSEC	1000000
#define NANOSEC		1000000000

#define SIG2STR_MAX	32

#ifndef ABS
#define	ABS(a)		((a) < 0 ? -(a) : (a))
#endif

#define _LITTLE_ENDIAN 1

/*
 * P2ROUNDUP - round x up to alignment boundary
 */
#define P2ROUNDUP(x, align)	(-(-(x) & -(align)))

/*
 * DTrace ID type
 */
typedef uint32_t dtrace_id_t;

#endif /* DTRACE_SYS_TYPES_H */
