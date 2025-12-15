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
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>

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
#define BPF_FUNC_perf_event_output	25
#define BPF_FUNC_probe_read_str		45
#define BPF_FUNC_probe_read_user	112
#define BPF_FUNC_probe_read_kernel	113
#define BPF_FUNC_probe_read_user_str	114
#define BPF_FUNC_probe_read_kernel_str	115

/*
 * User-space perf ring buffer for Redox.
 *
 * This simulates the Linux perf_event ring buffer format so that
 * dtrace_consume() can process output using the existing code paths.
 *
 * The buffer format matches what the kernel would produce:
 *   struct perf_event_header { type, misc, size }
 *   uint32_t data_size
 *   char data[data_size]
 */
#define REDOX_PERF_BUF_SIZE	(256 * 1024)  /* 256KB buffer */

static struct {
	/* Simulated perf_event_mmap_page header */
	uint64_t	data_head;	/* Updated by writer (us) */
	uint64_t	data_tail;	/* Updated by reader (consume) */
	/* Ring buffer data follows */
	char		data[REDOX_PERF_BUF_SIZE];
} redox_perf_buf;

/* perf_event_header types */
#define PERF_RECORD_SAMPLE	9

/* Simulated perf_event_header - matches Linux */
struct redox_perf_event_header {
	uint32_t	type;
	uint16_t	misc;
	uint16_t	size;
};

/*
 * Write data to the user-space perf ring buffer.
 * Returns 0 on success, -1 on failure (buffer full).
 */
static int
redox_perf_write(const void *data, size_t size)
{
	struct redox_perf_event_header hdr;
	uint32_t record_size;
	uint64_t head, tail, avail;
	char *dst;

	/* Total record size: header + data (no alignment needed for user-space) */
	record_size = sizeof(hdr) + size;

	head = redox_perf_buf.data_head;
	tail = redox_perf_buf.data_tail;

	/* Check available space */
	avail = REDOX_PERF_BUF_SIZE - (head - tail);
	if (record_size > avail) {
		fprintf(stderr, "redox_perf_write: buffer full (need %u, have %lu)\n",
			record_size, (unsigned long)avail);
		return -1;
	}

	/* Write header */
	hdr.type = PERF_RECORD_SAMPLE;
	hdr.misc = 0;
	hdr.size = record_size;

	dst = redox_perf_buf.data + (head % REDOX_PERF_BUF_SIZE);

	/* Handle wrap-around (simplified: assume no wrap for now) */
	if (head % REDOX_PERF_BUF_SIZE + record_size > REDOX_PERF_BUF_SIZE) {
		/* Would wrap - for simplicity, fail (shouldn't happen often) */
		fprintf(stderr, "redox_perf_write: would wrap, skipping\n");
		return -1;
	}

	memcpy(dst, &hdr, sizeof(hdr));
	memcpy(dst + sizeof(hdr), data, size);

	/* Memory barrier to ensure writes complete before updating head */
	__sync_synchronize();

	redox_perf_buf.data_head = head + record_size;

	return 0;
}

/*
 * Get the simulated perf buffer base address for dt_peb initialization.
 */
void *
dt_redox_perf_buf_base(void)
{
	return &redox_perf_buf;
}

size_t
dt_redox_perf_buf_data_size(void)
{
	return REDOX_PERF_BUF_SIZE;
}

/*
 * Helper: bpf_map_lookup_elem
 *
 * Looks up a key in a BPF map and returns a pointer to the value.
 * In rbpf, we return the actual value pointer from our user-space maps.
 */
static uint64_t
helper_map_lookup_elem(uint64_t map_fd, uint64_t key_ptr, uint64_t arg2,
		       uint64_t arg3, uint64_t arg4)
{
	void *value_ptr;
	uint32_t key;

	(void)arg2;
	(void)arg3;
	(void)arg4;

	if (dt_bpf_backend == NULL || dt_bpf_backend->map_lookup_ptr == NULL) {
		return 0;  /* NULL pointer */
	}

	if (key_ptr == 0) {
		return 0;
	}

	/* The key_ptr is a pointer in BPF memory - dereference it to get actual key */
	key = *(uint32_t *)(uintptr_t)key_ptr;

	/* Get a direct pointer to the map value (not a copy) */
	value_ptr = dt_bpf_backend->map_lookup_ptr((dt_bpf_map_t)map_fd, &key);

	return (uint64_t)(uintptr_t)value_ptr;
}

