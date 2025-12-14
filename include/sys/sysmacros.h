/*
 * Oracle Linux DTrace - RedoxOS Port
 * Copyright (c) 2025, Oracle and/or its affiliates. All rights reserved.
 * Licensed under the Universal Permissive License v 1.0 as shown at
 * http://oss.oracle.com/licenses/upl.
 *
 * System macros for device major/minor numbers
 */

#ifndef _SYS_SYSMACROS_H
#define _SYS_SYSMACROS_H

#include <sys/types.h>

/* Device number macros */
#ifndef major
#define major(dev)  ((unsigned int)(((dev) >> 8) & 0xfff))
#endif

#ifndef minor
#define minor(dev)  ((unsigned int)((dev) & 0xff) | (((dev) >> 12) & 0xfff00))
#endif

#ifndef makedev
#define makedev(maj, min) (((min) & 0xff) | (((maj) & 0xfff) << 8) | \
                           (((min) & ~0xff) << 12))
#endif

#endif /* _SYS_SYSMACROS_H */
