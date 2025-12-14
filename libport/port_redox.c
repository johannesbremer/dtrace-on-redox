/*
 * Oracle Linux DTrace - RedoxOS Port
 * Copyright (c) 2025, Oracle and/or its affiliates. All rights reserved.
 * Licensed under the Universal Permissive License v 1.0 as shown at
 * http://oss.oracle.com/licenses/upl.
 *
 * RedoxOS-specific platform implementation
 *
 * This file provides RedoxOS implementations of platform-specific
 * functions that are normally Linux-specific.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <errno.h>
#include <unistd.h>
#include <fnmatch.h>

#include <sys/compiler.h>
#include <port.h>

/*
 * strlcpy - copy string with size limit
 */
#ifndef HAVE_STRLCPY
size_t
strlcpy(char *dst, const char *src, size_t size)
{
	size_t len = strlen(src);
	if (size > 0) {
		size_t copy = (len >= size) ? size - 1 : len;
		memcpy(dst, src, copy);
		dst[copy] = '\0';
	}
	return len;
}

size_t
strlcat(char *dst, const char *src, size_t size)
{
	size_t dlen = strlen(dst);
	size_t slen = strlen(src);
	
	if (dlen >= size)
		return size + slen;
	
	size_t copy = (slen >= size - dlen) ? size - dlen - 1 : slen;
	memcpy(dst + dlen, src, copy);
	dst[dlen + copy] = '\0';
	
	return dlen + slen;
}
#endif

/*
 * gmatch is provided by gmatch.c - do not define here to avoid multiple definitions
 */

/*
 * daemon_perr - log error and exit
 */
_dt_noreturn_ void
daemon_perr(int fd, const char *err, int err_no)
{
	(void)fd;
	fprintf(stderr, "dtrace: %s: %s\n", err, strerror(err_no));
	exit(1);
}

/*
 * daemon_log - log message
 */
_dt_printflike_(2, 3) void
daemon_log(int fd, const char *fmt, ...)
{
	va_list ap;
	(void)fd;
	
	va_start(ap, fmt);
	vfprintf(stderr, fmt, ap);
	va_end(ap);
	fprintf(stderr, "\n");
}

