/*
 * src/universal_defs.c
 * By Reyaansh Mishra
 */

#include <pill/state.h>
#include <stdbool.h>
bool is_uefi_alive = true;

pill_malloc_provider_t  pre_malloc_malloc_provider      = NULL;
pill_free_provider_t    pre_free_free_provider          = NULL;
