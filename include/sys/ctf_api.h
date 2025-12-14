/*
 * Oracle Linux DTrace - RedoxOS Port
 * Copyright (c) 2025, Oracle and/or its affiliates. All rights reserved.
 * Licensed under the Universal Permissive License v 1.0 as shown at
 * http://oss.oracle.com/licenses/upl.
 *
 * CTF (Compact C Type Format) API for RedoxOS
 * This provides a minimal working type system for DTrace on Redox.
 */

#ifndef _SYS_CTF_API_H
#define _SYS_CTF_API_H

#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#ifdef __redox__
#include <stdio.h>
#endif

/*
 * Minimal CTF implementation for Redox.
 * Instead of stubs that return errors, we provide a simple
 * type table that can hold the basic types DTrace needs.
 */
/* CTF type and member IDs */
typedef uint32_t ctf_id_t;

/* Maximum types in our simple implementation */
#define CTF_REDOX_MAX_TYPES 256

/* CTF file handle - contains our type table */
typedef struct ctf_file {
	int model;
	void *specific;
	struct ctf_file *parent;
	ctf_id_t next_id;
	struct {
		char name[64];
		int kind;
		ctf_id_t ref;
		size_t size;
	} types[CTF_REDOX_MAX_TYPES];
} ctf_file_t;

typedef ctf_file_t ctf_dict_t;
typedef struct ctf_archive ctf_archive_t;

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

/* === Implementation functions === */

static inline ctf_file_t *ctf_create(int *errp)
{
	ctf_file_t *fp = calloc(1, sizeof(ctf_file_t));
	if (fp == NULL) {
		if (errp) *errp = ECTF_NOTFOUND;
		return NULL;
	}
	fp->model = CTF_MODEL_LP64;
	fp->next_id = 1; /* Start from 1, 0 is invalid */
	if (errp) *errp = 0;
	return fp;
}

static inline void ctf_close(ctf_file_t *fp)
{
	if (fp) free(fp);
}

static inline int ctf_setmodel(ctf_file_t *fp, int model)
{
	if (fp) fp->model = model;
	return 0;
}

static inline int ctf_getmodel(ctf_file_t *fp)
{
	return fp ? fp->model : CTF_MODEL_LP64;
}

static inline void ctf_setspecific(ctf_file_t *fp, void *data)
{
	if (fp) fp->specific = data;
}

static inline void *ctf_getspecific(ctf_file_t *fp)
{
	return fp ? fp->specific : NULL;
}

static inline int ctf_import(ctf_file_t *fp, ctf_file_t *pfp)
{
	ctf_id_t i;
	if (!fp || !pfp)
		return 0;
	
	/*
	 * Copy all types from parent to child so type IDs are consistent.
	 * This is simpler than proper parent lookup and works for our use case.
	 */
	for (i = 1; i < pfp->next_id && i < CTF_REDOX_MAX_TYPES; i++) {
		memcpy(&fp->types[i], &pfp->types[i], sizeof(fp->types[i]));
	}
	fp->next_id = pfp->next_id;
	fp->parent = pfp; /* Keep parent pointer for reference */
	
	return 0;
}

static inline ctf_file_t *ctf_parent_file(ctf_file_t *fp)
{
	return fp ? fp->parent : NULL;
}

static inline const char *ctf_parent_name(ctf_file_t *fp)
{
	(void)fp;
	return NULL;
}
static inline ctf_id_t ctf_add_integer(ctf_file_t *fp, uint32_t flags,
    const char *name, const ctf_encoding_t *ep)
{
	ctf_id_t id;
	(void)flags;
	if (!fp || fp->next_id >= CTF_REDOX_MAX_TYPES)
		return CTF_ERR;
	id = fp->next_id++;
	strncpy(fp->types[id].name, name ? name : "", 63);
	fp->types[id].name[63] = '\0';
	fp->types[id].kind = CTF_K_INTEGER;
	fp->types[id].size = ep ? (ep->cte_bits / 8) : 4;
	return id;
}

