/*
 * Oracle Linux DTrace.
 * Copyright (c) 2025, Oracle and/or its affiliates. All rights reserved.
 * Licensed under the Universal Permissive License v 1.0 as shown at
 * http://oss.oracle.com/licenses/upl.
 *
 * DTrace BPF Backend Abstraction Layer
 *
 * This header defines an abstraction layer for BPF operations that can be
 * implemented using different backends:
 *   - Linux kernel BPF syscalls (default on Linux)
 *   - rbpf user-space VM (for portability to other OSes like RedoxOS)
 *
 * The abstraction allows DTrace to run eBPF programs without relying on
 * Linux-specific kernel interfaces.
 */

#ifndef _DT_BPF_BACKEND_H
#define _DT_BPF_BACKEND_H

#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 * BPF Backend Types
 */
typedef enum dt_bpf_backend_type {
	DT_BPF_BACKEND_LINUX,	/* Linux kernel BPF syscalls */
	DT_BPF_BACKEND_RBPF,	/* rbpf user-space VM */
} dt_bpf_backend_type_t;

/*
 * BPF Map Types (portable subset)
 */
typedef enum dt_bpf_map_type {
	DT_BPF_MAP_TYPE_HASH = 1,
	DT_BPF_MAP_TYPE_ARRAY = 2,
	DT_BPF_MAP_TYPE_PERF_EVENT_ARRAY = 4,
	DT_BPF_MAP_TYPE_PERCPU_HASH = 5,
	DT_BPF_MAP_TYPE_PERCPU_ARRAY = 6,
	DT_BPF_MAP_TYPE_ARRAY_OF_MAPS = 12,
	DT_BPF_MAP_TYPE_HASH_OF_MAPS = 13,
} dt_bpf_map_type_t;

/*
 * BPF Program Types (portable subset)
 */
typedef enum dt_bpf_prog_type {
	DT_BPF_PROG_TYPE_UNSPEC = 0,
	DT_BPF_PROG_TYPE_KPROBE = 2,
	DT_BPF_PROG_TYPE_TRACEPOINT = 5,
	DT_BPF_PROG_TYPE_RAW_TRACEPOINT = 17,
	DT_BPF_PROG_TYPE_TRACING = 26,
} dt_bpf_prog_type_t;

/*
 * BPF Attach Types (portable subset)
 */
typedef enum dt_bpf_attach_type {
	DT_BPF_ATTACH_TYPE_NONE = 0,
	DT_BPF_TRACE_FENTRY = 15,
	DT_BPF_TRACE_FEXIT = 16,
	DT_BPF_TRACE_RAW_TP = 25,
} dt_bpf_attach_type_t;

/*
 * Map update flags
 */
#define DT_BPF_ANY		0	/* create new or update existing */
#define DT_BPF_NOEXIST		1	/* create new only */
#define DT_BPF_EXIST		2	/* update existing only */

/*
 * BPF instruction format (matches Linux/eBPF)
 */
typedef struct dt_bpf_insn {
	uint8_t		code;		/* opcode */
	uint8_t		dst_reg:4;	/* dest register */
	uint8_t		src_reg:4;	/* source register */
	int16_t		off;		/* signed offset */
	int32_t		imm;		/* signed immediate constant */
} dt_bpf_insn_t;

/*
 * BPF Map Handle
 *
 * On Linux, this is a file descriptor.
 * On rbpf, this is an internal handle to a user-space data structure.
 */
typedef int dt_bpf_map_t;

/*
 * BPF Program Handle
 *
 * On Linux, this is a file descriptor.
 * On rbpf, this is an internal handle to a loaded VM program.
 */
typedef int dt_bpf_prog_t;

/*
 * Helper function signature
 */
typedef uint64_t (*dt_bpf_helper_fn)(uint64_t, uint64_t, uint64_t,
				     uint64_t, uint64_t);

/*
 * BPF Backend Operations Structure
 *
 * This structure contains function pointers for all BPF operations.
 * Different backends implement these operations differently.
 */
