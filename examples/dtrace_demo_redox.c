/*
 * Oracle Linux DTrace - RedoxOS Port
 * Copyright (c) 2025, Oracle and/or its affiliates. All rights reserved.
 * Licensed under the Universal Permissive License v 1.0 as shown at
 * http://oss.oracle.com/licenses/upl.
 *
 * DTrace Self-Trace Demo for RedoxOS
 *
 * This demo shows how DTrace self-tracing works on RedoxOS using the
 * rbpf user-space eBPF virtual machine.
 *
 * Build:
 *   cargo build --release --target x86_64-unknown-redox --features no-jit
 *   x86_64-unknown-redox-gcc -o dtrace_demo dtrace_demo_redox.c \
 *       -I../include -L../libdtrace/rbpf_ffi/target/x86_64-unknown-redox/release \
 *       -lrbpf_ffi -D__redox__
 *
 * Run:
 *   ./dtrace_demo
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <time.h>
#include <unistd.h>

#ifdef __redox__
#include "config_redox.h"
#include "port_redox.h"
#else
/* For testing on Linux */
typedef int64_t hrtime_t;
static inline hrtime_t gethrtime(void) {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (hrtime_t)ts.tv_sec * 1000000000LL + ts.tv_nsec;
}
#endif

/*
 * Simple BPF program that just returns 42
 * 
 * Instructions:
 *   mov64 r0, 42
 *   exit
 */
static const uint8_t simple_prog[] = {
    0xb7, 0x00, 0x00, 0x00, 0x2a, 0x00, 0x00, 0x00,  /* mov64 r0, 42 */
    0x95, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  /* exit */
};

/*
 * BPF program that reads a byte from memory
 * 
 * Instructions:
 *   ldxb r0, [r1+0]   ; Load byte from memory at r1+0
 *   exit
 */
static const uint8_t mem_read_prog[] = {
    0x71, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  /* ldxb r0, [r1+0] */
    0x95, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  /* exit */
};

/*
 * BPF program that adds two values from memory
 * 
 * Instructions:
 *   ldxw r2, [r1+0]   ; Load 4-byte value at offset 0
 *   ldxw r3, [r1+4]   ; Load 4-byte value at offset 4
 *   add64 r2, r3      ; Add them
 *   mov64 r0, r2      ; Move result to r0
 *   exit
 */
static const uint8_t add_prog[] = {
    0x61, 0x12, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  /* ldxw r2, [r1+0] */
    0x61, 0x13, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00,  /* ldxw r3, [r1+4] */
    0x0f, 0x32, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  /* add64 r2, r3 */
    0xbf, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  /* mov64 r0, r2 */
    0x95, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  /* exit */
};

/* FFI declarations for rbpf */
extern void *rbpf_vm_new(const uint8_t *prog, size_t prog_len);
extern void rbpf_vm_destroy(void *vm);
extern uint64_t rbpf_vm_exec(void *vm, const uint8_t *mem, size_t mem_len);
extern const char *rbpf_version(void);

static void
print_separator(void)
{
    printf("========================================\n");
}

static void
test_simple_program(void)
{
    void *vm;
    uint64_t result;
    hrtime_t start, end;

    printf("\nTest 1: Simple Program (return 42)\n");
    print_separator();

    vm = rbpf_vm_new(simple_prog, sizeof(simple_prog));
    if (vm == NULL) {
        fprintf(stderr, "Failed to create VM\n");
        return;
    }

    start = gethrtime();
    result = rbpf_vm_exec(vm, NULL, 0);
    end = gethrtime();

    printf("Result: %lu (expected: 42)\n", (unsigned long)result);
    printf("Execution time: %lld ns\n", (long long)(end - start));
    printf("Status: %s\n", result == 42 ? "PASS" : "FAIL");

    rbpf_vm_destroy(vm);
}

static void
test_memory_read(void)
{
    void *vm;
    uint64_t result;
    uint8_t mem[4] = { 0xAA, 0xBB, 0xCC, 0xDD };
    hrtime_t start, end;

    printf("\nTest 2: Memory Read (first byte)\n");
    print_separator();

    vm = rbpf_vm_new(mem_read_prog, sizeof(mem_read_prog));
    if (vm == NULL) {
        fprintf(stderr, "Failed to create VM\n");
        return;
    }

    start = gethrtime();
    result = rbpf_vm_exec(vm, mem, sizeof(mem));
    end = gethrtime();

    printf("Memory: [0x%02X, 0x%02X, 0x%02X, 0x%02X]\n",
           mem[0], mem[1], mem[2], mem[3]);
    printf("Result: 0x%02lX (expected: 0xAA)\n", (unsigned long)result);
    printf("Execution time: %lld ns\n", (long long)(end - start));
    printf("Status: %s\n", result == 0xAA ? "PASS" : "FAIL");

    rbpf_vm_destroy(vm);
}

static void
test_addition(void)
{
    void *vm;
    uint64_t result;
    uint32_t mem[2] = { 100, 200 };
    hrtime_t start, end;

    printf("\nTest 3: Addition (100 + 200)\n");
    print_separator();

    vm = rbpf_vm_new(add_prog, sizeof(add_prog));
    if (vm == NULL) {
        fprintf(stderr, "Failed to create VM\n");
        return;
    }

    start = gethrtime();
    result = rbpf_vm_exec(vm, (uint8_t *)mem, sizeof(mem));
    end = gethrtime();

    printf("Operands: %u + %u\n", mem[0], mem[1]);
    printf("Result: %lu (expected: 300)\n", (unsigned long)result);
    printf("Execution time: %lld ns\n", (long long)(end - start));
    printf("Status: %s\n", result == 300 ? "PASS" : "FAIL");

    rbpf_vm_destroy(vm);
}

static void
test_performance(void)
{
    void *vm;
    hrtime_t start, end, total;
    int iterations = 10000;
    int i;

    printf("\nTest 4: Performance (%d iterations)\n", iterations);
    print_separator();

    vm = rbpf_vm_new(simple_prog, sizeof(simple_prog));
    if (vm == NULL) {
        fprintf(stderr, "Failed to create VM\n");
        return;
    }

    start = gethrtime();
    for (i = 0; i < iterations; i++) {
        (void)rbpf_vm_exec(vm, NULL, 0);
    }
    end = gethrtime();
    total = end - start;

    printf("Total time: %lld ns\n", (long long)total);
    printf("Average per iteration: %lld ns\n", (long long)(total / iterations));
    printf("Iterations per second: %lld\n", 
           (long long)(iterations * 1000000000LL / total));

    rbpf_vm_destroy(vm);
}

int
main(int argc, char *argv[])
{
    (void)argc;
    (void)argv;

    printf("DTrace Self-Trace Demo for RedoxOS\n");
    print_separator();
#ifdef __redox__
    printf("Platform: RedoxOS\n");
#else
    printf("Platform: Linux (test mode)\n");
#endif
    printf("rbpf version: %s\n", rbpf_version());
    printf("PID: %d\n", getpid());

    test_simple_program();
    test_memory_read();
    test_addition();
    test_performance();

    printf("\n");
    print_separator();
    printf("All tests completed!\n");
    printf("\nThis demonstrates that DTrace's BPF execution engine\n");
    printf("works on RedoxOS using the rbpf user-space VM.\n");
    printf("\nIn a full implementation, these BPF programs would be\n");
    printf("generated from D scripts and would trace the dtrace\n");
    printf("process itself.\n");

    return 0;
}
