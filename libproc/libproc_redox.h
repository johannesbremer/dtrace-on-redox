/*
 * Oracle Linux DTrace - RedoxOS Port
 * Copyright (c) 2025, Oracle and/or its affiliates. All rights reserved.
 * Licensed under the Universal Permissive License v 1.0 as shown at
 * http://oss.oracle.com/licenses/upl.
 *
 * Minimal libproc interface for RedoxOS
 * Process tracing is not supported - these are stub declarations.
 */

#ifndef _LIBPROC_REDOX_H
#define _LIBPROC_REDOX_H

#include <stdlib.h>
#include <stdint.h>
#include <sys/types.h>
#include <gelf.h>
#include <link.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Opaque process handle - not used on Redox
 */
struct ps_prochandle;
typedef struct ps_prochandle ps_prochandle;

/* State values returned by Pstate() */
#define PS_RUN		1
#define PS_STOP		2
#define PS_TRACESTOP	3
#define PS_DEAD		4

/* Release modes */
#define PS_RELEASE_NORMAL	0
#define PS_RELEASE_KILL		1
#define PS_RELEASE_NO_DETACH	2

/* Grab errors */
#define G_NOERR		0
#define G_NOPROC	1
#define G_NOCORE	2
#define G_NOPROCORCORE	3
#define G_NOEXEC	4
#define G_ZOMB		5
#define G_PERM		6
#define G_BUSY		7
#define G_SYS		8
#define G_SELF		9
#define G_INTR		10
#define G_LP64		11
#define G_FORMAT	12
#define G_ELF		13
#define G_NOTE		14
#define G_STRANGE	15
#define G_ISAINVAL	16
#define G_NOFD		17

/* Object name constants */
#define PR_OBJ_EVERY	((const char *)-1)
#define PR_OBJ_LDSO	((const char *)-2)

/* Lmid constants */
#define PR_LMID_EVERY	((Lmid_t)-1)

/* Symbol table types */
#define PR_SYMTAB	1
#define PR_DYNSYM	2

/* Symbol binding/type flags */
#define BIND_ANY	0x0f
#define TYPE_FUNC	0x10
#define TYPE_OBJECT	0x20

/* Memory map flags */
#define MA_READ		0x04
#define MA_WRITE	0x02
#define MA_EXEC		0x01
#define MA_SHARED	0x08

/*
 * prfile structure - stub for file info
 */
struct prfile {
	struct prmap *first_segment;
	char prf_mapname[64];
};

/*
 * Memory map structure - stub
 */
typedef struct prmap {
	uintptr_t pr_vaddr;
	size_t    pr_size;
	char      pr_mapname[64];
	uint32_t  pr_mflags;
	uint32_t  pr_pagesize;
	struct prfile *pr_file;
	uint64_t  pr_offset;
	uint64_t  pr_dev;      /* device number */
	uint64_t  pr_inum;     /* inode number */
} prmap_t;

/*
 * Symbol info structure - stub
 */
typedef struct prsyminfo {
	uint32_t prs_id;
	Lmid_t   prs_lmid;
	uint16_t prs_table;
} prsyminfo_t;

/*
 * ptrace request enum - stub for compatibility
 */
enum __ptrace_request {
	PTRACE_REQ_NONE = 0
};

/*
 * Callback function types
 */
typedef int proc_sym_f(void *cd, const GElf_Sym *sym, const char *name);
typedef int proc_map_f(void *cd, const prmap_t *map, const char *name);

/*
 * Stub function declarations
 * All return failure since process tracing isn't supported on Redox
 */
struct ps_prochandle *Pgrab(pid_t pid, int flags, int ptraced, void *arg, int *perr);
struct ps_prochandle *Pcreate(const char *file, char *const *argv, void *arg, int *perr);
void Pfree(struct ps_prochandle *P);
void Prelease(struct ps_prochandle *P, int mode);
void Pclose(struct ps_prochandle *P);
int Pstate(struct ps_prochandle *P);
const char *Pgrab_error(int err);
pid_t Pgetpid(struct ps_prochandle *P);
int Psetrun(struct ps_prochandle *P, int sig, int flags);
int Pstop(struct ps_prochandle *P, int msec);
ssize_t Pread(struct ps_prochandle *P, void *buf, size_t size, uintptr_t addr);
ssize_t Pwrite(struct ps_prochandle *P, const void *buf, size_t size, uintptr_t addr);

/* Symbol lookup */
int Plookup_by_name(struct ps_prochandle *P, const char *oname, const char *sname,
		    GElf_Sym *symp);
int Plookup_by_addr(struct ps_prochandle *P, uintptr_t addr, char *buf,
		    size_t size, GElf_Sym *symp);
int Pxlookup_by_name(struct ps_prochandle *P, Lmid_t lmid, const char *oname,
		     const char *sname, GElf_Sym *symp, prsyminfo_t *sip);

/* Map iteration */
const prmap_t *Paddr_to_map(struct ps_prochandle *P, uintptr_t addr);
const prmap_t *Pname_to_map(struct ps_prochandle *P, const char *name);
const prmap_t *Plmid_to_map(struct ps_prochandle *P, Lmid_t lmid, const char *name);
int Pobject_iter(struct ps_prochandle *P, proc_map_f *func, void *cd);
int Psymbol_iter(struct ps_prochandle *P, const char *oname, int type,
		 int bind, proc_sym_f *func, void *cd);

/* Lmid */
int Plmid(struct ps_prochandle *P, uintptr_t addr, Lmid_t *lmidp);

/* Executable name */
char *Pexecname(struct ps_prochandle *P, char *buf, size_t size);
char *Pobjname(struct ps_prochandle *P, uintptr_t addr, char *buf, size_t size);

/* Platform */
const char *Pplatform(struct ps_prochandle *P);

/* Procfs path setting - stub */
void Pset_procfs_path(const char *path);

/* Additional process control functions */
int Punbkpt(struct ps_prochandle *P, uintptr_t addr);
int Pdynamically_linked(struct ps_prochandle *P);
void Pupdate_syms(struct ps_prochandle *P);

/* Run-time linker agent */
typedef struct rd_agent rd_agent_t;
rd_agent_t *Prd_agent(struct ps_prochandle *P);

/* Breakpoint and memory functions */
int Pbkpt(struct ps_prochandle *P, uintptr_t addr, int temp,
	  int (*handler)(struct ps_prochandle *, void *, uintptr_t),
	  void *data, void *dpr);
uintptr_t Pgetauxval(struct ps_prochandle *P, int type);
uintptr_t Pread_first_arg(struct ps_prochandle *P);
int Pwait_internal(struct ps_prochandle *P, int block, int *return_early);

/* ptrace lock hooks */
void Pset_ptrace_lock_hook(void (*hook)(int));
void Pset_waitpid_lock_hook(void (*hook)(int));

/* Map file name */
const char *Pmap_mapfile_name(struct ps_prochandle *P, const prmap_t *pmp);

/* Process existence check */
int Pexists(pid_t pid);

#ifdef __cplusplus
}
#endif

#endif /* _LIBPROC_REDOX_H */
