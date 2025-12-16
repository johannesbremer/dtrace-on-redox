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
#include <string.h>
#include <fcntl.h>
#include <pthread.h>
#include <dt_impl.h>
#include <dt_proc.h>
#include <dt_program.h>
#include <dt_ident.h>
#include <bpf_asm.h>
#include <linux/bpf.h>
#include <dtrace/difo.h>

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

/*
 * BPF Library Function Registration for Redox
 *
 * On Linux, BPF library functions (dt_bvar_args, dt_bvar_probedesc, etc.)
 * are compiled into bpf_dlib.o and loaded at runtime. On Redox, we don't
 * have this ELF file, so we register stub implementations directly.
 *
 * Each function is registered with a simple DIFO that returns 0.
 * This allows D scripts using built-in variables like arg0-arg9 to compile
 * and run (though they'll get stub values).
 */

/* DTrace-specific BPF helper ID for dt_get_agg */
#define DT_BPF_FUNC_get_agg	201

/*
 * Create a stub DIFO that simply returns 0.
 * This is used for built-in variable accessor functions on Redox.
 */
static dtrace_difo_t *
dt_create_stub_difo(dtrace_hdl_t *dtp)
{
	dtrace_difo_t *dp;
	struct bpf_insn *insns;

	(void)dtp;  /* unused for now, may be needed for allocation */

	dp = calloc(1, sizeof(dtrace_difo_t));
	if (dp == NULL)
		return NULL;

	/*
	 * Create a minimal BPF program:
	 *   mov r0, 0   ; return value = 0
	 *   exit        ; return
	 */
	insns = calloc(2, sizeof(struct bpf_insn));
	if (insns == NULL) {
		free(dp);
		return NULL;
	}

	insns[0] = BPF_MOV_IMM(BPF_REG_0, 0);
	insns[1] = BPF_RETURN();

	dp->dtdo_buf = insns;
	dp->dtdo_len = 2;
	dp->dtdo_refcnt = 1;

	return dp;
}

/*
 * Create a DIFO that calls a BPF helper function.
 * This is used for functions like dt_get_agg that need to call
 * a real helper implementation rather than just returning 0.
 *
 * The generated DIFO simply calls the helper and returns its result:
 *   call <helper_id>
 *   exit
 *
 * Arguments are passed through r1-r5 from the caller.
 */
static dtrace_difo_t *
dt_create_helper_stub_difo(dtrace_hdl_t *dtp, uint32_t helper_id)
{
	dtrace_difo_t *dp;
	struct bpf_insn *insns;

	(void)dtp;

	dp = calloc(1, sizeof(dtrace_difo_t));
	if (dp == NULL)
		return NULL;

	insns = calloc(2, sizeof(struct bpf_insn));
	if (insns == NULL) {
		free(dp);
		return NULL;
	}

	insns[0] = BPF_CALL_HELPER(helper_id);
	insns[1] = BPF_RETURN();

	dp->dtdo_buf = insns;
	dp->dtdo_len = 2;
	dp->dtdo_refcnt = 1;

	return dp;
}

/*
 * Register a single BPF library function with a stub DIFO.
 */
static int
dt_register_bpf_func(dtrace_hdl_t *dtp, const char *name)
{
	dt_ident_t *idp;
	dtrace_difo_t *dp;

	/* Add the function to the BPF symbol table */
	idp = dt_dlib_add_func(dtp, name);
	if (idp == NULL)
		return -1;

	/* Create and attach a stub DIFO */
	dp = dt_create_stub_difo(dtp);
	if (dp == NULL)
		return -1;

	/* Set up the identifier with the DIFO */
	dt_ident_morph(idp, idp->di_kind, &dt_idops_difo, dtp);
	dt_ident_set_data(idp, dp);

	return 0;
}

/*
 * Register a BPF library function that calls a BPF helper.
 * This is used for functions like dt_get_agg that need a real implementation.
 */
static int
dt_register_bpf_func_helper(dtrace_hdl_t *dtp, const char *name,
    uint32_t helper_id)
{
	dt_ident_t *idp;
	dtrace_difo_t *dp;

	idp = dt_dlib_add_func(dtp, name);
	if (idp == NULL)
		return -1;

	dp = dt_create_helper_stub_difo(dtp, helper_id);
	if (dp == NULL)
		return -1;

	dt_ident_morph(idp, idp->di_kind, &dt_idops_difo, dtp);
	dt_ident_set_data(idp, dp);

	return 0;
}

/*
 * Initialize BPF library functions for Redox.
 * This is called from dt_dlib_init() to register stub implementations
 * of all the BPF library functions that would normally come from bpf_dlib.o.
 */
