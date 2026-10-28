/*
 * includes/pill/state.h
 * By Reyaansh Mishra
 */

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

/* For context that we need from UEFI */

extern bool is_uefi_alive;

/* ------------------------------------------
   ----------------- MEMORY -----------------
   ------------------------------------------ */

typedef void* (*pill_malloc_provider_t)(size_t);
// Now happily give me a malloc provider PRE PILL's malloc takeover
extern pill_malloc_provider_t pre_malloc_malloc_provider;

typedef void  (*pill_free_provider_t)(void*);
// Now happily give me a malloc provider PRE PILL's malloc takeover
extern pill_free_provider_t pre_free_free_provider;     // Tho this should ideally not be used.....


/* ------------------------------------------
   ------------------ UART ------------------
   ------------------------------------------ */

extern volatile uint32_t* uart_addr;
void uart__set_addr(uintptr_t addr);

