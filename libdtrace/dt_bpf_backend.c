/*
 * Oracle Linux DTrace.
 * Copyright (c) 2025, Oracle and/or its affiliates. All rights reserved.
 * Licensed under the Universal Permissive License v 1.0 as shown at
 * http://oss.oracle.com/licenses/upl.
 *
 * BPF Backend Selection and Management
 *
 * This file provides the backend selection logic and global state
 * for the BPF abstraction layer.
 */

#include <errno.h>
#include <stdlib.h>

#include <dt_bpf_backend.h>

/*
 * Global pointer to the currently active backend operations
 */
const dt_bpf_backend_ops_t *dt_bpf_backend = NULL;

/*
 * External backend getter functions
 */
extern const dt_bpf_backend_ops_t *dt_bpf_get_linux_backend(void);
extern const dt_bpf_backend_ops_t *dt_bpf_get_rbpf_backend(void);

/*
 * Detect the best available backend for the current platform
 */
static dt_bpf_backend_type_t
detect_best_backend(void)
{
#if defined(__linux__)
	/*
	 * On Linux, prefer the native kernel BPF backend.
	 * Could add a check here to see if BPF syscalls are available.
	 */
	return DT_BPF_BACKEND_LINUX;
#elif defined(__redox__)
	/*
	 * On RedoxOS, use rbpf user-space VM
	 */
	return DT_BPF_BACKEND_RBPF;
#else
	/*
	 * On other platforms (macOS, BSD, etc.), use rbpf
	 */
	return DT_BPF_BACKEND_RBPF;
#endif
}

/*
 * Select and initialize a specific backend
 */
int
dt_bpf_backend_select(dt_bpf_backend_type_t type)
{
	const dt_bpf_backend_ops_t *new_backend;

	/* If a backend is already active, clean it up first */
	if (dt_bpf_backend != NULL) {
		dt_bpf_backend_cleanup();
	}

	switch (type) {
	case DT_BPF_BACKEND_LINUX:
#if defined(__linux__)
		new_backend = dt_bpf_get_linux_backend();
		break;
#else
		/* Linux backend not available on non-Linux platforms */
		errno = ENOTSUP;
		return -1;
#endif

	case DT_BPF_BACKEND_RBPF:
		new_backend = dt_bpf_get_rbpf_backend();
		break;

	default:
		errno = EINVAL;
		return -1;
	}

	if (new_backend == NULL) {
		errno = ENOTSUP;
		return -1;
	}

	/* Set the global backend pointer */
	dt_bpf_backend = new_backend;

	/* Initialize the backend */
	if (dt_bpf_backend->init != NULL) {
		int rc = dt_bpf_backend->init(NULL);
		if (rc != 0) {
			dt_bpf_backend = NULL;
			return rc;
		}
	}

	return 0;
}

/*
 * Initialize the default backend for the current platform
 */
int
dt_bpf_backend_init_default(void)
{
	dt_bpf_backend_type_t type = detect_best_backend();
	return dt_bpf_backend_select(type);
}

/*
 * Clean up and release the current backend
 */
void
dt_bpf_backend_cleanup(void)
{
	if (dt_bpf_backend != NULL) {
		if (dt_bpf_backend->fini != NULL) {
			dt_bpf_backend->fini(NULL);
		}
		dt_bpf_backend = NULL;
	}
}

/*
 * Get the currently active backend type
 */
dt_bpf_backend_type_t
dt_bpf_backend_get_type(void)
{
	if (dt_bpf_backend == NULL)
		return DT_BPF_BACKEND_LINUX; /* Default */
	return dt_bpf_backend->type;
}

/*
 * Get the name of the currently active backend
 */
const char *
dt_bpf_backend_get_name(void)
{
	if (dt_bpf_backend == NULL)
		return "none";
	return dt_bpf_backend->name;
}

/*
 * Check if a specific backend is available on this platform
 */
int
dt_bpf_backend_available(dt_bpf_backend_type_t type)
{
	switch (type) {
	case DT_BPF_BACKEND_LINUX:
#if defined(__linux__)
		return 1;
#else
		return 0;
#endif

	case DT_BPF_BACKEND_RBPF:
		/* rbpf is always available (it's user-space only) */
		return 1;

	default:
		return 0;
	}
}
