/*
 * Oracle Linux DTrace - RedoxOS Port
 * Copyright (c) 2025, Oracle and/or its affiliates. All rights reserved.
 * Licensed under the Universal Permissive License v 1.0 as shown at
 * http://oss.oracle.com/licenses/upl.
 *
 * Stub functions for features not available on RedoxOS
 */

#ifdef __redox__

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <pthread.h>
#include <dt_impl.h>
#include <dt_proc.h>
#include <dt_program.h>

/* Large file support - Redox uses standard open() */
int open64(const char *path, int flags, ...)
{
	return open(path, flags);
}

/* dt_proc.c stubs - process tracking not supported */
void dt_proc_hash_create(dtrace_hdl_t *dtp)
{
	/*
	 * Allocate a minimal proc hash structure so dt_open.c checks pass.
	 * Process tracking isn't supported on Redox.
	 */
	dtp->dt_procs = calloc(1, sizeof(dt_proc_hash_t));
	if (dtp->dt_procs != NULL) {
		pthread_mutex_init(&dtp->dt_procs->dph_lock, NULL);
		dtp->dt_procs->dph_hashlen = 1;
		dtp->dt_procs->dph_lrulim = 8;
	}
}

void dt_proc_hash_destroy(dtrace_hdl_t *dtp)
{
	if (dtp->dt_procs != NULL) {
		pthread_mutex_destroy(&dtp->dt_procs->dph_lock);
		free(dtp->dt_procs);
		dtp->dt_procs = NULL;
	}
}

void dt_proc_signal_init(dtrace_hdl_t *dtp)
{
	(void)dtp;
}

void dt_proc_signal_fini(dtrace_hdl_t *dtp)
{
	(void)dtp;
}

pid_t dt_proc_grab_lock(dtrace_hdl_t *dtp, pid_t pid, int flags)
{
	(void)dtp; (void)pid; (void)flags;
	return -1;
}

void dt_proc_release_unlock(dtrace_hdl_t *dtp, pid_t pid)
{
	(void)dtp; (void)pid;
}

dt_proc_t *dt_proc_lookup(dtrace_hdl_t *dtp, pid_t pid)
{
	(void)dtp; (void)pid;
	return NULL;
}

/* dt_P* proxies for libproc operations */
int dt_Plookup_by_addr(dtrace_hdl_t *dtp, pid_t pid, uintptr_t addr,
    const char **namep, GElf_Sym *symp)
{
	(void)dtp; (void)pid; (void)addr; (void)namep; (void)symp;
	return -1;
}

const prmap_t *dt_Paddr_to_map(dtrace_hdl_t *dtp, pid_t pid, uintptr_t addr)
{
	(void)dtp; (void)pid; (void)addr;
	return NULL;
}

const prmap_t *dt_Plmid_to_map(dtrace_hdl_t *dtp, pid_t pid, Lmid_t lmid,
    const char *name)
{
	(void)dtp; (void)pid; (void)lmid; (void)name;
	return NULL;
}

const prmap_t *dt_Pname_to_map(dtrace_hdl_t *dtp, pid_t pid, const char *name)
{
	(void)dtp; (void)pid; (void)name;
	return NULL;
}

char *dt_Pobjname(dtrace_hdl_t *dtp, pid_t pid, uintptr_t addr,
    char *buf, size_t len)
{
	(void)dtp; (void)pid; (void)addr; (void)buf; (void)len;
	return NULL;
}

int dt_Plmid(dtrace_hdl_t *dtp, pid_t pid, uintptr_t addr, Lmid_t *lmid)
{
	(void)dtp; (void)pid; (void)addr; (void)lmid;
	return -1;
}

int dt_Pstate(dtrace_hdl_t *dtp, pid_t pid)
{
	(void)dtp; (void)pid;
	return PS_DEAD;
}

int dt_Pxlookup_by_name(dtrace_hdl_t *dtp, pid_t pid, Lmid_t lmid,
    const char *obj, const char *name, GElf_Sym *symp, prsyminfo_t *sip)
{
	(void)dtp; (void)pid; (void)lmid; (void)obj; (void)name;
	(void)symp; (void)sip;
	return -1;
}

int dt_Pwritable_mapping(dtrace_hdl_t *dtp, pid_t pid, uintptr_t addr)
{
	(void)dtp; (void)pid; (void)addr;
	return 0;
}

int dt_Psymbol_iter_by_addr(dtrace_hdl_t *dtp, pid_t pid, const char *obj,
    int which, int mask, proc_sym_f *func, void *arg)
{
	(void)dtp; (void)pid; (void)obj; (void)which; (void)mask;
	(void)func; (void)arg;
	return 0;
}

int dt_Pobject_iter(dtrace_hdl_t *dtp, pid_t pid, proc_map_f *func, void *arg)
{
	(void)dtp; (void)pid; (void)func; (void)arg;
	return 0;
}

