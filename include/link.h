/*
 * Oracle Linux DTrace - RedoxOS Port
 * link.h stub - dynamic linker interface not available on RedoxOS
 */

#ifndef _LINK_H
#define _LINK_H

#include <stdint.h>
#include <gelf.h>

/*
 * Link map ID type
 */
typedef long Lmid_t;

#define LM_ID_BASE   0
#define LM_ID_LDSO   1
#define LM_ID_NEWLM -1

/*
 * Dynamic linker structures - minimal stubs
 */

struct link_map {
	GElf_Addr l_addr;       /* Base address of shared object */
	char     *l_name;       /* Name of shared object */
	void     *l_ld;         /* Dynamic section pointer */
	struct link_map *l_next;
	struct link_map *l_prev;
};

struct r_debug {
	int r_version;
	struct link_map *r_map;
	GElf_Addr r_brk;
	enum {
		RT_CONSISTENT,
		RT_ADD,
		RT_DELETE
	} r_state;
	GElf_Addr r_ldbase;
};

/* dl_phdr_info for dl_iterate_phdr */
struct dl_phdr_info {
	GElf_Addr        dlpi_addr;
	const char      *dlpi_name;
	const GElf_Phdr *dlpi_phdr;
	GElf_Half        dlpi_phnum;
};

/* Stub dl_iterate_phdr */
static inline int dl_iterate_phdr(
	int (*callback)(struct dl_phdr_info *info, size_t size, void *data),
	void *data)
{
	(void)callback; (void)data;
	return 0;
}

#endif /* _LINK_H */
