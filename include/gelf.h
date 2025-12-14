/*
 * Oracle Linux DTrace - RedoxOS Port
 * Copyright (c) 2025, Oracle and/or its affiliates. All rights reserved.
 * Licensed under the Universal Permissive License v 1.0 as shown at
 * http://oss.oracle.com/licenses/upl.
 *
 * GELF (Generic ELF) API stubs for RedoxOS
 */

#ifndef _GELF_H
#define _GELF_H

#include <stdint.h>
#include <stddef.h>

/* Include system ELF header if available */
#ifdef __redox__
#include <elf.h>
/* Redox elf.h doesn't define Elf64_Sword */
#ifndef Elf64_Sword
typedef int32_t Elf64_Sword;
#endif
/* Redox may not have these symbol table types */
#ifndef Elf64_Sym
typedef struct {
    Elf64_Word    st_name;
    unsigned char st_info;
    unsigned char st_other;
    Elf64_Half    st_shndx;
    Elf64_Addr    st_value;
    Elf64_Xword   st_size;
} Elf64_Sym;
#endif
#ifndef Elf32_Sym
typedef struct {
    Elf32_Word    st_name;
    Elf32_Addr    st_value;
    Elf32_Word    st_size;
    unsigned char st_info;
    unsigned char st_other;
    Elf32_Half    st_shndx;
} Elf32_Sym;
#endif
#endif

/* GELF types - always 64-bit, based on system Elf64 types */
typedef Elf64_Addr   GElf_Addr;
typedef Elf64_Off    GElf_Off;
typedef Elf64_Half   GElf_Half;
typedef Elf64_Word   GElf_Word;
typedef Elf64_Sword  GElf_Sword;
typedef Elf64_Xword  GElf_Xword;
typedef Elf64_Sxword GElf_Sxword;

/* ELF header - only define if not already defined */
#ifndef EI_NIDENT
#define EI_NIDENT 16
#endif

typedef struct {
	unsigned char e_ident[EI_NIDENT];
	GElf_Half     e_type;
	GElf_Half     e_machine;
	GElf_Word     e_version;
	GElf_Addr     e_entry;
	GElf_Off      e_phoff;
	GElf_Off      e_shoff;
	GElf_Word     e_flags;
	GElf_Half     e_ehsize;
	GElf_Half     e_phentsize;
	GElf_Half     e_phnum;
	GElf_Half     e_shentsize;
	GElf_Half     e_shnum;
	GElf_Half     e_shstrndx;
} GElf_Ehdr;

/* Program header */
typedef struct {
	GElf_Word  p_type;
	GElf_Word  p_flags;
	GElf_Off   p_offset;
	GElf_Addr  p_vaddr;
	GElf_Addr  p_paddr;
	GElf_Xword p_filesz;
	GElf_Xword p_memsz;
	GElf_Xword p_align;
} GElf_Phdr;

/* Section header */
typedef struct {
	GElf_Word  sh_name;
	GElf_Word  sh_type;
	GElf_Xword sh_flags;
	GElf_Addr  sh_addr;
	GElf_Off   sh_offset;
	GElf_Xword sh_size;
	GElf_Word  sh_link;
	GElf_Word  sh_info;
	GElf_Xword sh_addralign;
	GElf_Xword sh_entsize;
} GElf_Shdr;

/* Symbol table entry */
typedef struct {
	GElf_Word      st_name;
	unsigned char  st_info;
	unsigned char  st_other;
	GElf_Half      st_shndx;
	GElf_Addr      st_value;
	GElf_Xword     st_size;
} GElf_Sym;

/* Relocation entries */
typedef struct {
	GElf_Addr   r_offset;
	GElf_Xword  r_info;
} GElf_Rel;

typedef struct {
	GElf_Addr   r_offset;
	GElf_Xword  r_info;
	GElf_Sxword r_addend;
} GElf_Rela;

/* Dynamic section entry */
typedef struct {
	GElf_Sxword d_tag;
	union {
		GElf_Xword d_val;
		GElf_Addr  d_ptr;
	} d_un;
} GElf_Dyn;

/* Note header */
typedef struct {
	GElf_Word n_namesz;
	GElf_Word n_descsz;
	GElf_Word n_type;
} GElf_Nhdr;

/* ELF class */
#ifndef ELFCLASSNONE
#define ELFCLASSNONE 0
#endif
#ifndef ELFCLASS32
#define ELFCLASS32   1
#endif
#ifndef ELFCLASS64
#define ELFCLASS64   2
#endif

/* ELF data encoding */
#ifndef ELFDATANONE
#define ELFDATANONE 0
#endif
#ifndef ELFDATA2LSB
#define ELFDATA2LSB 1
#endif
#ifndef ELFDATA2MSB
#define ELFDATA2MSB 2
#endif

