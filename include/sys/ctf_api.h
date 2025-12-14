/*
 * Oracle Linux DTrace - RedoxOS Port
 * Copyright (c) 2025, Oracle and/or its affiliates. All rights reserved.
 * Licensed under the Universal Permissive License v 1.0 as shown at
 * http://oss.oracle.com/licenses/upl.
 *
 * CTF (Compact C Type Format) API stubs for RedoxOS
 * CTF is not available on RedoxOS, so we provide minimal stubs.
 */

#ifndef _SYS_CTF_API_H
#define _SYS_CTF_API_H

#include <stdint.h>
#include <stddef.h>
#include <sys/types.h>

/* CTF file handle - opaque pointer */
typedef struct ctf_file ctf_file_t;
typedef struct ctf_file ctf_dict_t;
typedef struct ctf_archive ctf_archive_t;

/* CTF type and member IDs */
typedef uint32_t ctf_id_t;

/* CTF encoding structure for integers and floats */
typedef struct ctf_encoding {
	uint32_t cte_format;
	uint32_t cte_offset;
	uint32_t cte_bits;
} ctf_encoding_t;

/* CTF section info */
typedef struct ctf_sect {
	const char *cts_name;
	unsigned long cts_type;
	unsigned long cts_flags;
	void *cts_data;
	size_t cts_size;
	size_t cts_entsize;
	off_t cts_offset;
} ctf_sect_t;

/* CTF archive info - used for array types */
typedef struct ctf_arinfo {
	ctf_id_t ctr_contents;
	ctf_id_t ctr_index;
	uint32_t ctr_nelems;
} ctf_arinfo_t;

/* CTF function info */
typedef struct ctf_funcinfo {
	ctf_id_t ctc_return;
	uint32_t ctc_argc;
	uint32_t ctc_flags;
} ctf_funcinfo_t;

/* CTF member info */
typedef struct ctf_membinfo {
	ctf_id_t ctm_type;
	unsigned long ctm_offset;
} ctf_membinfo_t;

/* CTF integer encoding flags */
#define CTF_INT_SIGNED    0x01
#define CTF_INT_CHAR      0x02
#define CTF_INT_BOOL      0x04
#define CTF_INT_VARARGS   0x08

/* CTF char encoding - use same value as CTF_INT_CHAR for compat */
#define CTF_CHAR          CTF_INT_CHAR

/* CTF float encoding types */
#define CTF_FP_SINGLE     1
#define CTF_FP_DOUBLE     2
#define CTF_FP_CPLX       3
#define CTF_FP_DCPLX      4
#define CTF_FP_LDCPLX     5
#define CTF_FP_LDOUBLE    6
#define CTF_FP_INTRVL     7
#define CTF_FP_DINTRVL    8
#define CTF_FP_LDINTRVL   9
#define CTF_FP_IMAGRY     10
#define CTF_FP_DIMAGRY    11
#define CTF_FP_LDIMAGRY   12

/* CTF model constants */
#define CTF_MODEL_ILP32   1
#define CTF_MODEL_LP64    2
#ifdef __LP64__
#define CTF_MODEL_NATIVE  CTF_MODEL_LP64
#else
#define CTF_MODEL_NATIVE  CTF_MODEL_ILP32
#endif

/* CTF type kinds */
#define CTF_K_UNKNOWN     0
#define CTF_K_INTEGER     1
#define CTF_K_FLOAT       2
#define CTF_K_POINTER     3
#define CTF_K_ARRAY       4
#define CTF_K_FUNCTION    5
#define CTF_K_STRUCT      6
#define CTF_K_UNION       7
#define CTF_K_ENUM        8
#define CTF_K_FORWARD     9
#define CTF_K_TYPEDEF     10
#define CTF_K_VOLATILE    11
#define CTF_K_CONST       12
#define CTF_K_RESTRICT    13
#define CTF_K_MAX         63

/* CTF errors */
#define CTF_ERR           ((ctf_id_t)-1L)
#define ECTF_NOTFOUND     1
#define ECTF_NOTYPEDAT    2
#define ECTF_NOTYPE       3

/* CTF add flags */
#define CTF_ADD_NONROOT   0
#define CTF_ADD_ROOT      1

/* Stub functions - all return failure or NULL */
static inline ctf_file_t *ctf_open(const char *filename, int *errp)
{
	(void)filename;
	if (errp) *errp = ECTF_NOTFOUND;
	return NULL;
}

