/*
 * includes/pill/memory.h
 * By Reyaansh Mishra
 */

#include <stdint.h>
#include <stddef.h>

void* malloc(size_t size);      // 4K-Alignment guarentee.
                                        // This is expected to be used only for TT Generation.
void  free(void* ptr);

void* memcpy (void* dest, const void* src, size_t size);
void* memset (void* dest, int         val, size_t size);
void* memmove(void* dest, const void* src, size_t size);

size_t strlen(const char* str);
