/*
 * includes/pill/aarch64.h
 * By Reyaansh Mishra
 */

#include <stdint.h>

uint32_t get_current_el();

void mask_interrupts();
void unmask_interrupts();

void enable_mmu();
void disable_mmu();

static inline uintptr_t get_current_pc() {
        uint64_t current_pc = 0;

        __asm__ volatile(
                "mrs %0, elr_el2"
                : "=r"(current_pc)
                :
                :
        );
        return current_pc;
};

static inline uintptr_t get_current_sp() {
        uint64_t current_sp = 0;

        __asm__ volatile(
                "mov %0, sp"
                : "=r"(current_sp)
                :
                :
        );
        return current_sp;
};
