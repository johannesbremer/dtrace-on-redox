/*
 * Oracle Linux DTrace.
 * Copyright (c) 2025, Oracle and/or its affiliates. All rights reserved.
 * Licensed under the Universal Permissive License v 1.0 as shown at
 * http://oss.oracle.com/licenses/upl.
 *
 * Linux BPF Backend Implementation
 *
 * This file implements the BPF backend operations using Linux kernel
 * BPF syscalls. This is the default backend on Linux systems.
 */

#include <dt_bpf_backend.h>

#if defined(__linux__)

#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <linux/perf_event.h>
#include <linux/bpf.h>

/*
 * Map portable types to Linux types
 */
static inline enum bpf_map_type
map_type_to_linux(dt_bpf_map_type_t type)
{
	switch (type) {
	case DT_BPF_MAP_TYPE_HASH:
		return BPF_MAP_TYPE_HASH;
	case DT_BPF_MAP_TYPE_ARRAY:
		return BPF_MAP_TYPE_ARRAY;
	case DT_BPF_MAP_TYPE_PERF_EVENT_ARRAY:
		return BPF_MAP_TYPE_PERF_EVENT_ARRAY;
	case DT_BPF_MAP_TYPE_PERCPU_HASH:
		return BPF_MAP_TYPE_PERCPU_HASH;
	case DT_BPF_MAP_TYPE_PERCPU_ARRAY:
		return BPF_MAP_TYPE_PERCPU_ARRAY;
	case DT_BPF_MAP_TYPE_ARRAY_OF_MAPS:
		return BPF_MAP_TYPE_ARRAY_OF_MAPS;
	case DT_BPF_MAP_TYPE_HASH_OF_MAPS:
		return BPF_MAP_TYPE_HASH_OF_MAPS;
	default:
		return BPF_MAP_TYPE_UNSPEC;
	}
}

static inline enum bpf_prog_type
prog_type_to_linux(dt_bpf_prog_type_t type)
{
	switch (type) {
	case DT_BPF_PROG_TYPE_KPROBE:
		return BPF_PROG_TYPE_KPROBE;
	case DT_BPF_PROG_TYPE_TRACEPOINT:
		return BPF_PROG_TYPE_TRACEPOINT;
	case DT_BPF_PROG_TYPE_RAW_TRACEPOINT:
		return BPF_PROG_TYPE_RAW_TRACEPOINT;
	case DT_BPF_PROG_TYPE_TRACING:
		return BPF_PROG_TYPE_TRACING;
	default:
		return BPF_PROG_TYPE_UNSPEC;
	}
}

static inline enum bpf_attach_type
attach_type_to_linux(dt_bpf_attach_type_t type)
{
	switch (type) {
	case DT_BPF_TRACE_FENTRY:
		return BPF_TRACE_FENTRY;
	case DT_BPF_TRACE_FEXIT:
		return BPF_TRACE_FEXIT;
	case DT_BPF_TRACE_RAW_TP:
		return BPF_TRACE_RAW_TP;
	default:
		return 0;
	}
}

/*
 * Low-level BPF syscall wrapper
 */
static int
linux_bpf_syscall(enum bpf_cmd cmd, union bpf_attr *attr)
{
	int rc;

	rc = syscall(__NR_bpf, cmd, attr, sizeof(union bpf_attr));
	return rc >= 0 ? rc : -errno;
}

/*
 * Backend initialization
 */
static int
linux_backend_init(void *ctx)
{
	/* Nothing special to initialize for Linux backend */
	return 0;
}

static void
linux_backend_fini(void *ctx)
{
	/* Nothing special to clean up for Linux backend */
}

/*
 * Map operations
 */
static dt_bpf_map_t
linux_map_create(dt_bpf_map_type_t type, const char *name,
		 uint32_t key_size, uint32_t value_size,
		 uint32_t max_entries, uint32_t flags)
{
	union bpf_attr attr;

	memset(&attr, 0, sizeof(attr));
	attr.map_type = map_type_to_linux(type);
	attr.key_size = key_size;
	attr.value_size = value_size;
	attr.max_entries = max_entries;
	attr.map_flags = flags;
	if (name) {
		size_t len = strlen(name);
		if (len > sizeof(attr.map_name) - 1)
			len = sizeof(attr.map_name) - 1;
		memcpy(attr.map_name, name, len);
	}

	return linux_bpf_syscall(BPF_MAP_CREATE, &attr);
}

static int
linux_map_lookup(dt_bpf_map_t map, const void *key, void *value)
{
	union bpf_attr attr;

	memset(&attr, 0, sizeof(attr));
	attr.map_fd = map;
	attr.key = (uint64_t)(unsigned long)key;
	attr.value = (uint64_t)(unsigned long)value;

	return linux_bpf_syscall(BPF_MAP_LOOKUP_ELEM, &attr);
}

