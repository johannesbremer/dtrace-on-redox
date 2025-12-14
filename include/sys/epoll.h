/*
 * Oracle Linux DTrace - RedoxOS Port
 * Copyright (c) 2025, Oracle and/or its affiliates. All rights reserved.
 * Licensed under the Universal Permissive License v 1.0 as shown at
 * http://oss.oracle.com/licenses/upl.
 *
 * epoll API stubs for RedoxOS
 * epoll is not natively available on Redox, we provide minimal stubs.
 */

#ifndef _SYS_EPOLL_H
#define _SYS_EPOLL_H

#include <stdint.h>

/* epoll events */
#define EPOLLIN      0x001
#define EPOLLPRI     0x002
#define EPOLLOUT     0x004
#define EPOLLERR     0x008
#define EPOLLHUP     0x010
#define EPOLLRDNORM  0x040
#define EPOLLRDBAND  0x080
#define EPOLLWRNORM  0x100
#define EPOLLWRBAND  0x200
#define EPOLLMSG     0x400
#define EPOLLRDHUP   0x2000

/* epoll_ctl operations */
#define EPOLL_CTL_ADD 1
#define EPOLL_CTL_DEL 2
#define EPOLL_CTL_MOD 3

/* epoll_create flags */
#define EPOLL_CLOEXEC 0x80000

/* epoll data union */
typedef union epoll_data {
	void    *ptr;
	int      fd;
	uint32_t u32;
	uint64_t u64;
} epoll_data_t;

/* epoll event structure */
struct epoll_event {
	uint32_t     events;
	epoll_data_t data;
} __attribute__((packed));

/* Stub functions */
static inline int epoll_create(int size)
{
	(void)size;
	return -1;
}

static inline int epoll_create1(int flags)
{
	(void)flags;
	return -1;
}

static inline int epoll_ctl(int epfd, int op, int fd, struct epoll_event *event)
{
	(void)epfd; (void)op; (void)fd; (void)event;
	return -1;
}

static inline int epoll_wait(int epfd, struct epoll_event *events,
                             int maxevents, int timeout)
{
	(void)epfd; (void)events; (void)maxevents; (void)timeout;
	return -1;
}

static inline int epoll_pwait(int epfd, struct epoll_event *events,
                              int maxevents, int timeout, const void *sigmask)
{
	(void)epfd; (void)events; (void)maxevents; (void)timeout; (void)sigmask;
	return -1;
}

#endif /* _SYS_EPOLL_H */
