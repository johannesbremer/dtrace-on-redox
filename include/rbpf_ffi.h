/*
 * Oracle Linux DTrace.
 * Copyright (c) 2025, Oracle and/or its affiliates. All rights reserved.
 * Licensed under the Universal Permissive License v 1.0 as shown at
 * http://oss.oracle.com/licenses/upl.
 *
 * rbpf FFI C Header
 *
 * C bindings for the rbpf user-space eBPF virtual machine.
 * These functions are implemented in Rust and compiled into a static library.
 */

#ifndef _RBPF_FFI_H
#define _RBPF_FFI_H

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Create a new rbpf VM instance with the given program.
 *
 * @param prog      Pointer to eBPF bytecode
 * @param prog_len  Length of the bytecode in bytes
 * @return          Opaque pointer to VM instance, or NULL on error
 */
void *rbpf_vm_new(const uint8_t *prog, size_t prog_len);

/**
 * Destroy an rbpf VM instance.
 *
 * @param vm  VM instance created by rbpf_vm_new()
 */
void rbpf_vm_destroy(void *vm);

/**
 * Type for BPF helper functions.
 */
typedef uint64_t (*rbpf_helper_fn)(uint64_t, uint64_t, uint64_t,
                                   uint64_t, uint64_t);

/**
 * Register a helper function with the VM.
 *
 * @param vm    VM instance
 * @param idx   Helper function index (used in BPF call instructions)
 * @param func  Helper function to register
 * @return      0 on success, -1 on error
 */
int rbpf_vm_register_helper(void *vm, uint32_t idx, rbpf_helper_fn func);

/**
 * Execute the BPF program using the interpreter.
 *
 * @param vm       VM instance
 * @param mem      Pointer to memory buffer (packet data)
 * @param mem_len  Length of memory buffer
 * @return         Program return value, or UINT64_MAX on error
 */
uint64_t rbpf_vm_exec(void *vm, const uint8_t *mem, size_t mem_len);

/**
 * JIT compile the BPF program.
 *
 * @param vm  VM instance
 * @return    0 on success, -1 on error or if JIT not supported
 */
int rbpf_vm_jit_compile(void *vm);

/**
 * Execute the JIT-compiled BPF program.
 *
 * @param vm       VM instance
 * @param mem      Pointer to memory buffer (packet data)
 * @param mem_len  Length of memory buffer
 * @return         Program return value, or UINT64_MAX on error
 */
uint64_t rbpf_vm_exec_jit(void *vm, const uint8_t *mem, size_t mem_len);

/**
 * Allow all memory access in the VM.
 *
 * This disables memory bounds checking, which is useful for DTrace
 * where helpers return pointers to user-space memory that we trust.
 *
 * @param vm  VM instance
 * @return    0 on success, -1 on error
 */
int rbpf_vm_allow_all_memory(void *vm);

/**
 * Disassemble eBPF bytecode to human-readable format.
 *
 * @param prog      Pointer to eBPF bytecode
 * @param prog_len  Length of the bytecode in bytes
 * @return          Newly allocated string (must be freed with rbpf_free_string)
 */
char *rbpf_disassemble(const uint8_t *prog, size_t prog_len);

/**
 * Free a string allocated by rbpf FFI functions.
 *
 * @param s  String to free
 */
void rbpf_free_string(char *s);

/**
 * Assemble eBPF assembly into bytecode.
 *
 * @param asm_str      Null-terminated assembly string
 * @param out_buf      Buffer to write assembled bytecode
 * @param out_buf_len  Length of output buffer
 * @return             Length of assembled program, or -1 on error
 */
int64_t rbpf_assemble(const char *asm_str, uint8_t *out_buf, size_t out_buf_len);

/**
 * Get the version of rbpf being used.
 *
 * @return  Static version string
 */
const char *rbpf_version(void);

#ifdef __cplusplus
}
#endif

#endif /* _RBPF_FFI_H */