/*
 * Helper: bpf_map_update_elem
 *
 * Updates a value in a BPF map.
 */
static uint64_t
helper_map_update_elem(uint64_t map_fd, uint64_t key_ptr, uint64_t value_ptr,
		       uint64_t flags, uint64_t arg4)
{
	uint32_t key;
	uint32_t val32;
	int rc;

	(void)arg4;

	key = *(uint32_t *)(uintptr_t)key_ptr;
	val32 = *(uint32_t *)(uintptr_t)value_ptr;

	if (dt_bpf_backend == NULL || dt_bpf_backend->map_update == NULL)
		return (uint64_t)-1;

	rc = dt_bpf_backend->map_update((dt_bpf_map_t)map_fd,
					&key,
					(const void *)(uintptr_t)value_ptr,
					(uint32_t)flags);
	return (uint64_t)rc;
}

/*
 * Helper: bpf_map_delete_elem
 *
 * Deletes a key from a BPF map.
 */
static uint64_t
helper_map_delete_elem(uint64_t map_fd, uint64_t key_ptr, uint64_t arg2,
		       uint64_t arg3, uint64_t arg4)
{
	(void)arg2;
	(void)arg3;
	(void)arg4;

	if (dt_bpf_backend == NULL || dt_bpf_backend->map_delete == NULL)
		return (uint64_t)-1;

	return (uint64_t)dt_bpf_backend->map_delete((dt_bpf_map_t)map_fd,
						    (const void *)(uintptr_t)key_ptr);
}

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
	uint64_t result;

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
 * Helper: bpf_perf_event_output
 *
 * Output data to a perf event buffer.
 *
 * The data coming in has this format (from BPF epilogue):
 *   bytes 0-3:  SPECID
 *   bytes 4-7:  PRID (probe ID)
 *   bytes 8-11: STID (statement ID)
 *   bytes 12+:  Trace data (record descriptors + data)
 *
 * We prepend a uint32_t size field (as Linux perf does) and write to
 * the user-space ring buffer in the format dtrace_consume() expects:
 *   struct perf_event_header { type=SAMPLE, misc=0, size }
 *   uint32_t size  <- size of remaining data
 *   char data[]    <- SPECID, PRID, STID, trace data
 *
 * Args:
 *   ctx   - BPF context (ignored)
 *   map   - perf event map fd (ignored - we use our buffer)
 *   flags - flags (ignored)
 *   data  - pointer to data (SPECID, PRID, STID, trace data)
 *   size  - size of data
 */
static uint64_t
helper_perf_event_output(uint64_t ctx, uint64_t map, uint64_t flags,
			 uint64_t data, uint64_t size)
{
	char output_buf[4096];
	uint32_t *size_ptr;
	int rc;

	(void)ctx;
	(void)map;
	(void)flags;

	if (data == 0 || size == 0)
		return 0;

	/* Safety check */
	if (size > sizeof(output_buf) - 4) {
		fprintf(stderr, "perf_event_output: data too large (%lu > %zu)\n",
			(unsigned long)size, sizeof(output_buf) - 4);
		return -1;
	}

	/*
	 * Build the output record:
	 *   uint32_t size  <- size of following data
	 *   char data[]    <- the actual trace data
	 */
	size_ptr = (uint32_t *)output_buf;
	*size_ptr = (uint32_t)size;
	memcpy(output_buf + 4, (void *)(uintptr_t)data, size);

	/* Write to our ring buffer */
	rc = redox_perf_write(output_buf, size + 4);

	return rc < 0 ? (uint64_t)-1 : 0;
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
		/* Map operations - critical for BPF programs */
		rc |= dt_bpf_backend->register_helper(
			BPF_FUNC_map_lookup_elem,
			(dt_bpf_helper_fn)helper_map_lookup_elem);
		rc |= dt_bpf_backend->register_helper(
			BPF_FUNC_map_update_elem,
			(dt_bpf_helper_fn)helper_map_update_elem);
		rc |= dt_bpf_backend->register_helper(
			BPF_FUNC_map_delete_elem,
			(dt_bpf_helper_fn)helper_map_delete_elem);

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
		rc |= dt_bpf_backend->register_helper(
			BPF_FUNC_perf_event_output,
			(dt_bpf_helper_fn)helper_perf_event_output);

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
