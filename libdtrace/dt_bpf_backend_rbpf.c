/*
 * Oracle Linux DTrace.
 * Copyright (c) 2025, Oracle and/or its affiliates. All rights reserved.
 * Licensed under the Universal Permissive License v 1.0 as shown at
 * http://oss.oracle.com/licenses/upl.
 *
 * rbpf Backend Implementation
 *
 * This file implements the BPF backend operations using rbpf, a user-space
 * eBPF virtual machine written in Rust. This backend enables DTrace to run
 * on systems without Linux kernel BPF support, such as RedoxOS.
 *
 * rbpf provides:
 *   - An interpreter for eBPF programs
 *   - A JIT compiler for x86_64
 *   - A disassembler
 *   - Helper function registration
 *
 * This backend implements maps as user-space data structures and executes
 * BPF programs using rbpf's interpreter or JIT.
 */

#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include <dt_bpf_backend.h>

/*
 * Forward declarations for rbpf FFI bindings
 * These will be provided by a Rust library that wraps rbpf
 */
#ifdef DT_BPF_BACKEND_RBPF

/* External rbpf FFI functions - to be implemented in Rust */
extern void *rbpf_vm_new(const uint8_t *prog, size_t prog_len);
extern void rbpf_vm_destroy(void *vm);
extern int rbpf_vm_register_helper(void *vm, uint32_t idx,
				   uint64_t (*fn)(uint64_t, uint64_t, uint64_t,
						  uint64_t, uint64_t));
extern uint64_t rbpf_vm_exec(void *vm, const uint8_t *mem, size_t mem_len);
extern int rbpf_vm_jit_compile(void *vm);
extern uint64_t rbpf_vm_exec_jit(void *vm, const uint8_t *mem, size_t mem_len);

#endif /* DT_BPF_BACKEND_RBPF */

/*
 * Map implementation using user-space data structures
 */

#define RBPF_MAX_MAPS		256
#define RBPF_MAX_PROGS		256
#define RBPF_MAX_HELPERS	256

typedef struct rbpf_map_entry {
	void		*key;
	void		*value;
	struct rbpf_map_entry *next;
} rbpf_map_entry_t;

typedef struct rbpf_map {
	int			in_use;
	dt_bpf_map_type_t	type;
	char			name[64];
	uint32_t		key_size;
	uint32_t		value_size;
	uint32_t		max_entries;
	uint32_t		flags;
	uint32_t		num_entries;

	/* For hash maps */
	rbpf_map_entry_t	**buckets;
	uint32_t		num_buckets;

	/* For array maps */
	void			*array_data;

	/* For map-of-maps */
	int			inner_map_template;
	uint32_t		inner_key_size;
	uint32_t		inner_value_size;
	uint32_t		inner_max_entries;
} rbpf_map_t;

typedef struct rbpf_prog {
	int			in_use;
	dt_bpf_prog_type_t	type;
	dt_bpf_attach_type_t	attach_type;
	dt_bpf_insn_t		*insns;
	uint32_t		insn_cnt;
	void			*vm;		/* rbpf VM instance */
	int			jit_compiled;
} rbpf_prog_t;

typedef struct rbpf_backend_ctx {
	rbpf_map_t		maps[RBPF_MAX_MAPS];
	rbpf_prog_t		progs[RBPF_MAX_PROGS];
	dt_bpf_helper_fn	helpers[RBPF_MAX_HELPERS];
	int			initialized;
} rbpf_backend_ctx_t;

static rbpf_backend_ctx_t rbpf_ctx;

/*
 * Hash function for map keys
 */
static uint32_t
hash_key(const void *key, uint32_t key_size, uint32_t num_buckets)
{
	const uint8_t *data = key;
	uint32_t hash = 5381;
	uint32_t i;

	for (i = 0; i < key_size; i++)
		hash = ((hash << 5) + hash) + data[i];

	return hash % num_buckets;
}

/*
 * Allocate a map handle
 */
