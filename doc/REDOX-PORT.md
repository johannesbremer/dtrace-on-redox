# DTrace for RedoxOS

This document describes the port of DTrace to RedoxOS using the rbpf
user-space eBPF virtual machine.

## Overview

DTrace traditionally relies on Linux kernel BPF syscalls to load and execute
eBPF programs. To enable DTrace to run on RedoxOS, we use rbpf - a user-space
eBPF virtual machine written in Rust.

### Features

**Supported:**

- `dtrace:::BEGIN` - fires at start of tracing
- `dtrace:::END` - fires at end of tracing
- `dtrace:::ERROR` - fires on errors
- `profile:::tick-*` - timer-based probes (emulated)
- BPF program execution via interpreter
- User-space helper function emulation

**Not Supported (requires kernel):**

- Kernel tracing (`fbt`, `sdt`, `syscall`, etc.)
- JIT compilation (mmap restrictions on RedoxOS)
- External process tracing

### Architecture

```
┌─────────────────────────────────────────────────────────────┐
│                      DTrace CLI                              │
│                    (cmd/dtrace.c)                            │
└─────────────────────────────────────────────────────────────┘
                              │
                              ▼
┌─────────────────────────────────────────────────────────────┐
│                    libdtrace                                 │
│         D compiler, code generation, etc.                    │
└─────────────────────────────────────────────────────────────┘
                              │
                              ▼
┌─────────────────────────────────────────────────────────────┐
│              BPF Backend Abstraction Layer                   │
│                   (dt_bpf_backend.h)                         │
└─────────────────────────────────────────────────────────────┘
                              │
                              ▼
┌─────────────────────────────────────────────────────────────┐
│                    rbpf Backend                              │
│           (dt_bpf_backend_rbpf.c + rbpf_ffi)                │
│                                                              │
│  • User-space BPF maps (hash, array)                        │
│  • BPF program interpreter                                   │
│  • Helper function emulation                                 │
└─────────────────────────────────────────────────────────────┘
                              │
                              ▼
┌─────────────────────────────────────────────────────────────┐
│                   RedoxOS Self-Trace                         │
│                  (dt_prov_redox.c)                          │
│                                                              │
│  • Timer-based probes using POSIX timers                    │
│  • BEGIN/END/ERROR probe triggering                         │
│  • Self-process tracing only                                │
└─────────────────────────────────────────────────────────────┘
```

## Building

### Prerequisites

1. RedoxOS toolchain (`x86_64-unknown-redox-gcc`, etc.)
2. Rust toolchain with RedoxOS target:
   ```bash
   rustup target add x86_64-unknown-redox
   ```

### Build Steps

#### 1. Build the rbpf FFI library

```bash
cd libdtrace/rbpf_ffi
cargo build --release --target x86_64-unknown-redox --features no-jit
```

The library will be created at:

- `target/x86_64-unknown-redox/release/librbpf_ffi.a`

#### 2. Build DTrace for RedoxOS

Using the Makefile:

```bash
make TARGET=x86_64-unknown-redox
```

Or manually:

```bash
export CC=x86_64-unknown-redox-gcc
export CFLAGS="-D__redox__ -DDT_BPF_BACKEND_RBPF -DDT_SELF_TRACE_ONLY"
export LDFLAGS="-Llibdtrace/rbpf_ffi/target/x86_64-unknown-redox/release"
export LDLIBS="-lrbpf_ffi"

# Compile...
```

### Using the Redox Cookbook

Copy the `redox/recipe.toml` to your Redox cookbook:

```bash
cp redox/recipe.toml /path/to/redox/cookbook/recipes/tools/dtrace/
```

Then build with:

```bash
make r.dtrace
```

## Usage

On RedoxOS, DTrace runs in self-trace mode:

```bash
# Basic hello world
dtrace -n 'BEGIN { printf("Hello, RedoxOS!"); exit(0); }'

# Timer probe (emulated)
dtrace -n 'profile:::tick-1sec { printf("tick"); }'
```

## Files

| File                              | Description                 |
| --------------------------------- | --------------------------- |
| `include/config_redox.h`          | RedoxOS configuration       |
| `include/port_redox.h`            | RedoxOS portability header  |
| `libport/port_redox.c`            | RedoxOS platform functions  |
| `libdtrace/dt_prov_redox.c`       | RedoxOS self-trace provider |
| `libdtrace/dt_bpf_backend_rbpf.c` | rbpf backend implementation |
| `libdtrace/dt_bpf_helpers_rbpf.c` | BPF helper emulation        |
| `libdtrace/rbpf_ffi/`             | Rust FFI bindings for rbpf  |
| `redox/recipe.toml`               | Redox cookbook recipe       |
| `examples/dtrace_demo_redox.c`    | Demo program                |
| `Makeoptions.redox`               | RedoxOS build options       |

## Limitations

1. **No Kernel Tracing**: rbpf runs entirely in user-space, so kernel
   tracing is not possible.

2. **No JIT**: RedoxOS mmap restrictions prevent JIT compilation.
   The interpreter is used instead.

3. **Self-Trace Only**: DTrace can only trace itself, not other processes.

4. **No BTF**: BTF (BPF Type Format) is Linux-specific.

5. **Performance**: User-space interpretation is slower than kernel BPF.

## Future Work

1. External process tracing (when RedoxOS supports ptrace-like APIs)
2. USDT (User-level Statically Defined Tracing) support
3. More complete D language support
4. Performance improvements

## References

- [rbpf GitHub](https://github.com/qmonnet/rbpf)
- [DTrace](https://dtrace.org/)
- [RedoxOS](https://www.redox-os.org/)
- [eBPF Specification](https://docs.kernel.org/bpf/)
