/*
 * Oracle Linux DTrace - RedoxOS Port
 * Copyright (c) 2025, Oracle and/or its affiliates. All rights reserved.
 * Licensed under the Universal Permissive License v 1.0 as shown at
 * http://oss.oracle.com/licenses/upl.
 *
 * Eventfd stubs for RedoxOS - eventfd is not available.
 */

#ifndef _SYS_EVENTFD_H
#define _SYS_EVENTFD_H

#include <stdint.h>

/* eventfd flags */
#define EFD_CLOEXEC  02000000
#define EFD_NONBLOCK 04000
#define EFD_SEMAPHORE 1

typedef uint64_t eventfd_t;

/* Stub function - eventfd not available on Redox */
static inline int eventfd(unsigned int initval, int flags)
{
	(void)initval;
	(void)flags;
	return -1;  /* Always fail */
}

static inline int eventfd_read(int fd, eventfd_t *value)
{
	(void)fd;
	(void)value;
	return -1;
}

static inline int eventfd_write(int fd, eventfd_t value)
{
	(void)fd;
	(void)value;
	return -1;
}

#endif /* _SYS_EVENTFD_H */