static inline ctf_file_t *ctf_bufopen(const ctf_sect_t *ctfsect,
    const ctf_sect_t *symsect, const ctf_sect_t *strsect, int *errp)
{
	(void)ctfsect; (void)symsect; (void)strsect;
	if (errp) *errp = ECTF_NOTFOUND;
	return NULL;
}

static inline void ctf_close(ctf_file_t *fp)
{
	(void)fp;
}

static inline ctf_file_t *ctf_create(int *errp)
{
	if (errp) *errp = ECTF_NOTFOUND;
	return NULL;
}

static inline int ctf_setmodel(ctf_file_t *fp, int model)
{
	(void)fp; (void)model;
	return -1;
}

static inline void ctf_setspecific(ctf_file_t *fp, void *data)
{
	(void)fp; (void)data;
}

static inline void *ctf_getspecific(ctf_file_t *fp)
{
	(void)fp;
	return NULL;
}

static inline int ctf_import(ctf_file_t *fp, ctf_file_t *pfp)
{
	(void)fp; (void)pfp;
	return -1;
}

static inline ctf_id_t ctf_add_function(ctf_file_t *fp, uint32_t flags,
    const ctf_funcinfo_t *fi, const ctf_id_t *args)
{
	(void)fp; (void)flags; (void)fi; (void)args;
	return CTF_ERR;
}

static inline ctf_id_t ctf_lookup_by_name(ctf_file_t *fp, const char *name)
{
	(void)fp; (void)name;
	return CTF_ERR;
}

static inline ctf_id_t ctf_type_reference(ctf_file_t *fp, ctf_id_t type)
{
	(void)fp; (void)type;
	return CTF_ERR;
}

static inline int ctf_type_kind(ctf_file_t *fp, ctf_id_t type)
{
	(void)fp; (void)type;
	return CTF_K_UNKNOWN;
}

static inline ctf_id_t ctf_type_resolve(ctf_file_t *fp, ctf_id_t type)
{
	(void)fp; (void)type;
	return type;
}

static inline char *ctf_type_name(ctf_file_t *fp, ctf_id_t type,
    char *buf, size_t len)
{
	(void)fp; (void)type; (void)buf; (void)len;
	return NULL;
}

static inline int ctf_type_encoding(ctf_file_t *fp, ctf_id_t type,
    ctf_encoding_t *ep)
{
	(void)fp; (void)type; (void)ep;
	return -1;
}

static inline ssize_t ctf_type_size(ctf_file_t *fp, ctf_id_t type)
{
	(void)fp; (void)type;
	return -1;
}

static inline ssize_t ctf_type_align(ctf_file_t *fp, ctf_id_t type)
{
	(void)fp; (void)type;
	return -1;
}

static inline int ctf_member_info(ctf_file_t *fp, ctf_id_t type,
    const char *name, ctf_membinfo_t *mip)
{
	(void)fp; (void)type; (void)name; (void)mip;
	return -1;
}

static inline int ctf_array_info(ctf_file_t *fp, ctf_id_t type, void *arp)
{
	(void)fp; (void)type; (void)arp;
	return -1;
}

static inline int ctf_func_info(ctf_file_t *fp, unsigned long idx,
    ctf_funcinfo_t *fip)
{
	(void)fp; (void)idx; (void)fip;
	return -1;
}

static inline int ctf_func_args(ctf_file_t *fp, unsigned long idx,
    uint32_t argc, ctf_id_t *args)
{
	(void)fp; (void)idx; (void)argc; (void)args;
	return -1;
}

static inline const char *ctf_errmsg(int err)
{
	(void)err;
	return "CTF not supported on Redox";
}

static inline int ctf_errno(ctf_file_t *fp)
{
	(void)fp;
	return ECTF_NOTFOUND;
}

static inline ctf_file_t *ctf_parent_file(ctf_file_t *fp)
{
	(void)fp;
	return NULL;
}

static inline const char *ctf_parent_name(ctf_file_t *fp)
{
	(void)fp;
	return NULL;
}

static inline int ctf_type_iter(ctf_file_t *fp, int (*func)(ctf_id_t, void *), void *arg)
{
	(void)fp; (void)func; (void)arg;
	return 0;
}

static inline int ctf_member_iter(ctf_file_t *fp, ctf_id_t type,
    int (*func)(const char *, ctf_id_t, unsigned long, void *), void *arg)
{
	(void)fp; (void)type; (void)func; (void)arg;
	return 0;
}

static inline int ctf_enum_iter(ctf_file_t *fp, ctf_id_t type,
    int (*func)(const char *, int, void *), void *arg)
{
	(void)fp; (void)type; (void)func; (void)arg;
	return 0;
}

