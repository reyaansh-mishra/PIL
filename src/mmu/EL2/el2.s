/* src/mmu/EL2/el2.s */

.section .text
.global write_mair_el2
.global write_tcr_el2
.global write_ttbr0_el2
.global write_hcr
.global read_hcr
.global enable_mmu_el2
.global disable_mmu_el2

.macro cleanup
    dsb sy  // 1. Data Synchronization Barrier
    isb     // 2. Instruction Synchronization Barrier to flush the pipeline
.endm

write_mair_el2:
    msr mair_el2, x0
    cleanup
    ret

write_tcr_el2:
    msr tcr_el2, x0
    cleanup
    ret

write_ttbr0_el2:
    msr ttbr0_el2, x0
    tlbi alle2is    // 1. Invalidate all EL2 TLB entries (Inner Shareable)
    cleanup
    ret

enable_mmu_el2:
    mrs x0, sctlr_el2
    orr x0, x0, #1
    /* LATER
    orr x0, x0, #(1 << 0)
    orr x0, x0, #(1 << 2)
    orr x0, x0, #(1 << 12)
    */
    msr sctlr_el2, x0
    cleanup
    ret

disable_mmu_el2:
    mrs x0, sctlr_el2
    bic x0, x0, #1
    msr sctlr_el2, x0
    cleanup
    ret

write_hcr:
    msr hcr_el2, x0
    cleanup
    ret

read_hcr:
    mrs x0, hcr_el2
    ret