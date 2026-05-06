#ifndef CPU_H
#define CPU_H

#include <stdint.h>

#define QUANT_TIME_MS 20

void enable_interrupts(void);
void disable_interrupts(void);
void halt_cpu(void);
void interrupt(void);

#endif