/* ELF file types */
#ifndef ET_NONE
#define ET_NONE   0
#endif
#ifndef ET_REL
#define ET_REL    1
#endif
#ifndef ET_EXEC
#define ET_EXEC   2
#endif
#ifndef ET_DYN
#define ET_DYN    3
#endif
#ifndef ET_CORE
#define ET_CORE   4
#endif

/* Section types */
#ifndef SHT_NULL
#define SHT_NULL     0
#endif
#ifndef SHT_PROGBITS
#define SHT_PROGBITS 1
#endif
#ifndef SHT_SYMTAB
#define SHT_SYMTAB   2
#endif
#ifndef SHT_STRTAB
#define SHT_STRTAB   3
#endif
#ifndef SHT_RELA
#define SHT_RELA     4
#endif
#ifndef SHT_HASH
#define SHT_HASH     5
#endif
#ifndef SHT_DYNAMIC
#define SHT_DYNAMIC  6
#endif
#ifndef SHT_NOTE
#define SHT_NOTE     7
#endif
#ifndef SHT_NOBITS
#define SHT_NOBITS   8
#endif
#ifndef SHT_REL
#define SHT_REL      9
#endif
#ifndef SHT_DYNSYM
#define SHT_DYNSYM   11
#endif

/* Section flags */
#ifndef SHF_WRITE
#define SHF_WRITE     0x1
#endif
#ifndef SHF_ALLOC
#define SHF_ALLOC     0x2
#endif
#ifndef SHF_EXECINSTR
#define SHF_EXECINSTR 0x4
#endif

/* Symbol binding */
#ifndef STB_LOCAL
#define STB_LOCAL  0
#endif
#ifndef STB_GLOBAL
#define STB_GLOBAL 1
#endif
#ifndef STB_WEAK
#define STB_WEAK   2
#endif

/* Symbol types */
#ifndef STT_NOTYPE
#define STT_NOTYPE  0
#endif
#ifndef STT_OBJECT
#define STT_OBJECT  1
#endif
#ifndef STT_FUNC
#define STT_FUNC    2
#endif
#ifndef STT_SECTION
#define STT_SECTION 3
#endif
#ifndef STT_FILE
#define STT_FILE    4
#endif

/* Special section indices */
#ifndef SHN_UNDEF
#define SHN_UNDEF   0
#endif
#ifndef SHN_ABS
#define SHN_ABS     0xfff1
#endif
#ifndef SHN_COMMON
#define SHN_COMMON  0xfff2
#endif

/* ELF macros */
#ifndef ELF64_ST_BIND
#define ELF64_ST_BIND(info)       ((info) >> 4)
#endif
#ifndef ELF64_ST_TYPE
#define ELF64_ST_TYPE(info)       ((info) & 0xf)
#endif
#ifndef ELF64_ST_INFO
#define ELF64_ST_INFO(bind, type) (((bind) << 4) + ((type) & 0xf))
#endif
#ifndef ELF64_R_SYM
#define ELF64_R_SYM(info)         ((info) >> 32)
#endif
#ifndef ELF64_R_TYPE
#define ELF64_R_TYPE(info)        ((info) & 0xffffffffL)
#endif
#ifndef ELF64_R_INFO
#define ELF64_R_INFO(sym, type)   (((uint64_t)(sym) << 32) + (type))
#endif

/* GELF macros (use 64-bit versions) */
#ifndef GELF_ST_BIND
#define GELF_ST_BIND(info)       ELF64_ST_BIND(info)
#endif
#ifndef GELF_ST_TYPE
#define GELF_ST_TYPE(info)       ELF64_ST_TYPE(info)
#endif
#ifndef GELF_ST_INFO
#define GELF_ST_INFO(bind, type) ELF64_ST_INFO(bind, type)
#endif
#ifndef GELF_R_SYM
#define GELF_R_SYM(info)         ELF64_R_SYM(info)
#endif
#ifndef GELF_R_TYPE
#define GELF_R_TYPE(info)        ELF64_R_TYPE(info)
#endif
#ifndef GELF_R_INFO
#define GELF_R_INFO(sym, type)   ELF64_R_INFO(sym, type)
#endif

/* ELF handle types (opaque) */
typedef struct Elf Elf;
typedef struct Elf_Scn Elf_Scn;
typedef struct Elf_Data Elf_Data;

/* Elf_Data structure */
struct Elf_Data {
	void      *d_buf;
	int        d_type;
	size_t     d_size;
	uint64_t   d_off;
	size_t     d_align;
	uint64_t   d_version;
};

/* ELF commands */
typedef enum {
	ELF_C_NULL = 0,
	ELF_C_READ,
	ELF_C_READ_MMAP,
	ELF_C_WRITE,
	ELF_C_RDWR,
	ELF_C_SET,
	ELF_C_CLR,
	ELF_C_FDREAD
} Elf_Cmd;

