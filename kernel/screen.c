#include <stdint.h>
#include "screen.h"
#include "../math.h"

volatile uint16_t* const VGA = (uint16_t*)0xB8000;

void put_at(int x, int y, char c, uint8_t color) {
    if (x < 0 || x >= VGA_WIDTH || y < 0 || y >= VGA_HEIGHT) {
        return;
    }

    VGA[y * VGA_WIDTH + x] = ((uint16_t)color << 8) | (uint8_t)c;
}

void clear_screen(void) {
    for (int y = 0; y < VGA_HEIGHT; y++) {
        for (int x = 0; x < VGA_WIDTH; x++) {
            put_at(x, y, ' ', 0x07);
        }
    }
}

void clear_screen_color(int color) {
    for (int y = 0; y < VGA_HEIGHT; y++) {
        for (int x = 0; x < VGA_WIDTH; x++) {
            put_at(x, y, ' ', color);
        }
    }
}

void print_at(int x, int y, const char* text, uint8_t color) {
    while (*text) {
        put_at(x++, y, *text++, color);
    }
}

void print(char* text) {
    int x = 0;
    while (*text) {
        put_at(x++, VGA_HEIGHT-1, *text++, 0x1F);
    }
}

void draw_logo(int x, int y) {
    print_at(x, y+1, "--------------", SCREEN_STYLE);
    print_at(x, y+2, "|  TRASH-OS  |", SCREEN_STYLE);
    print_at(x, y+3, "--------------", SCREEN_STYLE);
}

void print_count(int counter) {
    // cycle counter
    int length = 10;
    int result[length];
    get_digits(counter, result, length);

    print_at(VGA_WIDTH-17, VGA_HEIGHT-2, "CPU: ", SCREEN_STYLE);
    int i = 0;
    while (i < length) {
        put_at(VGA_WIDTH-12+i, VGA_HEIGHT-2, (char)(result[i]+48), SCREEN_STYLE);
        i++;
    }
    counter++;
}

const char ascii_translate[256] = {
    [0x1E] = 'A', [0x30] = 'B', [0x2E] = 'C',
    [0x20] = 'D', [0x12] = 'E', [0x21] = 'F',
    [0x22] = 'G', [0x23] = 'H', [0x17] = 'I',
    [0x24] = 'J', [0x25] = 'K', [0x26] = 'L',
    [0x32] = 'M', [0x31] = 'N', [0x18] = 'O',
    [0x19] = 'P', [0x10] = 'Q', [0x13] = 'R',
    [0x1F] = 'S', [0x14] = 'T', [0x16] = 'U',
    [0x2F] = 'V', [0x11] = 'W', [0x2D] = 'X',
    [0x15] = 'Y', [0x2C] = 'Z',

    [0x0B] = '0', [0x02] = '1', [0x03] = '2', [0x04] = '3', [0x05] = '4',
    [0x06] = '5', [0x07] = '6', [0x08] = '7', [0x09] = '8', [0x0A] = '9',

    [0x39] = ' ',

    [0xF0] = '_'
};

char get_symbol(int scancode) {
    return ascii_translate[scancode];
}

void print_int(int number, int x, int y) {
    int length = 10;
    int result[length];
    get_digits(number, result, length);

    print_at(VGA_WIDTH-17, VGA_HEIGHT-2, "CPU: ", SCREEN_STYLE);
    int i = 0;
    while (i < length) {
        put_at(VGA_WIDTH-12+i, VGA_HEIGHT-2, (char)(result[i]+48), SCREEN_STYLE);
        i++;
    }
}