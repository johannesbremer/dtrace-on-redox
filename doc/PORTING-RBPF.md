# DTrace Portability: BPF Backend Abstraction

This document describes the BPF backend abstraction layer introduced to enable
DTrace to run on non-Linux operating systems, particularly RedoxOS.

## Overview

DTrace traditionally relies on Linux kernel BPF syscalls to load and execute
eBPF programs. To enable portability to other operating systems, we've introduced
an abstraction layer that can use different backends:

1. **Linux Backend** (`DT_BPF_BACKEND_LINUX`): Uses native Linux BPF syscalls.
   This is the default on Linux systems.

2. **rbpf Backend** (`DT_BPF_BACKEND_RBPF`): Uses the rbpf user-space eBPF
   virtual machine. This enables DTrace to run on non-Linux systems.

## Architecture

```
┌─────────────────────────────────────────────────────────────┐
│                      DTrace Core                             │
│  (dt_bpf.c, dt_consume.c, dt_prov_*.c, etc.)                │
└─────────────────────────────────────────────────────────────┘
                              │
                              ▼
┌─────────────────────────────────────────────────────────────┐
│              BPF Backend Abstraction Layer                   │
│                   (dt_bpf_backend.h)                         │
│                                                              │
│  • dt_bpf_backend_ops_t - Operations structure               │
│  • Portable type definitions                                 │
│  • Convenience macros                                        │
└─────────────────────────────────────────────────────────────┘
                              │
              ┌───────────────┼───────────────┐
              ▼               ▼               ▼
┌─────────────────┐ ┌─────────────────┐ ┌─────────────────┐
│  Linux Backend  │ │  rbpf Backend   │ │ Future Backends │
│   (native BPF)  │ │ (user-space VM) │ │   (e.g., uBPF)  │
└─────────────────┘ └─────────────────┘ └─────────────────┘
```

## Files

| File                               | Description                       |
| ---------------------------------- | --------------------------------- |
| `include/dt_bpf_backend.h`         | Backend abstraction interface     |
| `libdtrace/dt_bpf_backend.c`       | Backend selection and management  |
| `libdtrace/dt_bpf_backend_linux.c` | Linux kernel BPF implementation   |
| `libdtrace/dt_bpf_backend_rbpf.c`  | rbpf user-space VM implementation |
| `libdtrace/rbpf_ffi/`              | Rust FFI bindings for rbpf        |
| `include/rbpf_ffi.h`               | C header for rbpf FFI functions   |

## Backend Operations

The `dt_bpf_backend_ops_t` structure defines all BPF operations:

### Map Operations

- `map_create` - Create a BPF map
- `map_lookup` - Look up a value by key
- `map_update` - Update or insert a value
- `map_delete` - Delete a key
- `map_next_key` - Iterate over keys
- `map_close` - Close/free a map
- `map_create_meta` - Create map-of-maps
- `map_get_fd_by_id` - Get map handle by ID

### Program Operations

- `prog_load` - Load a BPF program
- `prog_close` - Close/free a program
- `prog_exec` - Execute program (interpreter)
- `prog_exec_jit` - Execute JIT-compiled program
- `prog_jit_compile` - JIT compile a program

### Other Operations

- `register_helper` - Register helper functions
- `btf_*` - BTF operations (Linux-specific)
- `raw_tracepoint_open` - Attach to tracepoints
- `perf_event_open` - Perf event operations

## Building with rbpf Backend

### Prerequisites

1. Rust toolchain (rustc, cargo)
2. rbpf crate (will be downloaded by cargo)

### Build Steps

```bash
# Build the rbpf FFI library
cd libdtrace/rbpf_ffi
cargo build --release

# The library will be at:
# target/release/librbpf_ffi.a (static)
# target/release/librbpf_ffi.so (shared)

# Then build DTrace with rbpf backend enabled
cd ../..
make DT_BPF_BACKEND_RBPF=1
```

### Selecting Backend at Runtime

```c
#include <dt_bpf_backend.h>

// Use Linux backend (default on Linux)
dt_bpf_backend_select(DT_BPF_BACKEND_LINUX);

// Use rbpf backend
dt_bpf_backend_select(DT_BPF_BACKEND_RBPF);

// Auto-detect best backend for platform
dt_bpf_backend_init_default();
```

## Porting to RedoxOS

To port DTrace to RedoxOS:

1. **Build rbpf FFI library for Redox**:

   ```bash
   cargo build --release --target x86_64-unknown-redox
   ```

2. **Configure build system**:

   - Set `DT_BPF_BACKEND_RBPF=1`
   - Link against `librbpf_ffi.a`
   - Disable Linux-specific features

3. **Implement platform-specific code**:
   - Replace `syscall()` with Redox equivalents
   - Implement perf event alternatives
   - Provide probe point discovery mechanism

## Limitations of rbpf Backend

The rbpf backend has some limitations compared to the Linux kernel backend:

1. **No Kernel Tracing**: rbpf runs entirely in user-space, so it cannot
   trace kernel functions, syscalls, or kernel tracepoints.

2. **No BTF Support**: BTF (BPF Type Format) is Linux-specific.

3. **Limited Helpers**: Only user-space helper functions are available.
   Kernel helpers like `bpf_probe_read` must be emulated.

4. **No perf_event_open**: Must use alternative event sources.

5. **Performance**: User-space execution is slower than kernel BPF, though
   JIT compilation helps.

## Future Work

1. **Complete refactoring of dt_bpf.c**: Migrate all BPF operations to use
   the abstraction layer macros.

2. **Helper emulation**: Implement user-space equivalents of common BPF
   helpers for the rbpf backend.

3. **Event sources**: Design probe point discovery for non-Linux systems.

4. **Testing**: Create comprehensive tests for the rbpf backend.

5. **Documentation**: Add platform-specific porting guides.

## References

- [rbpf GitHub](https://github.com/qmonnet/rbpf)
- [rbpf Documentation](https://docs.rs/rbpf)
- [eBPF Specification](https://docs.kernel.org/bpf/)
- [RedoxOS](https://www.redox-os.org/)