static int
linux_map_update(dt_bpf_map_t map, const void *key, const void *value,
		 uint32_t flags)
{
	union bpf_attr attr;

	memset(&attr, 0, sizeof(attr));
	attr.map_fd = map;
	attr.key = (uint64_t)(unsigned long)key;
	attr.value = (uint64_t)(unsigned long)value;
	attr.flags = flags;

	return linux_bpf_syscall(BPF_MAP_UPDATE_ELEM, &attr);
}

static int
linux_map_delete(dt_bpf_map_t map, const void *key)
{
	union bpf_attr attr;

	memset(&attr, 0, sizeof(attr));
	attr.map_fd = map;
	attr.key = (uint64_t)(unsigned long)key;

	return linux_bpf_syscall(BPF_MAP_DELETE_ELEM, &attr);
}

static int
linux_map_next_key(dt_bpf_map_t map, const void *key, void *next_key)
{
	union bpf_attr attr;

	memset(&attr, 0, sizeof(attr));
	attr.map_fd = map;
	attr.key = (uint64_t)(unsigned long)key;
	attr.next_key = (uint64_t)(unsigned long)next_key;

	return linux_bpf_syscall(BPF_MAP_GET_NEXT_KEY, &attr);
}

static int
linux_map_close(dt_bpf_map_t map)
{
	return close(map);
}

static dt_bpf_map_t
linux_map_create_meta(dt_bpf_map_type_t outer_type, const char *name,
		      uint32_t outer_key_size, uint32_t outer_max_entries,
		      uint32_t outer_flags, dt_bpf_map_type_t inner_type,
		      uint32_t inner_key_size, uint32_t inner_value_size,
		      uint32_t inner_max_entries, uint32_t inner_flags)
{
	union bpf_attr attr;
	int inner_fd, outer_fd;

	/* Create temporary inner map as template */
	memset(&attr, 0, sizeof(attr));
	attr.map_type = map_type_to_linux(inner_type);
	attr.key_size = inner_key_size;
	attr.value_size = inner_value_size;
	attr.max_entries = inner_max_entries;
	attr.map_flags = inner_flags;

	inner_fd = linux_bpf_syscall(BPF_MAP_CREATE, &attr);
	if (inner_fd < 0)
		return inner_fd;

	/* Create the map-of-maps */
	memset(&attr, 0, sizeof(attr));
	attr.map_type = map_type_to_linux(outer_type);
	attr.key_size = outer_key_size;
	attr.value_size = sizeof(uint32_t);
	attr.inner_map_fd = inner_fd;
	attr.max_entries = outer_max_entries;
	attr.map_flags = outer_flags;
	if (name) {
		size_t len = strlen(name);
		if (len > sizeof(attr.map_name) - 1)
			len = sizeof(attr.map_name) - 1;
		memcpy(attr.map_name, name, len);
	}

	outer_fd = linux_bpf_syscall(BPF_MAP_CREATE, &attr);

	/* Done with the template map */
	close(inner_fd);

	return outer_fd;
}

static dt_bpf_map_t
linux_map_get_fd_by_id(uint32_t id)
{
	union bpf_attr attr;

	memset(&attr, 0, sizeof(attr));
	attr.map_id = id;

	return linux_bpf_syscall(BPF_MAP_GET_FD_BY_ID, &attr);
}

/*
 * Program operations
 */
static dt_bpf_prog_t
linux_prog_load(dt_bpf_prog_type_t type, dt_bpf_attach_type_t attach_type,
		const dt_bpf_insn_t *insns, uint32_t insn_cnt,
		const char *license, uint32_t log_level,
		char *log_buf, size_t log_buf_size)
{
	union bpf_attr attr;
	int fd;
	int i = 0;

	memset(&attr, 0, sizeof(attr));
	attr.prog_type = prog_type_to_linux(type);
	attr.expected_attach_type = attach_type_to_linux(attach_type);
	attr.insn_cnt = insn_cnt;
	attr.insns = (uint64_t)insns;
	attr.license = (uint64_t)license;
	attr.log_level = log_level;

	if (log_level > 0) {
		attr.log_buf = (uint64_t)log_buf;
		attr.log_size = log_buf_size;
	}

	/* Syscall could return EAGAIN - try at most 5 times */
	do {
		fd = linux_bpf_syscall(BPF_PROG_LOAD, &attr);
	} while (fd == -EAGAIN && ++i < 5);

	return fd;
}

static int
linux_prog_close(dt_bpf_prog_t prog)
{
	return close(prog);
}

/*
 * Program execution - not applicable for Linux kernel backend
 * These are no-ops since the kernel executes the programs
 */
static uint64_t
linux_prog_exec(dt_bpf_prog_t prog, void *mem, size_t mem_len)
{
	/* Linux kernel executes BPF programs, not userspace */
	errno = ENOTSUP;
	return (uint64_t)-1;
}

static int
linux_prog_exec_with_mbuff(dt_bpf_prog_t prog, void *mem, size_t mem_len,
			   void *mbuff, size_t mbuff_len, uint64_t *result)
{
	/* Linux kernel executes BPF programs, not userspace */
	errno = ENOTSUP;
	return -1;
}

