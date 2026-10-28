/*
 * includes/pill/utils.h
 * By Reyaansh Mishra
 */

#pragma once

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

#define INFO(fmt, ...)  printf("[PILL]: " fmt, ##__VA_ARGS__)
#define ERR(fmt, ...)   printf("[ERR] [PILL]: " fmt, ##__VA_ARGS__)
#define ASSERT(args) \
    do { \
        if (!(args)) { \
            ERR("ASSERT FAILED: %s\n", #args); \
            __asm__ volatile("wfi"); \
        } \
    } while (0)


static inline bool is_1gb_aligned(uintptr_t ramBase) {
        return (ramBase & 0x3FFFFFFF) == 0;
};

static inline uint64_t round_up(uint64_t num, uint64_t to_multiple_of)
{
        if (to_multiple_of == 0) return num;
        return (((num + (to_multiple_of-1))/to_multiple_of) * to_multiple_of);
};

static inline uint64_t round_down(uint64_t num, uint64_t to_multiple_of)
{
        if (to_multiple_of == 0) return num;
        return (num / to_multiple_of) * to_multiple_of;
};

static inline bool get_bit(uint64_t source, uint64_t bit) {
        return ((source >> bit) & 1ULL);
};

static inline uint64_t get_bits(uint64_t src, size_t start_bit, size_t end_bit) {  // start_bit -> end_bit
        return (src >> end_bit) & ((1ULL << (start_bit - end_bit + 1)) - 1);
};

static inline void set_bit(uint64_t* target, uint64_t bit, bool val) {
        if (!target) { return; };

        if (val)
                *target |= (1ULL << bit);
        else
                *target &= ~(1ULL << bit);
};

static inline void set_bits(uint64_t* t, uint64_t hi, uint64_t lo, uint64_t val) {
        uint64_t width = hi - lo + 1;
        uint64_t mask  = (width >= 64 ? ~0ULL : ((1ULL << width) - 1)) << lo;
        *t = (*t & ~mask) | ((val << lo) & mask);
}

