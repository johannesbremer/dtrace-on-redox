//! FFI bindings for rbpf to enable DTrace on non-Linux systems
//!
//! This crate provides C-compatible FFI functions that wrap rbpf's
//! user-space eBPF virtual machine, allowing DTrace to execute BPF
//! programs without relying on Linux kernel BPF syscalls.
//!
//! Platform support:
//!   - Linux: Full support including JIT
//!   - RedoxOS: Interpreter only (no JIT due to mmap restrictions)
//!   - Other Unix: Interpreter only
//!
//! Copyright (c) 2025, Oracle and/or its affiliates. All rights reserved.
//! Licensed under the Universal Permissive License v 1.0 as shown at
//! http://oss.oracle.com/licenses/upl.

use std::collections::HashMap;
use std::ffi::c_void;
use std::ptr;
use std::slice;

use rbpf::EbpfVmRaw;

/// Type for BPF helper functions
type HelperFn = fn(u64, u64, u64, u64, u64) -> u64;

/// Wrapper around rbpf VM with helper storage
#[allow(dead_code)]
struct RbpfVmWrapper {
    vm: EbpfVmRaw<'static>,
    program: Vec<u8>,
    helpers: HashMap<u32, HelperFn>,
    jit_compiled: bool,
}

/// Create a new rbpf VM instance with the given program
///
/// # Safety
/// The caller must ensure that `prog` points to valid memory of at least
/// `prog_len` bytes containing valid eBPF bytecode.
#[no_mangle]
pub unsafe extern "C" fn rbpf_vm_new(
    prog: *const u8,
    prog_len: usize,
) -> *mut c_void {
    if prog.is_null() || prog_len == 0 {
        return ptr::null_mut();
    }

    // Copy the program to owned memory
    let program = slice::from_raw_parts(prog, prog_len).to_vec();

    // Leak the program to get a static lifetime (we'll manage the memory ourselves)
    let program_static: &'static [u8] = Box::leak(program.clone().into_boxed_slice());

    match EbpfVmRaw::new(Some(program_static)) {
        Ok(vm) => {
            let wrapper = Box::new(RbpfVmWrapper {
                vm,
                program,
                helpers: HashMap::new(),
                jit_compiled: false,
            });
            Box::into_raw(wrapper) as *mut c_void
        }
        Err(_) => ptr::null_mut(),
    }
}

/// Destroy an rbpf VM instance
///
/// # Safety
/// The caller must ensure that `vm` is a valid pointer returned by `rbpf_vm_new`
/// and has not been destroyed before.
#[no_mangle]
pub unsafe extern "C" fn rbpf_vm_destroy(vm: *mut c_void) {
    if !vm.is_null() {
        // Take ownership and drop
        let _ = Box::from_raw(vm as *mut RbpfVmWrapper);
    }
}

/// Register a helper function with the VM
///
/// # Safety
/// The caller must ensure that `vm` is a valid pointer returned by `rbpf_vm_new`.
#[no_mangle]
pub unsafe extern "C" fn rbpf_vm_register_helper(
    vm: *mut c_void,
    idx: u32,
    func: Option<extern "C" fn(u64, u64, u64, u64, u64) -> u64>,
) -> i32 {
    if vm.is_null() {
        return -1;
    }

    let wrapper = &mut *(vm as *mut RbpfVmWrapper);

    if let Some(f) = func {
        // Convert the C function pointer to a Rust function
        // This is safe because the function signature matches
        let helper: HelperFn = std::mem::transmute(f);

        match wrapper.vm.register_helper(idx, helper) {
            Ok(()) => {
                wrapper.helpers.insert(idx, helper);
                0
            }
            Err(_) => -1,
        }
    } else {
        -1
    }
}

/// Allow all memory access in the VM
///
/// This disables memory bounds checking, which is useful for DTrace
/// where helpers return pointers to user-space memory that we trust.
///
/// # Safety
/// The caller must ensure that `vm` is a valid pointer returned by `rbpf_vm_new`.
#[no_mangle]
pub unsafe extern "C" fn rbpf_vm_allow_all_memory(vm: *mut c_void) -> i32 {
    if vm.is_null() {
        return -1;
    }

    let wrapper = &mut *(vm as *mut RbpfVmWrapper);

    // Register a wide memory range as allowed
    // This effectively disables bounds checking for helper-returned pointers
    wrapper.vm.register_allowed_memory(0..u64::MAX);
    0
}

