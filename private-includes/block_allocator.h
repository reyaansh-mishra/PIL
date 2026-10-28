/*
 * private-includes/block_allocator.h
 * By Reyaansh Mishra
 */

#include <stddef.h>

void* block_allocator_allocate(size_t size);
void  block_allocator_free(void* ptr);
