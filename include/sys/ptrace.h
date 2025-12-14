/*
 * Oracle Linux DTrace - RedoxOS Port
 * sys/ptrace.h stub (no process tracing support)
 */

#ifndef _SYS_PTRACE_H
#define _SYS_PTRACE_H

/* ptrace request types - stubs only */
#define PTRACE_TRACEME     0
#define PTRACE_PEEKTEXT    1
#define PTRACE_PEEKDATA    2
#define PTRACE_PEEKUSER    3
#define PTRACE_POKETEXT    4
#define PTRACE_POKEDATA    5
#define PTRACE_POKEUSER    6
#define PTRACE_CONT        7
#define PTRACE_KILL        8
#define PTRACE_SINGLESTEP  9
#define PTRACE_ATTACH     16
#define PTRACE_DETACH     17

/* Stub ptrace function - always fails */
static inline long ptrace(int request, ...)
{
	(void)request;
	return -1;
}

#endif /* _SYS_PTRACE_H */