void
dt_dlib_init_redox(dtrace_hdl_t *dtp)
{
	/*
	 * Register built-in variable accessor functions.
	 * These are called by the code generator when D scripts use
	 * variables like arg0, arg1, pid, tid, etc.
	 */
	static const char *bvar_funcs[] = {
		"dt_bvar_args",		/* arg0-arg9, args[] */
		"dt_bvar_probedesc",	/* probeprov, probemod, probefunc, probename */
		"dt_bvar_execargs",	/* execargs (command line) */
		"dt_bvar_caller",	/* caller */
		"dt_bvar_curcpu",	/* curcpu */
		"dt_bvar_curthread",	/* curthread */
		"dt_bvar_epid",		/* epid (enabled probe ID) */
		"dt_bvar_errno",	/* errno */
		"dt_bvar_execname",	/* execname */
		"dt_bvar_gid",		/* gid */
		"dt_bvar_id",		/* id (probe ID) */
		"dt_bvar_pid",		/* pid */
		"dt_bvar_ppid",		/* ppid */
		"dt_bvar_stackdepth",	/* stackdepth */
		"dt_bvar_tid",		/* tid */
		"dt_bvar_timestamp",	/* timestamp */
		"dt_bvar_ucaller",	/* ucaller */
		"dt_bvar_uid",		/* uid */
		"dt_bvar_ustackdepth",	/* ustackdepth */
		"dt_bvar_walltimestamp", /* walltimestamp */
		NULL
	};

	/*
	 * Register other BPF library functions.
	 */
	static const char *other_funcs[] = {
		"dt_error",		/* Error handling */
		"dt_probe_error",	/* Probe error handling (fault reporting) */
		"dt_get_dvar",		/* Dynamic variable access */
		"dt_get_assoc",		/* Associative array access */
		"dt_get_tvar",		/* Thread-local variable access */
		"dt_speculation",	/* speculation() builtin */
		"dt_speculation_set_drainable",	/* speculation draining */
		"dt_speculation_speculate",	/* speculate() action */
		"dt_strcmp",		/* String comparison */
		"dt_strchr",		/* strchr() builtin */
		"dt_strrchr",		/* strrchr() builtin */
		"dt_strlen",		/* strlen() builtin */
		"dt_strjoin",		/* strjoin() builtin */
		"dt_substr",		/* substr() builtin */
		"dt_strtok",		/* strtok() builtin */
		"dt_index",		/* index() builtin */
		"dt_rindex",		/* rindex() builtin */
		"dt_progenyof",		/* progenyof() builtin */
		"dt_tlskey",		/* TLS key access */
		"dt_agg_lqbin",		/* Linear quantize aggregation */
		"dt_agg_qbin",		/* Quantize aggregation */
		"dt_basename",		/* basename() builtin */
		"dt_cleanpath",		/* cleanpath() builtin */
		"dt_dirname",		/* dirname() builtin */
		"dt_lltostr",		/* lltostr() builtin */
		"dt_inet_ntoa",		/* inet_ntoa() builtin */
		"dt_inet_ntoa6",	/* inet_ntoa6() builtin */
		"dt_link_ntop",		/* link_ntop() builtin */
		"dt_mutex_owned",	/* mutex_owned() builtin */
		"dt_mutex_owner",	/* mutex_owner() builtin */
		"dt_rw_iswriter",	/* rw_iswriter() builtin */
		"dt_rw_read_held",	/* rw_read_held() builtin */
		"dt_rw_write_held",	/* rw_write_held() builtin */
		NULL
	};

	const char **func;

	/* Register built-in variable functions */
	for (func = bvar_funcs; *func != NULL; func++) {
		if (dt_register_bpf_func(dtp, *func) != 0) {
			/* Non-fatal: some functions may not be needed */
			dt_dprintf("dt_dlib_init_redox: failed to register %s\n", *func);
		}
	}

	/* Register other library functions */
	for (func = other_funcs; *func != NULL; func++) {
		if (dt_register_bpf_func(dtp, *func) != 0) {
			dt_dprintf("dt_dlib_init_redox: failed to register %s\n", *func);
		}
	}

	/*
	 * Register dt_get_agg with a helper-based implementation.
	 * This function needs real aggregation logic, not just a return-0 stub.
	 */
	if (dt_register_bpf_func_helper(dtp, "dt_get_agg",
	    DT_BPF_FUNC_get_agg) != 0) {
		dt_dprintf("dt_dlib_init_redox: failed to register dt_get_agg\n");
	}
}

#endif /* __redox__ */
