/*
 * includes/pill/page.h
 * By Reyaansh Mishra
 */

enum PAGE_ATTRIBUTES {
        PAGE_RO   = 1 << 0,
        PAGE_RW   = 1 << 1,
        PAGE_EX   = 1 << 2,

        PAGE_DV   = 1 << 3,
};

#define PAGE_SIZE       4096
