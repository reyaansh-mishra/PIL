/*
 * includes/pill/EL1/translation_tables.h
 * By Reyaansh Mishra
 */

#include <stddef.h>
#include <stdint.h>

#include <pill/page.h>

/*
 * Internally selects 1G, 2MB, or 4KB granules
 */
int map_pages_el1(uintptr_t phy, uintptr_t virt, enum PAGE_ATTRIBUTES perms, size_t size); // MUST be a PAGE_SIZE multiple

#define map_pages(phy, virt, perms, size) map_pages_el1(phy, virt, perms, size)