static int
alloc_map_handle(void)
{
	int i;
	for (i = 0; i < RBPF_MAX_MAPS; i++) {
		if (!rbpf_ctx.maps[i].in_use)
			return i;
	}
	return -1;
}

/*
 * Allocate a program handle
 */
static int
alloc_prog_handle(void)
{
	int i;
	for (i = 0; i < RBPF_MAX_PROGS; i++) {
		if (!rbpf_ctx.progs[i].in_use)
			return i;
	}
	return -1;
}

/*
 * Backend initialization
 */
static int
rbpf_backend_init(void *ctx)
{
	memset(&rbpf_ctx, 0, sizeof(rbpf_ctx));
	rbpf_ctx.initialized = 1;
	return 0;
}

static void
rbpf_backend_fini(void *ctx)
{
	int i;

	/* Clean up all maps */
	for (i = 0; i < RBPF_MAX_MAPS; i++) {
		if (rbpf_ctx.maps[i].in_use) {
			rbpf_map_t *map = &rbpf_ctx.maps[i];

			if (map->type == DT_BPF_MAP_TYPE_ARRAY ||
			    map->type == DT_BPF_MAP_TYPE_PERCPU_ARRAY) {
				free(map->array_data);
			} else if (map->buckets) {
				uint32_t j;
				for (j = 0; j < map->num_buckets; j++) {
					rbpf_map_entry_t *entry = map->buckets[j];
					while (entry) {
						rbpf_map_entry_t *next = entry->next;
						free(entry->key);
						free(entry->value);
						free(entry);
						entry = next;
					}
				}
				free(map->buckets);
			}
			map->in_use = 0;
		}
	}

	/* Clean up all programs */
	for (i = 0; i < RBPF_MAX_PROGS; i++) {
		if (rbpf_ctx.progs[i].in_use) {
			rbpf_prog_t *prog = &rbpf_ctx.progs[i];
#ifdef DT_BPF_BACKEND_RBPF
			if (prog->vm)
				rbpf_vm_destroy(prog->vm);
#endif
			free(prog->insns);
			prog->in_use = 0;
		}
	}

	rbpf_ctx.initialized = 0;
}

/*
 * Map operations
 */
static dt_bpf_map_t
rbpf_map_create(dt_bpf_map_type_t type, const char *name,
		uint32_t key_size, uint32_t value_size,
		uint32_t max_entries, uint32_t flags)
{
	int handle;
	rbpf_map_t *map;

	handle = alloc_map_handle();
	if (handle < 0) {
		errno = ENOMEM;
		return -1;
	}

	map = &rbpf_ctx.maps[handle];
	memset(map, 0, sizeof(*map));

	map->in_use = 1;
	map->type = type;
	if (name) {
		strncpy(map->name, name, sizeof(map->name) - 1);
		map->name[sizeof(map->name) - 1] = '\0';
	}
	map->key_size = key_size;
	map->value_size = value_size;
	map->max_entries = max_entries;
	map->flags = flags;

	switch (type) {
	case DT_BPF_MAP_TYPE_ARRAY:
	case DT_BPF_MAP_TYPE_PERCPU_ARRAY:
	case DT_BPF_MAP_TYPE_PERF_EVENT_ARRAY:
		/* Array-based storage */
		map->array_data = calloc(max_entries, value_size);
		if (!map->array_data) {
			map->in_use = 0;
			errno = ENOMEM;
			return -1;
		}
		break;

	case DT_BPF_MAP_TYPE_HASH:
	case DT_BPF_MAP_TYPE_PERCPU_HASH:
		/* Hash table storage */
		map->num_buckets = max_entries < 256 ? max_entries : 256;
		map->buckets = calloc(map->num_buckets, sizeof(rbpf_map_entry_t *));
		if (!map->buckets) {
			map->in_use = 0;
			errno = ENOMEM;
			return -1;
		}
		break;

	case DT_BPF_MAP_TYPE_ARRAY_OF_MAPS:
	case DT_BPF_MAP_TYPE_HASH_OF_MAPS:
		/* Map-of-maps: store map handles as values */
		map->array_data = calloc(max_entries, sizeof(int));
		if (!map->array_data) {
			map->in_use = 0;
			errno = ENOMEM;
			return -1;
		}
		/* Initialize with -1 (invalid handle) */
		memset(map->array_data, 0xFF, max_entries * sizeof(int));
		break;

	default:
		map->in_use = 0;
		errno = EINVAL;
		return -1;
	}

	return handle;
}

