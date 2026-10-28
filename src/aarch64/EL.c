/*
 * src/aarch64/EL.c
 * By Reyaansh Mishra
 */

#include <pill/utils.h>
#include <pill/aarch64.h>

uint32_t get_current_el(void) {
        uint64_t el_reg;
        __asm__ volatile("mrs %0, CurrentEL" : "=r" (el_reg));
        return (uint32_t)(el_reg >> 2);
};
