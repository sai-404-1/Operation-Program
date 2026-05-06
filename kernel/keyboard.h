#include <stdint.h>

#ifndef KEYBOARD_H
#define KEYBOARD_H

uint8_t inb(uint16_t port);
uint16_t inw(uint16_t port);
void outb(uint16_t port, uint8_t value);
void key_status(int current_scancode);

#endif