static int
rbpf_map_lookup(dt_bpf_map_t handle, const void *key, void *value)
{
	rbpf_map_t *map;
	uint32_t idx;

	if (handle < 0 || handle >= RBPF_MAX_MAPS ||
	    !rbpf_ctx.maps[handle].in_use) {
		errno = EBADF;
		return -1;
	}

	map = &rbpf_ctx.maps[handle];

	switch (map->type) {
	case DT_BPF_MAP_TYPE_ARRAY:
	case DT_BPF_MAP_TYPE_PERCPU_ARRAY:
	case DT_BPF_MAP_TYPE_PERF_EVENT_ARRAY:
	case DT_BPF_MAP_TYPE_ARRAY_OF_MAPS:
		if (map->key_size != sizeof(uint32_t)) {
			errno = EINVAL;
			return -1;
		}
		idx = *(const uint32_t *)key;
		if (idx >= map->max_entries) {
			errno = ENOENT;
			return -1;
		}
		memcpy(value, (char *)map->array_data + idx * map->value_size,
		       map->value_size);
		return 0;

	case DT_BPF_MAP_TYPE_HASH:
	case DT_BPF_MAP_TYPE_PERCPU_HASH:
	case DT_BPF_MAP_TYPE_HASH_OF_MAPS: {
		uint32_t bucket = hash_key(key, map->key_size, map->num_buckets);
		rbpf_map_entry_t *entry = map->buckets[bucket];

		while (entry) {
			if (memcmp(entry->key, key, map->key_size) == 0) {
				memcpy(value, entry->value, map->value_size);
				return 0;
			}
			entry = entry->next;
		}
		errno = ENOENT;
		return -1;
	}

	default:
		errno = EINVAL;
		return -1;
	}
}

static int
rbpf_map_update(dt_bpf_map_t handle, const void *key, const void *value,
		uint32_t flags)
{
	rbpf_map_t *map;
	uint32_t idx;

	if (handle < 0 || handle >= RBPF_MAX_MAPS ||
	    !rbpf_ctx.maps[handle].in_use) {
		errno = EBADF;
		return -1;
	}

	map = &rbpf_ctx.maps[handle];

	switch (map->type) {
	case DT_BPF_MAP_TYPE_ARRAY:
	case DT_BPF_MAP_TYPE_PERCPU_ARRAY:
	case DT_BPF_MAP_TYPE_PERF_EVENT_ARRAY:
	case DT_BPF_MAP_TYPE_ARRAY_OF_MAPS:
		if (map->key_size != sizeof(uint32_t)) {
			errno = EINVAL;
			return -1;
		}
		idx = *(const uint32_t *)key;
		if (idx >= map->max_entries) {
			errno = E2BIG;
			return -1;
		}
		memcpy((char *)map->array_data + idx * map->value_size,
		       value, map->value_size);
		return 0;

	case DT_BPF_MAP_TYPE_HASH:
	case DT_BPF_MAP_TYPE_PERCPU_HASH:
	case DT_BPF_MAP_TYPE_HASH_OF_MAPS: {
		uint32_t bucket = hash_key(key, map->key_size, map->num_buckets);
		rbpf_map_entry_t *entry = map->buckets[bucket];
		rbpf_map_entry_t *prev = NULL;

		/* Look for existing entry */
		while (entry) {
			if (memcmp(entry->key, key, map->key_size) == 0) {
				if (flags == DT_BPF_NOEXIST) {
					errno = EEXIST;
					return -1;
				}
				memcpy(entry->value, value, map->value_size);
				return 0;
			}
			prev = entry;
			entry = entry->next;
		}

		/* Entry not found */
		if (flags == DT_BPF_EXIST) {
			errno = ENOENT;
			return -1;
		}

		/* Check max entries */
		if (map->num_entries >= map->max_entries) {
			errno = E2BIG;
			return -1;
		}

		/* Create new entry */
		entry = malloc(sizeof(*entry));
		if (!entry) {
			errno = ENOMEM;
			return -1;
		}
		entry->key = malloc(map->key_size);
		entry->value = malloc(map->value_size);
		if (!entry->key || !entry->value) {
			free(entry->key);
			free(entry->value);
			free(entry);
			errno = ENOMEM;
			return -1;
		}
		memcpy(entry->key, key, map->key_size);
		memcpy(entry->value, value, map->value_size);
		entry->next = NULL;

		if (prev)
			prev->next = entry;
		else
			map->buckets[bucket] = entry;

		map->num_entries++;
		return 0;
	}

	default:
		errno = EINVAL;
		return -1;
	}
}