/* ELF kinds */
typedef enum {
	ELF_K_NONE = 0,
	ELF_K_AR,
	ELF_K_COFF,
	ELF_K_ELF
} Elf_Kind;

/* Stub function declarations */
static inline unsigned int elf_version(unsigned int ver)
{
	(void)ver;
	return 1;  /* EV_CURRENT */
}

static inline Elf *elf_begin(int fd, Elf_Cmd cmd, Elf *ref)
{
	(void)fd; (void)cmd; (void)ref;
	return NULL;
}

static inline int elf_end(Elf *elf)
{
	(void)elf;
	return 0;
}

static inline Elf_Kind elf_kind(Elf *elf)
{
	(void)elf;
	return ELF_K_NONE;
}

static inline GElf_Ehdr *gelf_getehdr(Elf *elf, GElf_Ehdr *dst)
{
	(void)elf; (void)dst;
	return NULL;
}

static inline GElf_Phdr *gelf_getphdr(Elf *elf, int ndx, GElf_Phdr *dst)
{
	(void)elf; (void)ndx; (void)dst;
	return NULL;
}

static inline Elf_Scn *elf_getscn(Elf *elf, size_t ndx)
{
	(void)elf; (void)ndx;
	return NULL;
}

static inline Elf_Scn *elf_nextscn(Elf *elf, Elf_Scn *scn)
{
	(void)elf; (void)scn;
	return NULL;
}

static inline GElf_Shdr *gelf_getshdr(Elf_Scn *scn, GElf_Shdr *dst)
{
	(void)scn; (void)dst;
	return NULL;
}

static inline Elf_Data *elf_getdata(Elf_Scn *scn, Elf_Data *data)
{
	(void)scn; (void)data;
	return NULL;
}

static inline GElf_Sym *gelf_getsym(Elf_Data *data, int ndx, GElf_Sym *dst)
{
	(void)data; (void)ndx; (void)dst;
	return NULL;
}

static inline int gelf_update_sym(Elf_Data *data, int ndx, GElf_Sym *src)
{
	(void)data; (void)ndx; (void)src;
	return 0;
}

static inline GElf_Rela *gelf_getrela(Elf_Data *data, int ndx, GElf_Rela *dst)
{
	(void)data; (void)ndx; (void)dst;
	return NULL;
}

static inline int gelf_update_rela(Elf_Data *data, int ndx, GElf_Rela *src)
{
	(void)data; (void)ndx; (void)src;
	return 0;
}

static inline char *elf_strptr(Elf *elf, size_t ndx, size_t offset)
{
	(void)elf; (void)ndx; (void)offset;
	return NULL;
}

static inline size_t elf_ndxscn(Elf_Scn *scn)
{
	(void)scn;
	return 0;
}

static inline int elf_getshdrstrndx(Elf *elf, size_t *ndxp)
{
	(void)elf; (void)ndxp;
	return -1;
}

static inline int elf_getphdrnum(Elf *elf, size_t *nump)
{
	(void)elf; (void)nump;
	return -1;
}

static inline const char *elf_errmsg(int err)
{
	(void)err;
	return "ELF not supported on Redox";
}

static inline int elf_errno(void)
{
	return -1;
}

static inline int gelf_getclass(Elf *elf)
{
	(void)elf;
	return ELFCLASS64;
}

static inline off_t elf_update(Elf *elf, Elf_Cmd cmd)
{
	(void)elf; (void)cmd;
	return -1;
}

static inline int elf_flagelf(Elf *elf, Elf_Cmd cmd, unsigned int flags)
{
	(void)elf; (void)cmd; (void)flags;
	return 0;
}

static inline int elf_flagdata(Elf_Data *data, Elf_Cmd cmd, unsigned int flags)
{
	(void)data; (void)cmd; (void)flags;
	return 0;
}

static inline Elf_Scn *elf_newscn(Elf *elf)
{
	(void)elf;
	return NULL;
}

static inline Elf_Data *elf_newdata(Elf_Scn *scn)
{
	(void)scn;
	return NULL;
}

static inline int elf_cntl(Elf *elf, Elf_Cmd cmd)
{
	(void)elf; (void)cmd;
	return 0;
}

static inline char *elf_rawfile(Elf *elf, size_t *nbytes)
{
	(void)elf;
	if (nbytes) *nbytes = 0;
	return NULL;
}

static inline int elf_getshdrnum(Elf *elf, size_t *nump)
{
	(void)elf; (void)nump;
	return -1;
}

static inline size_t gelf_getnote(Elf_Data *data, size_t offset,
    GElf_Nhdr *nhdr, size_t *name_off, size_t *desc_off)
{
	(void)data; (void)offset; (void)nhdr; (void)name_off; (void)desc_off;
	return 0;  /* End of notes */
}

#endif /* _GELF_H */