static int
linux_prog_jit_compile(dt_bpf_prog_t prog)
{
	/* JIT is handled by the kernel */
	return 0;
}

static uint64_t
linux_prog_exec_jit(dt_bpf_prog_t prog, void *mem, size_t mem_len)
{
	/* Linux kernel executes BPF programs, not userspace */
	errno = ENOTSUP;
	return (uint64_t)-1;
}

/*
 * Helper registration - not applicable for Linux kernel backend
 */
static int
linux_register_helper(uint32_t helper_id, dt_bpf_helper_fn fn)
{
	/* Helpers are built into the kernel */
	return 0;
}

/*
 * BTF operations
 */
static int
linux_btf_get_fd_by_id(uint32_t id)
{
	union bpf_attr attr;

	memset(&attr, 0, sizeof(attr));
	attr.btf_id = id;

	return linux_bpf_syscall(BPF_BTF_GET_FD_BY_ID, &attr);
}

static int
linux_btf_get_next_id(uint32_t curr, uint32_t *next)
{
	union bpf_attr attr;
	int rc;

	memset(&attr, 0, sizeof(attr));
	attr.start_id = curr;

	rc = linux_bpf_syscall(BPF_BTF_GET_NEXT_ID, &attr);
	if (rc == 0)
		*next = attr.next_id;

	return rc;
}

static int
linux_btf_get_info_by_fd(int fd, void *info, uint32_t *size)
{
	union bpf_attr attr;
	int rc;

	memset(&attr, 0, sizeof(attr));
	attr.info.bpf_fd = fd;
	attr.info.info = (uint64_t)info;
	attr.info.info_len = *size;

	rc = linux_bpf_syscall(BPF_OBJ_GET_INFO_BY_FD, &attr);
	if (rc == 0)
		*size = attr.info.info_len;

	return rc;
}

/*
 * Tracing attachment
 */
static int
linux_raw_tracepoint_open(const char *name, dt_bpf_prog_t prog)
{
	union bpf_attr attr;

	memset(&attr, 0, sizeof(attr));
	attr.raw_tracepoint.name = (uint64_t)(unsigned long)name;
	attr.raw_tracepoint.prog_fd = prog;

	return linux_bpf_syscall(BPF_RAW_TRACEPOINT_OPEN, &attr);
}

/*
 * Perf event operations
 */
static int
linux_perf_event_open(void *attr, int pid, int cpu,
		      int group_fd, unsigned long flags)
{
	int rc;

	rc = syscall(__NR_perf_event_open, attr, pid, cpu, group_fd,
		     flags | PERF_FLAG_FD_CLOEXEC);
	return rc >= 0 ? rc : -errno;
}

/*
 * Linux backend operations structure
 */
static const dt_bpf_backend_ops_t linux_backend_ops = {
	.type = DT_BPF_BACKEND_LINUX,
	.name = "Linux BPF",

	.init = linux_backend_init,
	.fini = linux_backend_fini,

	.map_create = linux_map_create,
	.map_lookup = linux_map_lookup,
	.map_lookup_ptr = NULL,  /* Not used on Linux - kernel BPF has direct pointers */
	.map_update = linux_map_update,
	.map_delete = linux_map_delete,
	.map_next_key = linux_map_next_key,
	.map_close = linux_map_close,
	.map_create_meta = linux_map_create_meta,
	.map_get_fd_by_id = linux_map_get_fd_by_id,

	.prog_load = linux_prog_load,
	.prog_close = linux_prog_close,
	.prog_exec = linux_prog_exec,
	.prog_exec_with_mbuff = linux_prog_exec_with_mbuff,
	.prog_jit_compile = linux_prog_jit_compile,
	.prog_exec_jit = linux_prog_exec_jit,

	.register_helper = linux_register_helper,

	.btf_get_fd_by_id = linux_btf_get_fd_by_id,
	.btf_get_next_id = linux_btf_get_next_id,
	.btf_get_info_by_fd = linux_btf_get_info_by_fd,

	.raw_tracepoint_open = linux_raw_tracepoint_open,
	.perf_event_open = linux_perf_event_open,
};

/*
 * Get the Linux backend operations
 */
const dt_bpf_backend_ops_t *
dt_bpf_get_linux_backend(void)
{
	return &linux_backend_ops;
}

/*
 * Initialize the Linux backend
 */
int
dt_bpf_backend_init_linux(void)
{
	extern const dt_bpf_backend_ops_t *dt_bpf_backend;
	dt_bpf_backend = &linux_backend_ops;
	return linux_backend_init(NULL);
}

#else /* !__linux__ */

/*
 * Stub implementations for non-Linux platforms
 */
const dt_bpf_backend_ops_t *
dt_bpf_get_linux_backend(void)
{
	return NULL;
}

int
dt_bpf_backend_init_linux(void)
{
	return -1;
}

#endif /* __linux__ */