static int
rbpf_map_delete(dt_bpf_map_t handle, const void *key)
{
	rbpf_map_t *map;

	if (handle < 0 || handle >= RBPF_MAX_MAPS ||
	    !rbpf_ctx.maps[handle].in_use) {
		errno = EBADF;
		return -1;
	}

	map = &rbpf_ctx.maps[handle];

	switch (map->type) {
	case DT_BPF_MAP_TYPE_ARRAY:
	case DT_BPF_MAP_TYPE_PERCPU_ARRAY:
	case DT_BPF_MAP_TYPE_PERF_EVENT_ARRAY:
	case DT_BPF_MAP_TYPE_ARRAY_OF_MAPS:
		/* Arrays don't support delete */
		errno = EINVAL;
		return -1;

	case DT_BPF_MAP_TYPE_HASH:
	case DT_BPF_MAP_TYPE_PERCPU_HASH:
	case DT_BPF_MAP_TYPE_HASH_OF_MAPS: {
		uint32_t bucket = hash_key(key, map->key_size, map->num_buckets);
		rbpf_map_entry_t *entry = map->buckets[bucket];
		rbpf_map_entry_t *prev = NULL;

		while (entry) {
			if (memcmp(entry->key, key, map->key_size) == 0) {
				if (prev)
					prev->next = entry->next;
				else
					map->buckets[bucket] = entry->next;
				free(entry->key);
				free(entry->value);
				free(entry);
				map->num_entries--;
				return 0;
			}
			prev = entry;
			entry = entry->next;
		}
		errno = ENOENT;
		return -1;
	}

	default:
		errno = EINVAL;
		return -1;
	}
}

static int
rbpf_map_next_key(dt_bpf_map_t handle, const void *key, void *next_key)
{
	rbpf_map_t *map;

	if (handle < 0 || handle >= RBPF_MAX_MAPS ||
	    !rbpf_ctx.maps[handle].in_use) {
		errno = EBADF;
		return -1;
	}

	map = &rbpf_ctx.maps[handle];

	switch (map->type) {
	case DT_BPF_MAP_TYPE_ARRAY:
	case DT_BPF_MAP_TYPE_PERCPU_ARRAY:
	case DT_BPF_MAP_TYPE_PERF_EVENT_ARRAY:
	case DT_BPF_MAP_TYPE_ARRAY_OF_MAPS: {
		uint32_t idx;
		if (key == NULL) {
			idx = 0;
		} else {
			idx = *(const uint32_t *)key + 1;
		}
		if (idx >= map->max_entries) {
			errno = ENOENT;
			return -1;
		}
		*(uint32_t *)next_key = idx;
		return 0;
	}

	case DT_BPF_MAP_TYPE_HASH:
	case DT_BPF_MAP_TYPE_PERCPU_HASH:
	case DT_BPF_MAP_TYPE_HASH_OF_MAPS: {
		uint32_t start_bucket = 0;
		rbpf_map_entry_t *start_entry = NULL;
		uint32_t i;

		if (key != NULL) {
			/* Find current entry */
			uint32_t bucket = hash_key(key, map->key_size,
						   map->num_buckets);
			rbpf_map_entry_t *entry = map->buckets[bucket];

			while (entry) {
				if (memcmp(entry->key, key, map->key_size) == 0) {
					if (entry->next) {
						memcpy(next_key, entry->next->key,
						       map->key_size);
						return 0;
					}
					/* Move to next bucket */
					start_bucket = bucket + 1;
					break;
				}
				entry = entry->next;
			}
			if (!entry) {
				errno = ENOENT;
				return -1;
			}
		}

		/* Find next entry in buckets */
		for (i = start_bucket; i < map->num_buckets; i++) {
			if (map->buckets[i]) {
				memcpy(next_key, map->buckets[i]->key,
				       map->key_size);
				return 0;
			}
		}
		errno = ENOENT;
		return -1;
	}

	default:
		errno = EINVAL;
		return -1;
	}
}

