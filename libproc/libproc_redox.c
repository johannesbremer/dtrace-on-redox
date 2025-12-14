/*
 * Oracle Linux DTrace - RedoxOS Port
 * Copyright (c) 2025, Oracle and/or its affiliates. All rights reserved.
 * Licensed under the Universal Permissive License v 1.0 as shown at
 * http://oss.oracle.com/licenses/upl.
 *
 * Minimal libproc stubs for RedoxOS
 * Process tracing is not supported on Redox.
 */

#ifdef __redox__

#include <stddef.h>
#include <stdint.h>
#include <errno.h>
#include <sys/types.h>
#include "libproc_redox.h"

/* Basic proc handle functions */
struct ps_prochandle *
Pgrab(pid_t pid, int flags, int ptraced, void *arg, int *perr)
{
	(void)pid;
	(void)flags;
	(void)ptraced;
	(void)arg;
	if (perr)
		*perr = G_NOPROC;
	return NULL;
}

void
Pfree(struct ps_prochandle *P)
{
	(void)P;
}

void
Prelease(struct ps_prochandle *P, int mode)
{
	(void)P;
	(void)mode;
}

int
Pstate(struct ps_prochandle *P)
{
	(void)P;
	return PS_DEAD;
}

const char *
Pgrab_error(int err)
{
	(void)err;
	return "Process control not supported on RedoxOS";
}

pid_t
Pgetpid(struct ps_prochandle *P)
{
	(void)P;
	return -1;
}

/* Address/map lookup functions */
const prmap_t *
Paddr_to_map(struct ps_prochandle *P, uintptr_t addr)
{
	(void)P; (void)addr;
	return NULL;
}

const prmap_t *
Pname_to_map(struct ps_prochandle *P, const char *name)
{
	(void)P; (void)name;
	return NULL;
}

const char *
Pmap_mapfile_name(struct ps_prochandle *P, const prmap_t *map)
{
	(void)P; (void)map;
	return NULL;
}

int
Pxlookup_by_name(struct ps_prochandle *P, Lmid_t lmid, const char *obj,
    const char *name, GElf_Sym *symp, prsyminfo_t *sip)
{
	(void)P; (void)lmid; (void)obj; (void)name; (void)symp; (void)sip;
	return -1;
}

int
Pobject_iter(struct ps_prochandle *P, proc_map_f *func, void *arg)
{
	(void)P; (void)func; (void)arg;
	return 0;
}

int
Pexists(pid_t pid)
{
	(void)pid;
	return 0;
}

void
Pset_procfs_path(const char *path)
{
	(void)path;
}

#endif /* __redox__ */
