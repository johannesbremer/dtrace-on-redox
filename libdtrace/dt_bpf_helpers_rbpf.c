/*
 * Oracle Linux DTrace.
 * Copyright (c) 2025, Oracle and/or its affiliates. All rights reserved.
 * Licensed under the Universal Permissive License v 1.0 as shown at
 * http://oss.oracle.com/licenses/upl.
 *
 * User-space BPF Helper Emulation for rbpf Backend
 *
 * This file provides user-space implementations of common BPF helper
 * functions for the rbpf backend. These emulate kernel BPF helpers
 * in user-space to enable DTrace to run on non-Linux systems.
 *
 * Platform support:
 *   - Linux: Full emulation
 *   - RedoxOS: Adapted for relibc and Redox syscalls
 *   - Other Unix: POSIX-compliant implementation
 */

#include <errno.h>
#include <stdint.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>

#ifdef __redox__
#include "config_redox.h"
#endif

#include <dt_bpf_backend.h>

/*
 * BPF Helper IDs (matching Linux kernel values)
 */
#define BPF_FUNC_map_lookup_elem	1
#define BPF_FUNC_map_update_elem	2
#define BPF_FUNC_map_delete_elem	3
#define BPF_FUNC_probe_read		4
#define BPF_FUNC_ktime_get_ns		5
#define BPF_FUNC_trace_printk		6
#define BPF_FUNC_get_prandom_u32	7
#define BPF_FUNC_get_smp_processor_id	8
#define BPF_FUNC_get_current_pid_tgid	14
#define BPF_FUNC_get_current_uid_gid	15
#define BPF_FUNC_get_current_comm	16
#define BPF_FUNC_probe_read_str		45
#define BPF_FUNC_probe_read_user	112
#define BPF_FUNC_probe_read_kernel	113
#define BPF_FUNC_probe_read_user_str	114
#define BPF_FUNC_probe_read_kernel_str	115

/*
 * Helper: bpf_probe_read
 *
 * In user-space, this just does a memcpy since we're reading from
 * our own address space (not kernel memory).
 */
static uint64_t
helper_probe_read(uint64_t dst, uint64_t size, uint64_t src,
		  uint64_t arg3, uint64_t arg4)
{
	(void)arg3;
	(void)arg4;

	if (dst == 0 || src == 0 || size == 0)
		return (uint64_t)-EFAULT;

	memcpy((void *)(uintptr_t)dst, (void *)(uintptr_t)src, (size_t)size);
	return 0;
}

/*
 * Helper: bpf_ktime_get_ns
 *
 * Returns monotonic time in nanoseconds.
 */
static uint64_t
helper_ktime_get_ns(uint64_t arg0, uint64_t arg1, uint64_t arg2,
		    uint64_t arg3, uint64_t arg4)
{
	struct timespec ts;

	(void)arg0;
	(void)arg1;
	(void)arg2;
	(void)arg3;
	(void)arg4;

#ifdef CLOCK_MONOTONIC
	if (clock_gettime(CLOCK_MONOTONIC, &ts) == 0)
		return (uint64_t)ts.tv_sec * 1000000000ULL + (uint64_t)ts.tv_nsec;
#endif
	return 0;
}

/*
 * Helper: bpf_get_prandom_u32
 *
 * Returns a pseudo-random 32-bit number.
 */
static uint64_t
helper_get_prandom_u32(uint64_t arg0, uint64_t arg1, uint64_t arg2,
		       uint64_t arg3, uint64_t arg4)
{
	static uint64_t state = 0x12345678;

	(void)arg0;
	(void)arg1;
	(void)arg2;
	(void)arg3;
	(void)arg4;

	/* Simple xorshift PRNG */
	state ^= state << 13;
	state ^= state >> 17;
	state ^= state << 5;

	return (uint32_t)state;
}

/*
 * Helper: bpf_get_smp_processor_id
 *
 * Returns the current CPU ID. In user-space, we just return 0.
 */
static uint64_t
helper_get_smp_processor_id(uint64_t arg0, uint64_t arg1, uint64_t arg2,
			    uint64_t arg3, uint64_t arg4)
{
	(void)arg0;
	(void)arg1;
	(void)arg2;
	(void)arg3;
	(void)arg4;

	/* TODO: Could use sched_getcpu() on Linux */
	return 0;
}

/*
 * Helper: bpf_get_current_pid_tgid
 *
 * Returns (tgid << 32) | pid. In user-space, pid == tgid for the main thread.
 */
static uint64_t
helper_get_current_pid_tgid(uint64_t arg0, uint64_t arg1, uint64_t arg2,
			    uint64_t arg3, uint64_t arg4)
{
	pid_t pid;

	(void)arg0;
	(void)arg1;
	(void)arg2;
	(void)arg3;
	(void)arg4;

	pid = getpid();
	return ((uint64_t)pid << 32) | (uint64_t)pid;
}

/*
 * Helper: bpf_get_current_uid_gid
 *
 * Returns (gid << 32) | uid.
 */