static int
rbpf_map_close(dt_bpf_map_t handle)
{
	rbpf_map_t *map;

	if (handle < 0 || handle >= RBPF_MAX_MAPS ||
	    !rbpf_ctx.maps[handle].in_use) {
		errno = EBADF;
		return -1;
	}

	map = &rbpf_ctx.maps[handle];

	if (map->array_data) {
		free(map->array_data);
		map->array_data = NULL;
	}

	if (map->buckets) {
		uint32_t i;
		for (i = 0; i < map->num_buckets; i++) {
			rbpf_map_entry_t *entry = map->buckets[i];
			while (entry) {
				rbpf_map_entry_t *next = entry->next;
				free(entry->key);
				free(entry->value);
				free(entry);
				entry = next;
			}
		}
		free(map->buckets);
		map->buckets = NULL;
	}

	map->in_use = 0;
	return 0;
}

static dt_bpf_map_t
rbpf_map_create_meta(dt_bpf_map_type_t outer_type, const char *name,
		     uint32_t outer_key_size, uint32_t outer_max_entries,
		     uint32_t outer_flags, dt_bpf_map_type_t inner_type,
		     uint32_t inner_key_size, uint32_t inner_value_size,
		     uint32_t inner_max_entries, uint32_t inner_flags)
{
	dt_bpf_map_t handle;
	rbpf_map_t *map;

	/* Create outer map that stores map handles */
	handle = rbpf_map_create(outer_type, name, outer_key_size,
				 sizeof(int), outer_max_entries, outer_flags);
	if (handle < 0)
		return handle;

	/* Store inner map template info for creating new inner maps */
	map = &rbpf_ctx.maps[handle];
	map->inner_key_size = inner_key_size;
	map->inner_value_size = inner_value_size;
	map->inner_max_entries = inner_max_entries;

	return handle;
}

static dt_bpf_map_t
rbpf_map_get_fd_by_id(uint32_t id)
{
	/* In rbpf, map ID == handle, verify it's valid */
	if (id < RBPF_MAX_MAPS && rbpf_ctx.maps[id].in_use)
		return id;
	errno = ENOENT;
	return -1;
}

/*
 * Program operations
 */
