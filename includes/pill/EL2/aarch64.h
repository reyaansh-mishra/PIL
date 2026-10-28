/*
 * includes/pill/EL2/aarch64.h
 * By Reyaansh Mishra
 */

#include <stdint.h>

void write_vbar_el2(uintptr_t);
static inline void install_exception_vectors_el2(uintptr_t vector_table) {
        write_vbar_el2(vector_table);
};
#define install_vbars install_exception_vectors_el2

// --------------------------------------------------------

void write_mair_el2(uint64_t data);
#define write_mair write_mair_el2

void write_tcr_el2(uint64_t data);
#define write_tcr write_tcr_el2

void write_ttbr0_el2(uint64_t data); // Not #defining this one because this one needs CLARITY

void write_hcr_el2(uint64_t data);
#define write_hcr write_hcr_el2

uint64_t read_hcr_el2();
#define read_hcr read_hcr_el2