typedef struct dt_bpf_backend_ops {
	/* Backend identification */
	dt_bpf_backend_type_t type;
	const char *name;

	/* Initialization and cleanup */
	int (*init)(void *ctx);
	void (*fini)(void *ctx);

	/* Map operations */
	dt_bpf_map_t (*map_create)(dt_bpf_map_type_t type, const char *name,
				   uint32_t key_size, uint32_t value_size,
				   uint32_t max_entries, uint32_t flags);
	int (*map_lookup)(dt_bpf_map_t map, const void *key, void *value);
	int (*map_update)(dt_bpf_map_t map, const void *key, const void *value,
			  uint32_t flags);
	int (*map_delete)(dt_bpf_map_t map, const void *key);
	int (*map_next_key)(dt_bpf_map_t map, const void *key, void *next_key);
	int (*map_close)(dt_bpf_map_t map);

	/* Map-of-maps operations */
	dt_bpf_map_t (*map_create_meta)(dt_bpf_map_type_t outer_type,
					const char *name,
					uint32_t outer_key_size,
					uint32_t outer_max_entries,
					uint32_t outer_flags,
					dt_bpf_map_type_t inner_type,
					uint32_t inner_key_size,
					uint32_t inner_value_size,
					uint32_t inner_max_entries,
					uint32_t inner_flags);
	dt_bpf_map_t (*map_get_fd_by_id)(uint32_t id);

	/* Program operations */
	dt_bpf_prog_t (*prog_load)(dt_bpf_prog_type_t type,
				   dt_bpf_attach_type_t attach_type,
				   const dt_bpf_insn_t *insns,
				   uint32_t insn_cnt,
				   const char *license,
				   uint32_t log_level,
				   char *log_buf,
				   size_t log_buf_size);
	int (*prog_close)(dt_bpf_prog_t prog);

	/* Program execution (for rbpf) */
	uint64_t (*prog_exec)(dt_bpf_prog_t prog, void *mem, size_t mem_len);
	int (*prog_exec_with_mbuff)(dt_bpf_prog_t prog, void *mem, size_t mem_len,
				    void *mbuff, size_t mbuff_len, uint64_t *result);

	/* JIT compilation (for rbpf) */
	int (*prog_jit_compile)(dt_bpf_prog_t prog);
	uint64_t (*prog_exec_jit)(dt_bpf_prog_t prog, void *mem, size_t mem_len);

	/* Helper registration */
	int (*register_helper)(uint32_t helper_id, dt_bpf_helper_fn fn);

	/* BTF operations (Linux-specific, may be no-ops on other backends) */
	int (*btf_get_fd_by_id)(uint32_t id);
	int (*btf_get_next_id)(uint32_t curr, uint32_t *next);
	int (*btf_get_info_by_fd)(int fd, void *info, uint32_t *size);

	/* Tracing attachment (Linux-specific, may be no-ops on other backends) */
	int (*raw_tracepoint_open)(const char *name, dt_bpf_prog_t prog);

	/* Perf event operations (Linux-specific) */
	int (*perf_event_open)(void *attr, int pid, int cpu,
			       int group_fd, unsigned long flags);
} dt_bpf_backend_ops_t;

/*
 * Global backend operations pointer
 */
extern const dt_bpf_backend_ops_t *dt_bpf_backend;

/*
 * Backend initialization functions
 */
int dt_bpf_backend_init_linux(void);
int dt_bpf_backend_init_rbpf(void);

/*
 * Backend selection and initialization
 */
int dt_bpf_backend_select(dt_bpf_backend_type_t type);
void dt_bpf_backend_cleanup(void);

/*
 * Initialize default backend for the current platform
 */
int dt_bpf_backend_init_default(void);

/*
 * Register user-space helper emulations for rbpf backend
 */
int dt_bpf_register_rbpf_helpers(void);

/*
 * Convenience macros for calling backend operations
 */
#define DT_BPF_MAP_CREATE(type, name, ksz, vsz, max, flags) \
	dt_bpf_backend->map_create((type), (name), (ksz), (vsz), (max), (flags))

#define DT_BPF_MAP_LOOKUP(map, key, val) \
	dt_bpf_backend->map_lookup((map), (key), (val))

#define DT_BPF_MAP_UPDATE(map, key, val, flags) \
	dt_bpf_backend->map_update((map), (key), (val), (flags))

#define DT_BPF_MAP_DELETE(map, key) \
	dt_bpf_backend->map_delete((map), (key))

#define DT_BPF_MAP_NEXT_KEY(map, key, next) \
	dt_bpf_backend->map_next_key((map), (key), (next))

#define DT_BPF_MAP_CLOSE(map) \
	dt_bpf_backend->map_close((map))

#define DT_BPF_PROG_LOAD(type, atype, insns, cnt, lic, lvl, buf, sz) \
	dt_bpf_backend->prog_load((type), (atype), (insns), (cnt), \
				  (lic), (lvl), (buf), (sz))

#define DT_BPF_PROG_CLOSE(prog) \
	dt_bpf_backend->prog_close((prog))

#define DT_BPF_PROG_EXEC(prog, mem, len) \
	dt_bpf_backend->prog_exec((prog), (mem), (len))

#ifdef __cplusplus
}
#endif

#endif /* _DT_BPF_BACKEND_H */
