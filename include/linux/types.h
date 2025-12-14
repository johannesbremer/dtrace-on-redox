/* SPDX-License-Identifier: GPL-2.0 WITH Linux-syscall-note */
/*
 * Linux types - Redox compatibility header
 * Provides __u8, __u16, __u32, __u64, __s8, __s16, __s32, __s64
 */

#ifndef _LINUX_TYPES_H
#define _LINUX_TYPES_H

#include <stdint.h>

typedef uint8_t  __u8;
typedef uint16_t __u16;
typedef uint32_t __u32;
typedef uint64_t __u64;

typedef int8_t   __s8;
typedef int16_t  __s16;
typedef int32_t  __s32;
typedef int64_t  __s64;

typedef uint16_t __be16;
typedef uint32_t __be32;
typedef uint64_t __be64;

typedef uint16_t __le16;
typedef uint32_t __le32;
typedef uint64_t __le64;

typedef __u16 __sum16;
typedef __u32 __wsum;

/* Aligned types for BPF structures */
typedef __u64 __attribute__((aligned(8))) __aligned_u64;
typedef __s64 __attribute__((aligned(8))) __aligned_s64;

#endif /* _LINUX_TYPES_H */