static inline ctf_id_t ctf_add_float(ctf_file_t *fp, uint32_t flags,
    const char *name, const ctf_encoding_t *ep)
{
	ctf_id_t id;
	(void)flags;
	if (!fp || fp->next_id >= CTF_REDOX_MAX_TYPES)
		return CTF_ERR;
	id = fp->next_id++;
	strncpy(fp->types[id].name, name ? name : "", 63);
	fp->types[id].name[63] = '\0';
	fp->types[id].kind = CTF_K_FLOAT;
	fp->types[id].size = ep ? (ep->cte_bits / 8) : 8;
	return id;
}

static inline ctf_id_t ctf_add_pointer(ctf_file_t *fp, uint32_t flags,
    ctf_id_t ref)
{
	ctf_id_t id;
	(void)flags;
	if (!fp || fp->next_id >= CTF_REDOX_MAX_TYPES)
		return CTF_ERR;
	id = fp->next_id++;
	fp->types[id].name[0] = '\0';
	fp->types[id].kind = CTF_K_POINTER;
	fp->types[id].ref = ref;
	fp->types[id].size = 8;
	return id;
}

static inline ctf_id_t ctf_add_typedef(ctf_file_t *fp, uint32_t flags,
    const char *name, ctf_id_t ref)
{
	ctf_id_t id;
	(void)flags;
	if (!fp || fp->next_id >= CTF_REDOX_MAX_TYPES)
		return CTF_ERR;
	id = fp->next_id++;
	strncpy(fp->types[id].name, name ? name : "", 63);
	fp->types[id].name[63] = '\0';
	fp->types[id].kind = CTF_K_TYPEDEF;
	fp->types[id].ref = ref;
	return id;
}

static inline ctf_id_t ctf_add_struct(ctf_file_t *fp, uint32_t flags,
    const char *name)
{
	ctf_id_t id;
	(void)flags;
	if (!fp || fp->next_id >= CTF_REDOX_MAX_TYPES)
		return CTF_ERR;
	id = fp->next_id++;
	strncpy(fp->types[id].name, name ? name : "", 63);
	fp->types[id].name[63] = '\0';
	fp->types[id].kind = CTF_K_STRUCT;
	return id;
}

static inline ctf_id_t ctf_add_union(ctf_file_t *fp, uint32_t flags,
    const char *name)
{
	ctf_id_t id;
	(void)flags;
	if (!fp || fp->next_id >= CTF_REDOX_MAX_TYPES)
		return CTF_ERR;
	id = fp->next_id++;
	strncpy(fp->types[id].name, name ? name : "", 63);
	fp->types[id].name[63] = '\0';
	fp->types[id].kind = CTF_K_UNION;
	return id;
}

static inline ctf_id_t ctf_add_enum(ctf_file_t *fp, uint32_t flags,
    const char *name)
{
	ctf_id_t id;
	(void)flags;
	if (!fp || fp->next_id >= CTF_REDOX_MAX_TYPES)
		return CTF_ERR;
	id = fp->next_id++;
	strncpy(fp->types[id].name, name ? name : "", 63);
	fp->types[id].name[63] = '\0';
	fp->types[id].kind = CTF_K_ENUM;
	return id;
}

static inline ctf_id_t ctf_add_array(ctf_file_t *fp, uint32_t flags,
    const ctf_arinfo_t *arp)
{
	ctf_id_t id;
	(void)flags;
	if (!fp || fp->next_id >= CTF_REDOX_MAX_TYPES)
		return CTF_ERR;
	id = fp->next_id++;
	fp->types[id].name[0] = '\0';
	fp->types[id].kind = CTF_K_ARRAY;
	if (arp) fp->types[id].ref = arp->ctr_contents;
	return id;
}

static inline ctf_id_t ctf_add_function(ctf_file_t *fp, uint32_t flags,
    const ctf_funcinfo_t *fi, const ctf_id_t *args)
{
	ctf_id_t id;
	(void)flags; (void)fi; (void)args;
	if (!fp || fp->next_id >= CTF_REDOX_MAX_TYPES)
		return CTF_ERR;
	id = fp->next_id++;
	fp->types[id].name[0] = '\0';
	fp->types[id].kind = CTF_K_FUNCTION;
	return id;
}

