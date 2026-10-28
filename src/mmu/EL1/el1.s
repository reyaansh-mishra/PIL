/* src/mmu/EL1/el1.s */

.section .text
.global write_mair_el1
.global write_tcr_el1
.global write_ttbr0_el1
.global enable_mmu_el1
.global disable_mmu_el1

.macro cleanup
    dsb sy  // 1. Data Synchronization Barrier
    isb     // 2. Instruction Synchronization Barrier to flush the pipeline
.endm

write_mair_el1:
    msr mair_el1, x0
    cleanup
    ret

write_tcr_el1:
    msr tcr_el1, x0
    cleanup
    ret

write_ttbr0_el1:
    msr ttbr0_el1, x0
    tlbi alle1is    // 1. Invalidate all EL2 TLB entries (Inner Shareable)
    cleanup
    ret

enable_mmu_el1:
    mrs x0, sctlr_el1
    orr x0, x0, #1
    /* LATER
    orr x0, x0, #(1 << 0)
    orr x0, x0, #(1 << 2)
    orr x0, x0, #(1 << 12)
    */
    msr sctlr_el1, x0
    cleanup
    ret

disable_mmu_el1:
    mrs x0, sctlr_el1
    bic x0, x0, #1
    msr sctlr_el1, x0
    cleanup
    ret