static uint64_t
helper_get_current_uid_gid(uint64_t arg0, uint64_t arg1, uint64_t arg2,
			   uint64_t arg3, uint64_t arg4)
{
	uid_t uid;
	gid_t gid;

	(void)arg0;
	(void)arg1;
	(void)arg2;
	(void)arg3;
	(void)arg4;

	uid = getuid();
	gid = getgid();
	return ((uint64_t)gid << 32) | (uint64_t)uid;
}

/*
 * Helper: bpf_get_current_comm
 *
 * Copies the current process name to the buffer.
 */
static uint64_t
helper_get_current_comm(uint64_t buf, uint64_t size, uint64_t arg2,
			uint64_t arg3, uint64_t arg4)
{
	const char *comm = "dtrace";  /* Default for user-space */

	(void)arg2;
	(void)arg3;
	(void)arg4;

	if (buf == 0 || size == 0)
		return (uint64_t)-EINVAL;

	/* In real implementation, would read /proc/self/comm */
	strncpy((char *)(uintptr_t)buf, comm, (size_t)size - 1);
	((char *)(uintptr_t)buf)[size - 1] = '\0';

	return 0;
}

/*
 * Helper: bpf_probe_read_str
 *
 * Reads a null-terminated string from memory.
 */
static uint64_t
helper_probe_read_str(uint64_t dst, uint64_t size, uint64_t src,
		      uint64_t arg3, uint64_t arg4)
{
	size_t len;

	(void)arg3;
	(void)arg4;

	if (dst == 0 || src == 0 || size == 0)
		return (uint64_t)-EFAULT;

	len = strlen((const char *)(uintptr_t)src);
	if (len >= size)
		len = size - 1;

	memcpy((void *)(uintptr_t)dst, (void *)(uintptr_t)src, len);
	((char *)(uintptr_t)dst)[len] = '\0';

	return (uint64_t)(len + 1);
}

/*
 * Helper: bpf_trace_printk
 *
 * Debug printf - just returns 0 in user-space for now.
 */
static uint64_t
helper_trace_printk(uint64_t fmt, uint64_t fmt_size, uint64_t arg1,
		    uint64_t arg2, uint64_t arg3)
{
	(void)fmt;
	(void)fmt_size;
	(void)arg1;
	(void)arg2;
	(void)arg3;

	/* Could implement actual printing if needed */
	return 0;
}

/*
 * Register all user-space helper emulations with the backend.
 *
 * This function should be called after the rbpf backend is initialized
 * to register emulated helper functions.
 */
int
dt_bpf_register_rbpf_helpers(void)
{
	int rc = 0;

	if (dt_bpf_backend == NULL)
		return -1;

	/* Register helpers */
	if (dt_bpf_backend->register_helper != NULL) {
		rc |= dt_bpf_backend->register_helper(
			BPF_FUNC_probe_read,
			(dt_bpf_helper_fn)helper_probe_read);
		rc |= dt_bpf_backend->register_helper(
			BPF_FUNC_ktime_get_ns,
			(dt_bpf_helper_fn)helper_ktime_get_ns);
		rc |= dt_bpf_backend->register_helper(
			BPF_FUNC_get_prandom_u32,
			(dt_bpf_helper_fn)helper_get_prandom_u32);
		rc |= dt_bpf_backend->register_helper(
			BPF_FUNC_get_smp_processor_id,
			(dt_bpf_helper_fn)helper_get_smp_processor_id);
		rc |= dt_bpf_backend->register_helper(
			BPF_FUNC_get_current_pid_tgid,
			(dt_bpf_helper_fn)helper_get_current_pid_tgid);
		rc |= dt_bpf_backend->register_helper(
			BPF_FUNC_get_current_uid_gid,
			(dt_bpf_helper_fn)helper_get_current_uid_gid);
		rc |= dt_bpf_backend->register_helper(
			BPF_FUNC_get_current_comm,
			(dt_bpf_helper_fn)helper_get_current_comm);
		rc |= dt_bpf_backend->register_helper(
			BPF_FUNC_probe_read_str,
			(dt_bpf_helper_fn)helper_probe_read_str);
		rc |= dt_bpf_backend->register_helper(
			BPF_FUNC_trace_printk,
			(dt_bpf_helper_fn)helper_trace_printk);

		/* User/kernel read variants - same as probe_read in user-space */
		rc |= dt_bpf_backend->register_helper(
			BPF_FUNC_probe_read_user,
			(dt_bpf_helper_fn)helper_probe_read);
		rc |= dt_bpf_backend->register_helper(
			BPF_FUNC_probe_read_kernel,
			(dt_bpf_helper_fn)helper_probe_read);
		rc |= dt_bpf_backend->register_helper(
			BPF_FUNC_probe_read_user_str,
			(dt_bpf_helper_fn)helper_probe_read_str);
		rc |= dt_bpf_backend->register_helper(
			BPF_FUNC_probe_read_kernel_str,
			(dt_bpf_helper_fn)helper_probe_read_str);
	}

	return rc;
}
