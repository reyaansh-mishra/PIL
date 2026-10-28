/*
 * includes/pill/EL1/aarch64.h
 * By Reyaansh Mishra
 */

#include <stdint.h>

void write_vbar_el1(uintptr_t);
static inline void install_exception_vectors_el1(uintptr_t vector_table) {
        write_vbar_el1(vector_table);
};
#define install_vbars install_exception_vectors_el1

// --------------------------------------------------------

void write_mair_el1(uint64_t data);
#define write_mair write_mair_el1

void write_tcr_el1(uint64_t data);
#define write_tcr write_tcr_el1

void write_ttbr0_el1(uint64_t data); // Not #defining this one because this one needs CLARITY
