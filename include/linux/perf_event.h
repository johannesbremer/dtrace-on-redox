/*
 * Oracle Linux DTrace - RedoxOS Port
 * linux/perf_event.h stub - perf events not available on RedoxOS
 */

#ifndef _LINUX_PERF_EVENT_H
#define _LINUX_PERF_EVENT_H

#include <stdint.h>

/*
 * Perf event types - stubs only
 */
enum perf_type_id {
	PERF_TYPE_HARDWARE = 0,
	PERF_TYPE_SOFTWARE = 1,
	PERF_TYPE_TRACEPOINT = 2,
	PERF_TYPE_HW_CACHE = 3,
	PERF_TYPE_RAW = 4,
	PERF_TYPE_BREAKPOINT = 5,
};

enum perf_sw_ids {
	PERF_COUNT_SW_CPU_CLOCK = 0,
	PERF_COUNT_SW_TASK_CLOCK = 1,
	PERF_COUNT_SW_PAGE_FAULTS = 2,
	PERF_COUNT_SW_CONTEXT_SWITCHES = 3,
	PERF_COUNT_SW_CPU_MIGRATIONS = 4,
	PERF_COUNT_SW_PAGE_FAULTS_MIN = 5,
	PERF_COUNT_SW_PAGE_FAULTS_MAJ = 6,
	PERF_COUNT_SW_DUMMY = 9,
	PERF_COUNT_SW_BPF_OUTPUT = 10,
};

/*
 * Perf event header for ring buffer
 */
struct perf_event_header {
	uint32_t type;
	uint16_t misc;
	uint16_t size;
};

enum perf_event_type {
	PERF_RECORD_MMAP = 1,
	PERF_RECORD_LOST = 2,
	PERF_RECORD_COMM = 3,
	PERF_RECORD_EXIT = 4,
	PERF_RECORD_THROTTLE = 5,
	PERF_RECORD_UNTHROTTLE = 6,
	PERF_RECORD_FORK = 7,
	PERF_RECORD_READ = 8,
	PERF_RECORD_SAMPLE = 9,
	PERF_RECORD_MMAP2 = 10,
	PERF_RECORD_SWITCH = 14,
	PERF_RECORD_SWITCH_CPU_WIDE = 15,
};

/*
 * Perf event attribute structure
 */
struct perf_event_attr {
	uint32_t type;
	uint32_t size;
	uint64_t config;
	union {
		uint64_t sample_period;
		uint64_t sample_freq;
	};
	uint64_t sample_type;
	uint64_t read_format;
	uint64_t disabled       : 1,
		 inherit        : 1,
		 pinned         : 1,
		 exclusive      : 1,
		 exclude_user   : 1,
		 exclude_kernel : 1,
		 exclude_hv     : 1,
		 exclude_idle   : 1,
		 mmap           : 1,
		 comm           : 1,
		 freq           : 1,
		 inherit_stat   : 1,
		 enable_on_exec : 1,
		 task           : 1,
		 watermark      : 1,
		 precise_ip     : 2,
		 mmap_data      : 1,
		 sample_id_all  : 1,
		 exclude_host   : 1,
		 exclude_guest  : 1,
		 exclude_callchain_kernel : 1,
		 exclude_callchain_user   : 1,
		 mmap2          : 1,
		 comm_exec      : 1,
		 use_clockid    : 1,
		 context_switch : 1,
		 write_backward : 1,
		 namespaces     : 1,
		 __reserved_1   : 35;
	union {
		uint32_t wakeup_events;
		uint32_t wakeup_watermark;
	};
	uint32_t bp_type;
	union {
		uint64_t bp_addr;
		uint64_t config1;
	};
	union {
		uint64_t bp_len;
		uint64_t config2;
	};
	uint64_t branch_sample_type;
	uint64_t sample_regs_user;
	uint32_t sample_stack_user;
	int32_t  clockid;
	uint64_t sample_regs_intr;
	uint32_t aux_watermark;
	uint16_t sample_max_stack;
	uint16_t __reserved_2;
};

/*
 * Perf event mmap page - shared between kernel and userspace
 */
struct perf_event_mmap_page {
	uint32_t version;
	uint32_t compat_version;
	uint32_t lock;
	uint32_t index;
	int64_t  offset;
	uint64_t time_enabled;
	uint64_t time_running;
	union {
		uint64_t capabilities;
		struct {
			uint64_t cap_bit0 : 1,
				 cap_bit0_is_deprecated : 1,
				 cap_user_rdpmc : 1,
				 cap_user_time : 1,
				 cap_user_time_zero : 1,
				 cap_____res : 59;
		};
	};
	uint16_t pmc_width;
	uint16_t time_shift;
	uint32_t time_mult;
	uint64_t time_offset;
	uint64_t time_zero;
	uint32_t size;
	uint8_t  __reserved[948];
	uint64_t data_head;
	uint64_t data_tail;
	uint64_t data_offset;
	uint64_t data_size;
	uint64_t aux_head;
	uint64_t aux_tail;
	uint64_t aux_offset;
	uint64_t aux_size;
};

/* IOCTL commands */
#define PERF_EVENT_IOC_ENABLE    0x2400
#define PERF_EVENT_IOC_DISABLE   0x2401
#define PERF_EVENT_IOC_SET_BPF   0x40042408

/* perf_event_open flags */
#define PERF_FLAG_FD_CLOEXEC  (1UL << 3)

/* Sample type flags */
#define PERF_SAMPLE_IP         (1U << 0)
#define PERF_SAMPLE_RAW        (1U << 10)

/* Stub function */
static inline int perf_event_open(struct perf_event_attr *attr,
				  pid_t pid, int cpu, int group_fd,
				  unsigned long flags)
{
	(void)attr; (void)pid; (void)cpu; (void)group_fd; (void)flags;
	return -1;
}

#endif /* _LINUX_PERF_EVENT_H */