static dt_bpf_prog_t
rbpf_prog_load(dt_bpf_prog_type_t type, dt_bpf_attach_type_t attach_type,
	       const dt_bpf_insn_t *insns, uint32_t insn_cnt,
	       const char *license, uint32_t log_level,
	       char *log_buf, size_t log_buf_size)
{
	int handle;
	rbpf_prog_t *prog;

	handle = alloc_prog_handle();
	if (handle < 0) {
		errno = ENOMEM;
		if (log_buf && log_buf_size > 0)
			snprintf(log_buf, log_buf_size, "No free program slots");
		return -1;
	}

	prog = &rbpf_ctx.progs[handle];
	memset(prog, 0, sizeof(*prog));

	prog->in_use = 1;
	prog->type = type;
	prog->attach_type = attach_type;
	prog->insn_cnt = insn_cnt;

	/* Copy instructions */
	prog->insns = malloc(insn_cnt * sizeof(dt_bpf_insn_t));
	if (!prog->insns) {
		prog->in_use = 0;
		errno = ENOMEM;
		if (log_buf && log_buf_size > 0)
			snprintf(log_buf, log_buf_size, "Out of memory");
		return -1;
	}
	memcpy(prog->insns, insns, insn_cnt * sizeof(dt_bpf_insn_t));

#ifdef DT_BPF_BACKEND_RBPF
	/* Create rbpf VM instance */
	prog->vm = rbpf_vm_new((const uint8_t *)prog->insns,
			       insn_cnt * sizeof(dt_bpf_insn_t));
	if (!prog->vm) {
		free(prog->insns);
		prog->in_use = 0;
		errno = EINVAL;
		if (log_buf && log_buf_size > 0)
			snprintf(log_buf, log_buf_size, "Failed to create rbpf VM");
		return -1;
	}

	/* Register helpers */
	for (int i = 0; i < RBPF_MAX_HELPERS; i++) {
		if (rbpf_ctx.helpers[i])
			rbpf_vm_register_helper(prog->vm, i, rbpf_ctx.helpers[i]);
	}
#endif

	return handle;
}

static int
rbpf_prog_close(dt_bpf_prog_t handle)
{
	rbpf_prog_t *prog;

	if (handle < 0 || handle >= RBPF_MAX_PROGS ||
	    !rbpf_ctx.progs[handle].in_use) {
		errno = EBADF;
		return -1;
	}

	prog = &rbpf_ctx.progs[handle];

#ifdef DT_BPF_BACKEND_RBPF
	if (prog->vm)
		rbpf_vm_destroy(prog->vm);
#endif

	free(prog->insns);
	prog->in_use = 0;

	return 0;
}

static uint64_t
rbpf_prog_exec(dt_bpf_prog_t handle, void *mem, size_t mem_len)
{
	rbpf_prog_t *prog;

	if (handle < 0 || handle >= RBPF_MAX_PROGS ||
	    !rbpf_ctx.progs[handle].in_use) {
		errno = EBADF;
		return (uint64_t)-1;
	}

	prog = &rbpf_ctx.progs[handle];

#ifdef DT_BPF_BACKEND_RBPF
	if (!prog->vm) {
		errno = EINVAL;
		return (uint64_t)-1;
	}

	return rbpf_vm_exec(prog->vm, (const uint8_t *)mem, mem_len);
#else
	errno = ENOTSUP;
	return (uint64_t)-1;
#endif
}

static int
rbpf_prog_exec_with_mbuff(dt_bpf_prog_t handle, void *mem, size_t mem_len,
			  void *mbuff, size_t mbuff_len, uint64_t *result)
{
	/* For rbpf, we use EbpfVmMbuff or EbpfVmFixedMbuff */
	/* This is a simplified version - full implementation needs
	 * proper metadata buffer handling */
	*result = rbpf_prog_exec(handle, mem, mem_len);
	return (*result == (uint64_t)-1 && errno != 0) ? -1 : 0;
}

static int
rbpf_prog_jit_compile(dt_bpf_prog_t handle)
{
	rbpf_prog_t *prog;

	if (handle < 0 || handle >= RBPF_MAX_PROGS ||
	    !rbpf_ctx.progs[handle].in_use) {
		errno = EBADF;
		return -1;
	}

	prog = &rbpf_ctx.progs[handle];

#ifdef DT_BPF_BACKEND_RBPF
	if (!prog->vm) {
		errno = EINVAL;
		return -1;
	}

	if (rbpf_vm_jit_compile(prog->vm) < 0) {
		errno = EINVAL;
		return -1;
	}

	prog->jit_compiled = 1;
	return 0;
#else
	errno = ENOTSUP;
	return -1;
#endif
}

static uint64_t
rbpf_prog_exec_jit(dt_bpf_prog_t handle, void *mem, size_t mem_len)
{
	rbpf_prog_t *prog;

	if (handle < 0 || handle >= RBPF_MAX_PROGS ||
	    !rbpf_ctx.progs[handle].in_use) {
		errno = EBADF;
		return (uint64_t)-1;
	}

	prog = &rbpf_ctx.progs[handle];

#ifdef DT_BPF_BACKEND_RBPF
	if (!prog->vm || !prog->jit_compiled) {
		errno = EINVAL;
		return (uint64_t)-1;
	}

	return rbpf_vm_exec_jit(prog->vm, (const uint8_t *)mem, mem_len);
#else
	errno = ENOTSUP;
	return (uint64_t)-1;
#endif
}