/// Execute the BPF program using the interpreter
///
/// # Safety
/// The caller must ensure that:
/// - `vm` is a valid pointer returned by `rbpf_vm_new`
/// - `mem` points to valid memory of at least `mem_len` bytes
#[no_mangle]
pub unsafe extern "C" fn rbpf_vm_exec(
    vm: *mut c_void,
    mem: *const u8,
    mem_len: usize,
) -> u64 {
    if vm.is_null() {
        return u64::MAX;
    }

    let wrapper = &mut *(vm as *mut RbpfVmWrapper);

    let mem_slice = if mem.is_null() || mem_len == 0 {
        &mut []
    } else {
        slice::from_raw_parts_mut(mem as *mut u8, mem_len)
    };

    match wrapper.vm.execute_program(mem_slice) {
        Ok(result) => result,
        Err(e) => {
            eprintln!("rbpf_vm_exec error: {:?}", e);
            u64::MAX
        }
    }
}

/// JIT compile the BPF program
///
/// # Safety
/// The caller must ensure that `vm` is a valid pointer returned by `rbpf_vm_new`.
///
/// Note: JIT compilation is not available on RedoxOS due to mmap restrictions.
/// On RedoxOS, this function always returns -1 and the interpreter is used instead.
#[no_mangle]
#[cfg(all(not(windows), not(target_os = "redox"), feature = "std", not(feature = "no-jit")))]
pub unsafe extern "C" fn rbpf_vm_jit_compile(vm: *mut c_void) -> i32 {
    if vm.is_null() {
        return -1;
    }

    let wrapper = &mut *(vm as *mut RbpfVmWrapper);

    match wrapper.vm.jit_compile() {
        Ok(()) => {
            wrapper.jit_compiled = true;
            0
        }
        Err(_) => -1,
    }
}

/// JIT compile stub for platforms that don't support JIT (Windows, RedoxOS, no-std)
#[no_mangle]
#[cfg(any(windows, target_os = "redox", not(feature = "std"), feature = "no-jit"))]
pub unsafe extern "C" fn rbpf_vm_jit_compile(_vm: *mut c_void) -> i32 {
    -1 // JIT not supported on this platform
}

/// Execute the JIT-compiled BPF program
///
/// # Safety
/// The caller must ensure that:
/// - `vm` is a valid pointer returned by `rbpf_vm_new`
/// - The program has been JIT-compiled with `rbpf_vm_jit_compile`
/// - `mem` points to valid memory of at least `mem_len` bytes
#[no_mangle]
#[cfg(all(not(windows), not(target_os = "redox"), feature = "std", not(feature = "no-jit")))]
pub unsafe extern "C" fn rbpf_vm_exec_jit(
    vm: *mut c_void,
    mem: *const u8,
    mem_len: usize,
) -> u64 {
    if vm.is_null() {
        return u64::MAX;
    }

    let wrapper = &mut *(vm as *mut RbpfVmWrapper);

    if !wrapper.jit_compiled {
        return u64::MAX;
    }

    let mem_slice = if mem.is_null() || mem_len == 0 {
        &mut []
    } else {
        slice::from_raw_parts_mut(mem as *mut u8, mem_len)
    };

    match wrapper.vm.execute_program_jit(mem_slice) {
        Ok(result) => result,
        Err(_) => u64::MAX,
    }
}

/// JIT execution stub for platforms that don't support JIT (Windows, RedoxOS, no-std)
#[no_mangle]
#[cfg(any(windows, target_os = "redox", not(feature = "std"), feature = "no-jit"))]
pub unsafe extern "C" fn rbpf_vm_exec_jit(
    _vm: *mut c_void,
    _mem: *const u8,
    _mem_len: usize,
) -> u64 {
    u64::MAX // JIT not supported on this platform
}