static inline ctf_archive_t *ctf_arc_open(const char *filename, int *errp)
{
	(void)filename;
	if (errp) *errp = ECTF_NOTFOUND;
	return NULL;
}

static inline void ctf_arc_close(ctf_archive_t *arc)
{
	(void)arc;
}

static inline ctf_file_t *ctf_arc_open_by_name(ctf_archive_t *arc,
    const char *name, int *errp)
{
	(void)arc; (void)name;
	if (errp) *errp = ECTF_NOTFOUND;
	return NULL;
}

static inline int ctf_arc_iter(ctf_archive_t *arc,
    int (*func)(ctf_file_t *, const char *, void *), void *arg)
{
	(void)arc; (void)func; (void)arg;
	return 0;
}

static inline ctf_id_t ctf_add_integer(ctf_file_t *fp, uint32_t flags,
    const char *name, const ctf_encoding_t *ep)
{
	(void)fp; (void)flags; (void)name; (void)ep;
	return CTF_ERR;
}

static inline ctf_id_t ctf_add_float(ctf_file_t *fp, uint32_t flags,
    const char *name, const ctf_encoding_t *ep)
{
	(void)fp; (void)flags; (void)name; (void)ep;
	return CTF_ERR;
}

static inline ctf_id_t ctf_add_pointer(ctf_file_t *fp, uint32_t flags,
    ctf_id_t ref)
{
	(void)fp; (void)flags; (void)ref;
	return CTF_ERR;
}

static inline ctf_id_t ctf_add_typedef(ctf_file_t *fp, uint32_t flags,
    const char *name, ctf_id_t ref)
{
	(void)fp; (void)flags; (void)name; (void)ref;
	return CTF_ERR;
}

static inline ctf_id_t ctf_add_struct(ctf_file_t *fp, uint32_t flags,
    const char *name)
{
	(void)fp; (void)flags; (void)name;
	return CTF_ERR;
}

static inline ctf_id_t ctf_add_union(ctf_file_t *fp, uint32_t flags,
    const char *name)
{
	(void)fp; (void)flags; (void)name;
	return CTF_ERR;
}

static inline ctf_id_t ctf_add_enum(ctf_file_t *fp, uint32_t flags,
    const char *name)
{
	(void)fp; (void)flags; (void)name;
	return CTF_ERR;
}

static inline int ctf_add_member(ctf_file_t *fp, ctf_id_t type,
    const char *name, ctf_id_t memb)
{
	(void)fp; (void)type; (void)name; (void)memb;
	return -1;
}

static inline int ctf_add_enumerator(ctf_file_t *fp, ctf_id_t type,
    const char *name, int val)
{
	(void)fp; (void)type; (void)name; (void)val;
	return -1;
}

static inline int ctf_discard(ctf_file_t *fp)
{
	(void)fp;
	return -1;
}

static inline int ctf_write(ctf_file_t *fp, int fd)
{
	(void)fp; (void)fd;
	return -1;
}

static inline int ctf_update(ctf_file_t *fp)
{
	(void)fp;
	return -1;
}

static inline int ctf_set_array(ctf_file_t *fp, ctf_id_t type,
    const ctf_arinfo_t *arp)
{
	(void)fp; (void)type; (void)arp;
	return -1;
}

static inline int ctf_type_compat(ctf_file_t *fp1, ctf_id_t type1,
    ctf_file_t *fp2, ctf_id_t type2)
{
	(void)fp1; (void)type1; (void)fp2; (void)type2;
	return 0;
}

static inline int ctf_getmodel(ctf_file_t *fp)
{
	(void)fp;
	return CTF_MODEL_LP64;
}

static inline ctf_id_t ctf_add_type(ctf_file_t *dst, ctf_file_t *src,
    ctf_id_t type)
{
	(void)dst; (void)src; (void)type;
	return CTF_ERR;
}

static inline ctf_id_t ctf_add_array(ctf_file_t *fp, uint32_t flags,
    const ctf_arinfo_t *arp)
{
	(void)fp; (void)flags; (void)arp;
	return CTF_ERR;
}

static inline ctf_id_t ctf_lookup_variable(ctf_file_t *fp, const char *name)
{
	(void)fp; (void)name;
	return CTF_ERR;
}

static inline ctf_id_t ctf_lookup_by_symbol(ctf_file_t *fp, unsigned long idx)
{
	(void)fp; (void)idx;
	return CTF_ERR;
}

#endif /* _SYS_CTF_API_H */
