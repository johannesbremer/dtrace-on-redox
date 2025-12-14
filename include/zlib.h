/*
 * Oracle Linux DTrace - RedoxOS Port
 * Copyright (c) 2025, Oracle and/or its affiliates. All rights reserved.
 * Licensed under the Universal Permissive License v 1.0 as shown at
 * http://oss.oracle.com/licenses/upl.
 *
 * Minimal zlib stubs for RedoxOS
 * We don't support compressed CTF on Redox.
 */

#ifndef _ZLIB_H
#define _ZLIB_H

#include <stddef.h>
#include <stdint.h>

typedef void *voidp;
typedef unsigned char Byte;
typedef unsigned char Bytef;
typedef unsigned int uInt;
typedef unsigned long uLong;
typedef uLong uLongf;

/* Return codes */
#define Z_OK            0
#define Z_STREAM_END    1
#define Z_NEED_DICT     2
#define Z_ERRNO        (-1)
#define Z_STREAM_ERROR (-2)
#define Z_DATA_ERROR   (-3)
#define Z_MEM_ERROR    (-4)
#define Z_BUF_ERROR    (-5)
#define Z_VERSION_ERROR (-6)

/* Compression levels */
#define Z_NO_COMPRESSION         0
#define Z_BEST_SPEED             1
#define Z_BEST_COMPRESSION       9
#define Z_DEFAULT_COMPRESSION  (-1)

/* Flush values */
#define Z_NO_FLUSH      0
#define Z_PARTIAL_FLUSH 1
#define Z_SYNC_FLUSH    2
#define Z_FULL_FLUSH    3
#define Z_FINISH        4
#define Z_BLOCK         5
#define Z_TREES         6

/* Z_NULL for null pointer/function */
#define Z_NULL  0

/* z_stream structure - stub for decompression interface */
typedef struct z_stream_s {
	Bytef    *next_in;   /* next input byte */
	uInt     avail_in;   /* number of bytes available at next_in */
	uLong    total_in;   /* total bytes read so far */
	Bytef    *next_out;  /* next output byte */
	uInt     avail_out;  /* remaining free space at next_out */
	uLong    total_out;  /* total bytes written so far */
	char     *msg;       /* error message */
	void     *state;     /* internal state */
	void     *zalloc;    /* memory allocator */
	void     *zfree;     /* memory deallocator */
	void     *opaque;    /* private data */
	int      data_type;  /* data type */
	uLong    adler;      /* Adler-32 checksum */
	uLong    reserved;   /* reserved for future use */
} z_stream;

/* Stub functions - decompression not supported */
static inline int uncompress(Bytef *dest, uLongf *destLen,
                             const Bytef *source, uLong sourceLen)
{
	(void)dest; (void)destLen; (void)source; (void)sourceLen;
	return Z_DATA_ERROR;
}

static inline int compress(Bytef *dest, uLongf *destLen,
                           const Bytef *source, uLong sourceLen)
{
	(void)dest; (void)destLen; (void)source; (void)sourceLen;
	return Z_DATA_ERROR;
}

static inline int compress2(Bytef *dest, uLongf *destLen,
                            const Bytef *source, uLong sourceLen, int level)
{
	(void)dest; (void)destLen; (void)source; (void)sourceLen; (void)level;
	return Z_DATA_ERROR;
}

static inline uLong compressBound(uLong sourceLen)
{
	return sourceLen + (sourceLen >> 12) + (sourceLen >> 14) + 11;
}

/* Inflate (decompression) stubs */
static inline int inflateInit_(z_stream *strm, const char *version, int stream_size)
{
	(void)strm; (void)version; (void)stream_size;
	return Z_DATA_ERROR;
}

static inline int inflateInit2_(z_stream *strm, int windowBits, const char *version, int stream_size)
{
	(void)strm; (void)windowBits; (void)version; (void)stream_size;
	return Z_DATA_ERROR;
}

#define inflateInit(strm) inflateInit_((strm), "1.0", (int)sizeof(z_stream))
#define inflateInit2(strm, windowBits) inflateInit2_((strm), (windowBits), "1.0", (int)sizeof(z_stream))

static inline int inflate(z_stream *strm, int flush)
{
	(void)strm; (void)flush;
	return Z_DATA_ERROR;
}

static inline int inflateEnd(z_stream *strm)
{
	(void)strm;
	return Z_OK;
}

#endif /* _ZLIB_H */
