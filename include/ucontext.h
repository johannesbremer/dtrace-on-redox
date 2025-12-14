/*
 * Oracle Linux DTrace - RedoxOS Port
 * Copyright (c) 2025, Oracle and/or its affiliates. All rights reserved.
 * Licensed under the Universal Permissive License v 1.0 as shown at
 * http://oss.oracle.com/licenses/upl.
 *
 * ucontext.h stubs for RedoxOS - user context is not fully available.
 */

#ifndef _UCONTEXT_H
#define _UCONTEXT_H

#include <signal.h>
#include <stddef.h>

/* Redox provides ucontext_t via signal.h, so we just need the defines */

/* General register type */
#ifndef NGREG
typedef long long greg_t;

/* Number of general registers - x86_64 */
#define NGREG 23

/* General register array */
typedef greg_t gregset_t[NGREG];
#endif

/* Register indices for x86_64 */
#ifndef REG_R8
#define REG_R8      0
#define REG_R9      1
#define REG_R10     2
#define REG_R11     3
#define REG_R12     4
#define REG_R13     5
#define REG_R14     6
#define REG_R15     7
#define REG_RDI     8
#define REG_RSI     9
#define REG_RBP     10
#define REG_RBX     11
#define REG_RDX     12
#define REG_RAX     13
#define REG_RCX     14
#define REG_RSP     15
#define REG_RIP     16
#define REG_EFL     17
#define REG_CSGSFS  18
#define REG_ERR     19
#define REG_TRAPNO  20
#define REG_OLDMASK 21
#define REG_CR2     22
#endif

/* Stub functions - context manipulation not supported */
#ifndef getcontext
static inline int getcontext(ucontext_t *ucp)
{
	(void)ucp;
	return -1;
}

static inline int setcontext(const ucontext_t *ucp)
{
	(void)ucp;
	return -1;
}

static inline void makecontext(ucontext_t *ucp, void (*func)(void), int argc, ...)
{
	(void)ucp;
	(void)func;
	(void)argc;
}

static inline int swapcontext(ucontext_t *oucp, const ucontext_t *ucp)
{
	(void)oucp;
	(void)ucp;
	return -1;
}
#endif

#endif /* _UCONTEXT_H */