/*
 * Helper registration
 */
static int
rbpf_register_helper(uint32_t helper_id, dt_bpf_helper_fn fn)
{
	if (helper_id >= RBPF_MAX_HELPERS) {
		errno = EINVAL;
		return -1;
	}

	rbpf_ctx.helpers[helper_id] = fn;
	return 0;
}

/*
 * BTF operations - not applicable for rbpf
 */
static int
rbpf_btf_get_fd_by_id(uint32_t id)
{
	errno = ENOTSUP;
	return -1;
}

static int
rbpf_btf_get_next_id(uint32_t curr, uint32_t *next)
{
	errno = ENOTSUP;
	return -1;
}

static int
rbpf_btf_get_info_by_fd(int fd, void *info, uint32_t *size)
{
	errno = ENOTSUP;
	return -1;
}

/*
 * Tracing attachment - not applicable for rbpf
 */
static int
rbpf_raw_tracepoint_open(const char *name, dt_bpf_prog_t prog)
{
	/*
	 * In rbpf mode, we don't attach to kernel tracepoints.
	 * Instead, programs are executed directly by the user-space VM.
	 * This function returns a pseudo-handle for compatibility.
	 */
	if (prog < 0 || prog >= RBPF_MAX_PROGS ||
	    !rbpf_ctx.progs[prog].in_use) {
		errno = EBADF;
		return -1;
	}

	/* Return the program handle as the "tracepoint" handle */
	return prog;
}

/*
 * Perf event operations - not applicable for rbpf
 */
static int
rbpf_perf_event_open(void *attr, int pid, int cpu,
		     int group_fd, unsigned long flags)
{
	errno = ENOTSUP;
	return -1;
}

/*
 * rbpf backend operations structure
 */
static const dt_bpf_backend_ops_t rbpf_backend_ops = {
	.type = DT_BPF_BACKEND_RBPF,
	.name = "rbpf (user-space VM)",

	.init = rbpf_backend_init,
	.fini = rbpf_backend_fini,

	.map_create = rbpf_map_create,
	.map_lookup = rbpf_map_lookup,
	.map_update = rbpf_map_update,
	.map_delete = rbpf_map_delete,
	.map_next_key = rbpf_map_next_key,
	.map_close = rbpf_map_close,
	.map_create_meta = rbpf_map_create_meta,
	.map_get_fd_by_id = rbpf_map_get_fd_by_id,

	.prog_load = rbpf_prog_load,
	.prog_close = rbpf_prog_close,
	.prog_exec = rbpf_prog_exec,
	.prog_exec_with_mbuff = rbpf_prog_exec_with_mbuff,
	.prog_jit_compile = rbpf_prog_jit_compile,
	.prog_exec_jit = rbpf_prog_exec_jit,

	.register_helper = rbpf_register_helper,

	.btf_get_fd_by_id = rbpf_btf_get_fd_by_id,
	.btf_get_next_id = rbpf_btf_get_next_id,
	.btf_get_info_by_fd = rbpf_btf_get_info_by_fd,

	.raw_tracepoint_open = rbpf_raw_tracepoint_open,
	.perf_event_open = rbpf_perf_event_open,
};

/*
 * Get the rbpf backend operations
 */
const dt_bpf_backend_ops_t *
dt_bpf_get_rbpf_backend(void)
{
	return &rbpf_backend_ops;
}

/*
 * Initialize the rbpf backend
 */
int
dt_bpf_backend_init_rbpf(void)
{
	extern const dt_bpf_backend_ops_t *dt_bpf_backend;
	dt_bpf_backend = &rbpf_backend_ops;
	return rbpf_backend_init(NULL);
}