static inline int ctf_add_member(ctf_file_t *fp, ctf_id_t type,
    const char *name, ctf_id_t memb)
{
	(void)fp; (void)type; (void)name; (void)memb;
	return 0; /* Success - we don't track members */
}

static inline int ctf_add_enumerator(ctf_file_t *fp, ctf_id_t type,
    const char *name, int val)
{
	(void)fp; (void)type; (void)name; (void)val;
	return 0;
}

static inline int ctf_update(ctf_file_t *fp)
{
	(void)fp;
	return 0;
}

static inline ctf_id_t ctf_lookup_by_name(ctf_file_t *fp, const char *name)
{
	ctf_id_t i;
	size_t name_len;
	
	if (!fp || !name)
		return CTF_ERR;
	if ((unsigned long)fp < 0x1000)
		return CTF_ERR;
	if (fp->next_id > CTF_REDOX_MAX_TYPES)
		return CTF_ERR;
	
	name_len = strlen(name);
	
	/* Trim trailing whitespace from search name */
	while (name_len > 0 && (name[name_len - 1] == ' ' || 
	       name[name_len - 1] == '\t' || name[name_len - 1] == '\n'))
		name_len--;
	
	/* 
	 * Search in current file. Types from parent are copied during import,
	 * so all types should be available locally.
	 */
	for (i = 1; i < fp->next_id; i++) {
		/* Manual comparison to avoid relibc strcmp issues */
		const char *tname = fp->types[i].name;
		size_t tlen = strlen(tname);
		
		if (tlen == name_len && memcmp(tname, name, name_len) == 0)
			return i;
	}
	return CTF_ERR;
}

static inline int ctf_type_kind(ctf_file_t *fp, ctf_id_t type)
{
	if (!fp || type == 0 || type >= CTF_REDOX_MAX_TYPES)
		return CTF_K_UNKNOWN;
	return fp->types[type].kind;
}

static inline ctf_id_t ctf_type_reference(ctf_file_t *fp, ctf_id_t type)
{
	int kind;
	if (!fp || type == 0 || type >= CTF_REDOX_MAX_TYPES)
		return CTF_ERR;
	
	/* Only pointer, typedef, array, volatile, const, restrict have refs */
	kind = fp->types[type].kind;
	if (kind != CTF_K_POINTER && kind != CTF_K_TYPEDEF &&
	    kind != CTF_K_ARRAY && kind != CTF_K_VOLATILE &&
	    kind != CTF_K_CONST && kind != CTF_K_RESTRICT)
		return CTF_ERR;
	
	/* Return CTF_ERR if ref is not set (0) */
	if (fp->types[type].ref == 0)
		return CTF_ERR;
	
	return fp->types[type].ref;
}

static inline ctf_id_t ctf_type_resolve(ctf_file_t *fp, ctf_id_t type)
{
	int kind;
	int depth = 0;
	const int max_depth = 100; /* Prevent infinite loops */
	
	while (fp && type != 0 && type < CTF_REDOX_MAX_TYPES && depth < max_depth) {
		kind = fp->types[type].kind;
		if (kind == CTF_K_TYPEDEF && fp->types[type].ref != 0 && 
		    fp->types[type].ref != type) {
			type = fp->types[type].ref;
			depth++;
		} else {
			break;
		}
	}
	return type;
}

static inline char *ctf_type_name(ctf_file_t *fp, ctf_id_t type,
    char *buf, size_t len)
{
	if (!fp || !buf || len == 0 || type == 0 || type >= CTF_REDOX_MAX_TYPES)
		return NULL;
	strncpy(buf, fp->types[type].name, len - 1);
	buf[len - 1] = '\0';
	return buf;
}

