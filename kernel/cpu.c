#include <stdint.h>
#include "cpu.h"

#define QUANT_TIME_MS 20

void enable_interrupts(void) {
    __asm__ volatile ("sti");
}

void disable_interrupts(void) {
    __asm__ volatile ("cli");
}

void halt_cpu(void) {
    __asm__ volatile ("hlt");
}

void interrupt(void) {
    __asm__ volatile ("int $0x80");
}