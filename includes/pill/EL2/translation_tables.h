/*
 * includes/pill/EL2/translation_tables.h
 * By Reyaansh Mishra
 */

#include <stddef.h>
#include <stdint.h>

#include <pill/page.h>

/*
 * Internally selects 1G, 2MB, or 4KB granules
 */
int map_pages_el2(uintptr_t phy, uintptr_t virt, enum PAGE_ATTRIBUTES perms, size_t size); // MUST be a PAGE_SIZE multiple
        // Returns Standard Error Code.
#define map_pages map_pages_el2
