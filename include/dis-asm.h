/*
 * Oracle Linux DTrace - RedoxOS Port
 * Copyright (c) 2025, Oracle and/or its affiliates. All rights reserved.
 * Licensed under the Universal Permissive License v 1.0 as shown at
 * http://oss.oracle.com/licenses/upl.
 *
 * Disassembler API stubs for RedoxOS
 * The binutils disassembler is not available on Redox.
 */

#ifndef _DIS_ASM_H
#define _DIS_ASM_H

#include <stdint.h>
#include <stddef.h>
#include <stdio.h>

/* Minimal stub structures and types */
typedef struct disassemble_info {
	void *stream;
	int (*fprintf_func)(void *, const char *, ...);
	int (*read_memory_func)(uint64_t, uint8_t *, unsigned int, struct disassemble_info *);
	void (*memory_error_func)(int, uint64_t, struct disassemble_info *);
	void (*print_address_func)(uint64_t, struct disassemble_info *);
	int bytes_per_line;
	int bytes_per_chunk;
	int mach;
	int arch;
	void *private_data;
	uint8_t *buffer;
	size_t buffer_length;
	uint64_t buffer_vma;
} disassemble_info;

typedef int (*disassembler_ftype)(uint64_t, struct disassemble_info *);

/* Macros for configure detection */
#define INIT_DISASM_INFO_THREE_ARG 1
#define DISASSEMBLER_FOUR_ARGS     1

/* Architecture constants */
#define bfd_mach_x86_64         64
#define bfd_mach_x86_64_intel_syntax 65
#define bfd_arch_i386           1

/* Stub functions */
static inline void init_disassemble_info(disassemble_info *dinfo,
    void *stream, int (*fprintf_func)(void *, const char *, ...))
{
	if (dinfo) {
		dinfo->stream = stream;
		dinfo->fprintf_func = fprintf_func;
	}
}

static inline disassembler_ftype disassembler(int arch, int big_endian,
    unsigned long mach, void *abfd)
{
	(void)arch; (void)big_endian; (void)mach; (void)abfd;
	return NULL;  /* Disassembly not supported */
}

static inline int buffer_read_memory(uint64_t memaddr, uint8_t *myaddr,
    unsigned int length, disassemble_info *dinfo)
{
	(void)memaddr; (void)myaddr; (void)length; (void)dinfo;
	return -1;
}

static inline void perror_memory(int status, uint64_t memaddr,
    disassemble_info *dinfo)
{
	(void)status; (void)memaddr; (void)dinfo;
}

static inline void generic_print_address(uint64_t addr, disassemble_info *dinfo)
{
	if (dinfo && dinfo->fprintf_func)
		dinfo->fprintf_func(dinfo->stream, "0x%lx", (unsigned long)addr);
}

#endif /* _DIS_ASM_H */