ssize_t dt_Pread(dtrace_hdl_t *dtp, pid_t pid, void *buf, size_t len,
    uintptr_t addr)
{
	(void)dtp; (void)pid; (void)buf; (void)len; (void)addr;
	return -1;
}

/* dt_btf.c stubs - BTF type format not available on Redox */
int dt_btf_load_module(dtrace_hdl_t *dtp, void *dmp)
{
	(void)dtp; (void)dmp;
	return 0;
}

void dt_btf_destroy(dtrace_hdl_t *dtp)
{
	(void)dtp;
}

int dt_btf_get_module_ids(dtrace_hdl_t *dtp)
{
	(void)dtp;
	return 0;
}

/* dt_rodata.c and dt_dis.c now compile correctly - no stubs needed */

/* dt_dof.c stubs - DOF not used on Redox */
void dt_dof_init(dtrace_hdl_t *dtp)
{
	(void)dtp;
}

void dt_dof_fini(dtrace_hdl_t *dtp)
{
	(void)dtp;
}

/* dt_errtag is now provided by redox/generated/dt_errtags.c */

/* dt_pcap.c stubs - packet capture not available */
void dt_pcap_destroy(dtrace_hdl_t *dtp)
{
	(void)dtp;
}

const char *dt_pcap_filename(dtrace_hdl_t *dtp, FILE *fp)
{
	(void)dtp; (void)fp;
	return NULL;
}

void dt_pcap_dump(dtrace_hdl_t *dtp, const char *name, uint64_t ts_sec,
    uint64_t ts_nsec, void *data, uint32_t caplen, uint32_t datalen)
{
	(void)dtp; (void)name; (void)ts_sec; (void)ts_nsec;
	(void)data; (void)caplen; (void)datalen;
}

/* dt_pebs.c stubs - PEBS sampling not available on Redox */
void dt_pebs_exit(dtrace_hdl_t *dtp)
{
	(void)dtp;
}

/* CTF stubs are now in include/sys/ctf_api.h */

/* dt_kern_path_lookup_by_name - dt_cg.c / dt_module.c support */
const char *dt_kern_path_lookup_by_name(dtrace_hdl_t *dtp, const char *modname)
{
	(void)dtp; (void)modname;
	return NULL;
}

/* dt_module.c support - configuration init */
void dt_conf_init(dtrace_hdl_t *dtp)
{
	/* Set some basic defaults for Redox */
	dtp->dt_conf.dtc_difversion = 2;
	dtp->dt_conf.dtc_difintregs = 8;
	dtp->dt_conf.dtc_diftupregs = 8;
	dtp->dt_conf.dtc_ctfmodel = 2; /* LP64 */
	
	/* CPU configuration - Redox doesn't have /sys/devices/system/cpu */
	dtp->dt_conf.num_possible_cpus = 1;
	dtp->dt_conf.num_online_cpus = 1;
	dtp->dt_conf.max_cpuid = 0;
	
	/* Allocate a single CPU info structure */
	dtp->dt_conf.cpus = calloc(1, sizeof(cpuinfo_t));
	if (dtp->dt_conf.cpus != NULL) {
		dtp->dt_conf.cpus[0].cpu_id = 0;
		dtp->dt_conf.cpus[0].cpu_chip = 0;
	}
}

/* dtrace_proc_* API stubs - process control not available on Redox */
struct dtrace_proc *dtrace_proc_grab_pid(dtrace_hdl_t *dtp, pid_t pid,
    int flags)
{
	(void)dtp; (void)pid; (void)flags;
	return NULL;
}

struct dtrace_proc *dtrace_proc_create(dtrace_hdl_t *dtp, const char *file,
    char *const *argv, int flags)
{
	(void)dtp; (void)file; (void)argv; (void)flags;
	return NULL;
}

void dtrace_proc_continue(dtrace_hdl_t *dtp, struct dtrace_proc *proc)
{
	(void)dtp; (void)proc;
}

void dtrace_proc_release(dtrace_hdl_t *dtp, struct dtrace_proc *proc)
{
	(void)dtp; (void)proc;
}

/* fmemopen stub */
FILE *fmemopen(void *buf, size_t size, const char *mode)
{
	(void)buf; (void)size; (void)mode;
	return NULL;
}

/* dt_link.c stubs - ELF/DOF linking not needed on Redox */
int dtrace_program_link(dtrace_hdl_t *dtp, dtrace_prog_t *pgp,
    uint_t dflags, const char *file, int objc, char *const objv[])
{
	(void)dtp; (void)pgp; (void)dflags; (void)file;
	(void)objc; (void)objv;
	/* On Redox, we don't link to ELF - just succeed */
	return 0;
}

#endif /* __redox__ */
