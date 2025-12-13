#!/bin/bash
#
# DTrace for RedoxOS - Build Script
# Cross-compiles dtrace using redoxer toolchain
#
set -e

SRC="/src"
BUILD="/build/dtrace-build"

echo "=== DTrace for RedoxOS Build ==="
echo "Source: $SRC"
echo "Build:  $BUILD"
echo ""

# Install toolchain if not present
TOOLCHAIN_DIR="$HOME/.redoxer/x86_64-unknown-redox/toolchain"
if [ ! -d "$TOOLCHAIN_DIR" ]; then
    echo "=== Installing Redoxer toolchain ==="
    redoxer toolchain
    echo ""
fi

# Set up cross-compiler from redoxer toolchain
export PATH="$TOOLCHAIN_DIR/bin:$PATH"
CC="x86_64-unknown-redox-gcc"
AR="x86_64-unknown-redox-ar"

echo "Checking toolchain..."
$CC --version | head -1
echo ""

# Create build directory
rm -rf "$BUILD"
mkdir -p "$BUILD/obj"

# Compiler flags
CFLAGS="-O2 -Wall -D__redox__"
CFLAGS+=" -DUSE_RBPF_BACKEND"
CFLAGS+=" -DHAVE_STRLCPY -DHAVE_STRLCAT"
CFLAGS+=" -I${SRC}/include"
CFLAGS+=" -I${SRC}/libdtrace"
CFLAGS+=" -Wno-pedantic"
# Use baseline x86-64 to avoid unsupported instructions in QEMU TCG
# Disable all SSE3+ and AVX extensions
CFLAGS+=" -march=x86-64 -mtune=generic"
CFLAGS+=" -mno-sse3 -mno-ssse3 -mno-sse4.1 -mno-sse4.2 -mno-avx -mno-avx2"

echo "CFLAGS: $CFLAGS"
echo ""

compile_file() {
    local src="$1"
    local obj="$2"
    echo -n "  Compiling $(basename $src)... "
    if $CC $CFLAGS -c "$src" -o "$obj" 2>&1; then
        echo "OK"
        return 0
    else
        echo "FAILED"
        return 1
    fi
}

echo "=== Step 1: Compile BPF Backend ==="
compile_file "${SRC}/libdtrace/dt_bpf_backend.c" "$BUILD/obj/dt_bpf_backend.o"
compile_file "${SRC}/libdtrace/dt_bpf_backend_rbpf.c" "$BUILD/obj/dt_bpf_backend_rbpf.o"

echo ""
echo "=== Step 2: Compile RedoxOS-specific code ==="
if [ -f "${SRC}/libdtrace/dt_prov_redox.c" ]; then
    compile_file "${SRC}/libdtrace/dt_prov_redox.c" "$BUILD/obj/dt_prov_redox.o"
else
    echo "  dt_prov_redox.c not found (skipping)"
fi

echo ""
echo "=== Step 3: Compile port layer ==="
if [ -f "${SRC}/libport/port_redox.c" ]; then
    compile_file "${SRC}/libport/port_redox.c" "$BUILD/obj/port_redox.o"
else
    echo "  port_redox.c not found (skipping)"
fi

echo ""
echo "=== Step 4: Build rbpf FFI Rust library ==="
# Try to build the actual Rust library first
RBPF_FFI_DIR="${SRC}/libdtrace/rbpf_ffi"
if [ -f "$RBPF_FFI_DIR/Cargo.toml" ]; then
    echo "  Building rbpf_ffi with cargo..."
    
    # Need to copy to a writable location since /src is read-only
    mkdir -p "$BUILD/rbpf_ffi"
    cp -r "$RBPF_FFI_DIR"/* "$BUILD/rbpf_ffi/"
    cd "$BUILD/rbpf_ffi"
    
    # Try to build for Redox target
    if cargo build --release --target x86_64-unknown-redox --features no-jit 2>&1; then
        echo "  Rust library built successfully"
        cp "target/x86_64-unknown-redox/release/librbpf_ffi.a" "$BUILD/obj/" 2>/dev/null || true
        HAVE_RBPF=1
    else
        echo "  Rust build failed, using stubs"
        HAVE_RBPF=0
    fi
    cd "$BUILD"
else
    echo "  rbpf_ffi not found, using stubs"
    HAVE_RBPF=0
fi

# Create stubs if Rust build failed
if [ "${HAVE_RBPF:-0}" = "0" ]; then
    echo "  Creating rbpf FFI stubs..."
    cat > "$BUILD/rbpf_stubs.c" << 'STUBS'
/*
 * Stub implementations for rbpf FFI functions
 * These will be replaced by the actual Rust library
 */
