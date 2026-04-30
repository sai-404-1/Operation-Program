#ifndef SCREEN
#define SCREEN
#define VGA_WIDTH  80
#define VGA_HEIGHT 25

static volatile uint16_t* const VGA = (uint16_t*)0xB8000;

static void put_at(int x, int y, char c, uint8_t color) {
    if (x < 0 || x >= VGA_WIDTH || y < 0 || y >= VGA_HEIGHT) {
        return;
    }

    VGA[y * VGA_WIDTH + x] = ((uint16_t)color << 8) | (uint8_t)c;
}

static void clear_screen(void) {
    for (int y = 0; y < VGA_HEIGHT; y++) {
        for (int x = 0; x < VGA_WIDTH; x++) {
            put_at(x, y, ' ', 0x07);
        }
    }
}

static void clear_screen_color(int color) {
    for (int y = 0; y < VGA_HEIGHT; y++) {
        for (int x = 0; x < VGA_WIDTH; x++) {
            put_at(x, y, ' ', color);
        }
    }
}

static void print_at(int x, int y, const char* text, uint8_t color) {
    while (*text) {
        put_at(x++, y, *text++, color);
    }
}

#endif