static inline ssize_t ctf_type_size(ctf_file_t *fp, ctf_id_t type)
{
	if (!fp || type == 0 || type >= CTF_REDOX_MAX_TYPES)
		return -1;
	if (fp->types[type].kind == CTF_K_TYPEDEF)
		return ctf_type_size(fp, fp->types[type].ref);
	return (ssize_t)fp->types[type].size;
}

static inline ssize_t ctf_type_align(ctf_file_t *fp, ctf_id_t type)
{
	ssize_t sz = ctf_type_size(fp, type);
	if (sz <= 0) return 1;
	if (sz > 8) return 8;
	return sz;
}

static inline int ctf_type_encoding(ctf_file_t *fp, ctf_id_t type,
    ctf_encoding_t *ep)
{
	ctf_id_t resolved;
	
	if (!fp || !ep || type == 0 || type >= CTF_REDOX_MAX_TYPES)
		return -1;
	
	/* Resolve through typedefs to get the actual base type's encoding */
	resolved = ctf_type_resolve(fp, type);
	if (resolved == 0 || resolved >= CTF_REDOX_MAX_TYPES)
		resolved = type;
	
	ep->cte_format = 0;
	ep->cte_offset = 0;
	ep->cte_bits = (uint32_t)(fp->types[resolved].size * 8);
	return 0;
}

static inline const char *ctf_errmsg(int err)
{
	(void)err;
	return "CTF error";
}

static inline int ctf_errno(ctf_file_t *fp)
{
	(void)fp;
	return 0;
}

/* Functions that are not needed - return success/no-op */
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

static inline int ctf_discard(ctf_file_t *fp)
{
	(void)fp;
	return 0;
}

static inline int ctf_write(ctf_file_t *fp, int fd)
{
	(void)fp; (void)fd;
	return 0;
}

static inline int ctf_set_array(ctf_file_t *fp, ctf_id_t type,
    const ctf_arinfo_t *arp)
{
	(void)fp; (void)type; (void)arp;
	return 0;
}

static inline int ctf_type_compat(ctf_file_t *fp1, ctf_id_t type1,
    ctf_file_t *fp2, ctf_id_t type2)
{
	(void)fp1; (void)fp2;
	return type1 == type2 ? 1 : 0;
}

static inline ctf_id_t ctf_add_type(ctf_file_t *dst, ctf_file_t *src,
    ctf_id_t type)
{
	(void)dst; (void)src; (void)type;
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

/* Additional stubs from dt_stubs_redox.c */
static inline ctf_id_t ctf_type_pointer(ctf_file_t *fp, ctf_id_t type)
{
	(void)fp; (void)type;
	return CTF_ERR;
}

static inline int ctf_type_cmp(ctf_file_t *fp1, ctf_id_t t1, ctf_file_t *fp2, ctf_id_t t2)
{
	(void)fp1; (void)fp2;
	if (t1 == t2) return 0;
	return (t1 < t2) ? -1 : 1;
}

static inline int ctf_enum_value(ctf_file_t *fp, ctf_id_t type, const char *name, int *valp)
{
	(void)fp; (void)type; (void)name; (void)valp;
	return -1;
}

static inline ctf_id_t ctf_add_forward(ctf_file_t *fp, unsigned int flag, const char *name,
    unsigned int kind)
{
	ctf_id_t id;
	(void)flag;
	if (!fp || fp->next_id >= CTF_REDOX_MAX_TYPES)
		return CTF_ERR;
	id = fp->next_id++;
	strncpy(fp->types[id].name, name ? name : "", 63);
	fp->types[id].name[63] = '\0';
	fp->types[id].kind = (int)kind;
	return id;
}

/* ctf_visit_f is a callback type */
typedef int ctf_visit_f(const char *, ctf_id_t, unsigned long, int, void *);

static inline int ctf_type_visit(ctf_file_t *fp, ctf_id_t type, ctf_visit_f *func, void *arg)
{
	(void)fp; (void)type; (void)func; (void)arg;
	return 0;
}

#endif /* _SYS_CTF_API_H */
