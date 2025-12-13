#!/bin/bash
#
# Oracle Linux DTrace - RedoxOS Port
# Copyright (c) 2025, Oracle and/or its affiliates. All rights reserved.
# Licensed under the Universal Permissive License v 1.0 as shown at
# http://oss.oracle.com/licenses/upl.
#
# Build script for DTrace on RedoxOS
#
# Usage:
#   ./build-redox.sh [command]
#
# Commands:
#   build      - Build DTrace for RedoxOS (default)
#   clean      - Clean build artifacts
#   rbpf       - Build only the rbpf FFI library
#   demo       - Build and run the demo (on Linux for testing)
#   test       - Run tests on Linux with rbpf backend
#   help       - Show this help message

set -e

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
TARGET="x86_64-unknown-redox"
RBPF_DIR="${SCRIPT_DIR}/libdtrace/rbpf_ffi"

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

info() {
    echo -e "${GREEN}[INFO]${NC} $1"
}

warn() {
    echo -e "${YELLOW}[WARN]${NC} $1"
}

error() {
    echo -e "${RED}[ERROR]${NC} $1"
    exit 1
}

# Check for required tools
check_tools() {
    info "Checking for required tools..."
    
    if ! command -v cargo &> /dev/null; then
        error "cargo not found. Please install Rust: https://rustup.rs/"
    fi
    
    if ! command -v rustup &> /dev/null; then
        error "rustup not found. Please install Rust: https://rustup.rs/"
    fi
    
    info "All required tools found."
}

# Check for RedoxOS target
check_redox_target() {
    info "Checking for RedoxOS Rust target..."
    
    if ! rustup target list --installed | grep -q "$TARGET"; then
        warn "RedoxOS target not installed. Installing..."
        rustup target add "$TARGET" || {
            warn "Failed to add target. You may need to configure a custom toolchain."
            warn "See: https://doc.redox-os.org/book/ch02-05-compiling-redox.html"
        }
    fi
    
    info "RedoxOS target is available."
}

# Build the rbpf FFI library
build_rbpf() {
    info "Building rbpf FFI library..."
    
    cd "$RBPF_DIR"
    
    if [ "$1" = "redox" ]; then
        check_redox_target
        cargo build --release --target "$TARGET" --features no-jit
        info "rbpf FFI library built for RedoxOS at:"
        info "  ${RBPF_DIR}/target/${TARGET}/release/librbpf_ffi.a"
    else
        cargo build --release
        info "rbpf FFI library built for host at:"
        info "  ${RBPF_DIR}/target/release/librbpf_ffi.a"
    fi
    
    cd "$SCRIPT_DIR"
}

# Build DTrace for RedoxOS
build_dtrace() {
    info "Building DTrace for RedoxOS..."
    
    build_rbpf redox
    
    # For now, just show what would be built
    info "DTrace build configuration for RedoxOS:"
    echo "  TARGET: ${TARGET}"
    echo "  CFLAGS: -D__redox__ -DDT_BPF_BACKEND_RBPF -DDT_SELF_TRACE_ONLY"
    echo "  LDFLAGS: -L${RBPF_DIR}/target/${TARGET}/release"
    echo "  LDLIBS: -lrbpf_ffi"
    
    warn "Full DTrace build requires RedoxOS cross-compilation toolchain."
    warn "Use the Redox cookbook recipe for a complete build."
    
    info "To build using Redox cookbook:"
    echo "  1. Copy redox/recipe.toml to your cookbook"
    echo "  2. Run: make r.dtrace"
}

# Build and run demo on host (for testing)
build_demo() {
    info "Building demo on host for testing..."
    
    build_rbpf host
    
    cd "$SCRIPT_DIR"
    
    DEMO_SRC="examples/dtrace_demo_redox.c"
    DEMO_BIN="_build/dtrace_demo"
    
    mkdir -p _build
    
    info "Compiling demo..."
    gcc -o "$DEMO_BIN" "$DEMO_SRC" \
        -I"include" \
        -L"${RBPF_DIR}/target/release" \
        -lrbpf_ffi -lpthread -ldl -lm \
        -Wall -O2
    
    info "Running demo..."
    echo ""
    LD_LIBRARY_PATH="${RBPF_DIR}/target/release:$LD_LIBRARY_PATH" "./$DEMO_BIN"
}

# Run tests with rbpf backend on Linux
run_tests() {
    info "Running tests with rbpf backend on Linux..."
    
    cd "$RBPF_DIR"
    cargo test --release
    
    info "rbpf FFI tests passed."
    
    cd "$SCRIPT_DIR"
    
    # Run the demo as a basic integration test
    build_demo
}

# Clean build artifacts
clean() {
    info "Cleaning build artifacts..."
    
    rm -rf _build/
    
    cd "$RBPF_DIR"
    cargo clean
    cd "$SCRIPT_DIR"
    
    info "Clean complete."
}

# Show help
show_help() {
    echo "DTrace for RedoxOS Build Script"
    echo ""
    echo "Usage: $0 [command]"
    echo ""
    echo "Commands:"
    echo "  build      Build DTrace for RedoxOS (default)"
    echo "  clean      Clean build artifacts"
    echo "  rbpf       Build only the rbpf FFI library"
    echo "  demo       Build and run the demo (on Linux for testing)"
    echo "  test       Run tests on Linux with rbpf backend"
    echo "  help       Show this help message"
    echo ""
    echo "For full RedoxOS builds, use the Redox cookbook:"
    echo "  1. Copy redox/recipe.toml to recipes/tools/dtrace/"
    echo "  2. Run: make r.dtrace"
}

# Main
main() {
    check_tools
    
    case "${1:-build}" in
        build)
            build_dtrace
            ;;
        clean)
            clean
            ;;
        rbpf)
            build_rbpf "${2:-host}"
            ;;
        demo)
            build_demo
            ;;
        test)
            run_tests
            ;;
        help|--help|-h)
            show_help
            ;;
        *)
            error "Unknown command: $1. Use 'help' for usage."
            ;;
    esac
}

main "$@"