/// Disassemble eBPF bytecode to human-readable format
///
/// Returns a newly allocated string that must be freed with `rbpf_free_string`.
///
/// # Safety
/// The caller must ensure that `prog` points to valid memory of at least
/// `prog_len` bytes containing valid eBPF bytecode.
#[no_mangle]
pub unsafe extern "C" fn rbpf_disassemble(
    prog: *const u8,
    prog_len: usize,
) -> *mut libc::c_char {
    if prog.is_null() || prog_len == 0 {
        return ptr::null_mut();
    }

    let program = slice::from_raw_parts(prog, prog_len);

    // Use rbpf's disassembler to generate string output
    let output = rbpf::disassembler::to_insn_vec(program)
        .iter()
        .enumerate()
        .map(|(i, insn)| format!("{:04x}: {}", i * 8, insn.desc))
        .collect::<Vec<_>>()
        .join("\n");

    match std::ffi::CString::new(output) {
        Ok(cstr) => cstr.into_raw(),
        Err(_) => ptr::null_mut(),
    }
}

/// Free a string allocated by rbpf FFI functions
///
/// # Safety
/// The caller must ensure that `s` was returned by an rbpf FFI function
/// that allocates strings (e.g., `rbpf_disassemble`).
#[no_mangle]
pub unsafe extern "C" fn rbpf_free_string(s: *mut libc::c_char) {
    if !s.is_null() {
        let _ = std::ffi::CString::from_raw(s);
    }
}

/// Assemble eBPF assembly into bytecode
///
/// Returns the length of the assembled program, or -1 on error.
/// The assembled program is written to `out_buf` if it's large enough.
///
/// # Safety
/// The caller must ensure that:
/// - `asm_str` is a valid null-terminated C string
/// - `out_buf` points to valid memory of at least `out_buf_len` bytes
#[no_mangle]
pub unsafe extern "C" fn rbpf_assemble(
    asm_str: *const libc::c_char,
    out_buf: *mut u8,
    out_buf_len: usize,
) -> i64 {
    if asm_str.is_null() {
        return -1;
    }

    let asm_cstr = match std::ffi::CStr::from_ptr(asm_str).to_str() {
        Ok(s) => s,
        Err(_) => return -1,
    };

    match rbpf::assembler::assemble(asm_cstr) {
        Ok(bytecode) => {
            let len = bytecode.len();
            if !out_buf.is_null() && out_buf_len >= len {
                ptr::copy_nonoverlapping(bytecode.as_ptr(), out_buf, len);
            }
            len as i64
        }
        Err(_) => -1,
    }
}

/// Get the version of rbpf being used
#[no_mangle]
pub extern "C" fn rbpf_version() -> *const libc::c_char {
    // Return a static version string
    static VERSION: &[u8] = b"0.3.0\0";
    VERSION.as_ptr() as *const libc::c_char
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_vm_creation() {
        // Simple eBPF program: mov64 r0, 0x42; exit
        let prog: [u8; 16] = [
            0xb7, 0x00, 0x00, 0x00, 0x42, 0x00, 0x00, 0x00,
            0x95, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        ];

        unsafe {
            let vm = rbpf_vm_new(prog.as_ptr(), prog.len());
            assert!(!vm.is_null());

            let result = rbpf_vm_exec(vm, ptr::null(), 0);
            assert_eq!(result, 0x42);

            rbpf_vm_destroy(vm);
        }
    }

    #[test]
    fn test_vm_with_memory() {
        // eBPF program: ldxb r0, [r1+0]; exit
        let prog: [u8; 16] = [
            0x71, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x95, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        ];

        let mem: [u8; 4] = [0xAA, 0xBB, 0xCC, 0xDD];

        unsafe {
            let vm = rbpf_vm_new(prog.as_ptr(), prog.len());
            assert!(!vm.is_null());

            let result = rbpf_vm_exec(vm, mem.as_ptr(), mem.len());
            assert_eq!(result, 0xAA);

            rbpf_vm_destroy(vm);
        }
    }
}