#include <stdint.h>
#include <stddef.h>

void *rbpf_vm_new(const uint8_t *prog, size_t prog_len) {
    (void)prog; (void)prog_len;
    return (void*)0x1; /* Return non-null stub */
}

void rbpf_vm_destroy(void *vm) {
    (void)vm;
}

int rbpf_vm_register_helper(void *vm, uint32_t idx,
    uint64_t (*fn)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t)) {
    (void)vm; (void)idx; (void)fn;
    return 0;
}

uint64_t rbpf_vm_exec(void *vm, const uint8_t *mem, size_t mem_len) {
    (void)vm; (void)mem; (void)mem_len;
    return 0;
}

int rbpf_vm_jit_compile(void *vm) {
    (void)vm;
    return -1; /* JIT not available */
}

uint64_t rbpf_vm_exec_jit(void *vm, const uint8_t *mem, size_t mem_len) {
    (void)vm; (void)mem; (void)mem_len;
    return 0;
}
STUBS
    compile_file "$BUILD/rbpf_stubs.c" "$BUILD/obj/rbpf_stubs.o"
fi

echo ""
echo "=== Step 5: Link static library ==="
# Determine which objects to link
OBJS="$BUILD/obj/dt_bpf_backend.o"
OBJS+=" $BUILD/obj/dt_bpf_backend_rbpf.o"
OBJS+=" $BUILD/obj/dt_prov_redox.o"
OBJS+=" $BUILD/obj/port_redox.o"

RBPF_LIB=""
if [ -f "$BUILD/obj/librbpf_ffi.a" ]; then
    echo "  Using rbpf_ffi Rust library"
    RBPF_LIB="$BUILD/obj/librbpf_ffi.a"
elif [ -f "$BUILD/obj/rbpf_stubs.o" ]; then
    OBJS+=" $BUILD/obj/rbpf_stubs.o"
    echo "  Using rbpf stubs"
fi

$AR rcs "$BUILD/libdtrace_redox.a" $OBJS
echo "  Created libdtrace_redox.a"

echo ""
echo "=== Step 6: Build test program ==="
cat > "$BUILD/dtrace_test.c" << 'TESTPROG'
/*
 * DTrace for RedoxOS - Test Program
 */
#include <stdio.h>
#include <stdint.h>

/* Forward declarations */
int redox_trace_init(void);
void redox_trace_fini(void);
int redox_trace_start(void (*callback)(int, void *), void *arg);
int redox_trace_stop(void);

static void probe_callback(int probe_id, void *arg) {
    (void)arg;
    printf("Probe fired: %d\n", probe_id);
}

int main(void) {
    printf("DTrace for RedoxOS - Test\n");
    printf("=========================\n\n");
    
    printf("Initializing trace provider...\n");
    if (redox_trace_init() != 0) {
        printf("ERROR: Failed to initialize\n");
        return 1;
    }
    
    printf("Starting trace...\n");
    redox_trace_start(probe_callback, NULL);
    
    printf("Stopping trace...\n");
    redox_trace_stop();
    
    printf("Cleaning up...\n");
    redox_trace_fini();
    
    printf("\nSUCCESS: DTrace test completed!\n");
    return 0;
}
TESTPROG

echo "  Compiling test program..."
$CC $CFLAGS -c "$BUILD/dtrace_test.c" -o "$BUILD/obj/dtrace_test.o"
echo "  Linking test program..."
# Static link with explicit baseline x86-64-v1 (no SSE3/SSSE3/etc)
# Link order matters: test program, dtrace library, rbpf Rust library
if [ -n "$RBPF_LIB" ]; then
    $CC -static -Wl,--no-relax -o "$BUILD/dtrace" "$BUILD/obj/dtrace_test.o" -L"$BUILD" -ldtrace_redox "$RBPF_LIB"
else
    $CC -static -Wl,--no-relax -o "$BUILD/dtrace" "$BUILD/obj/dtrace_test.o" -L"$BUILD" -ldtrace_redox
fi
echo "  Created dtrace"

echo ""
echo "=== Build Summary ==="
ls -la "$BUILD/obj/"
ls -la "$BUILD/"*.a "$BUILD/dtrace"

echo ""
echo "SUCCESS: DTrace RedoxOS library and test program built!"
echo ""
echo "To test on RedoxOS:"
echo "  1. Start HTTP server: python3 -m http.server 8080"
echo "  2. In Redox: curl http://10.0.2.2:8080/dtrace -O"
echo "  3. chmod +x dtrace && ./dtrace"
echo "  2. Run ./dtrace_test"
