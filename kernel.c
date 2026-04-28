#include <stdint.h>

#define VGA_WIDTH  80
#define VGA_HEIGHT 25

static volatile uint16_t* const VGA = (uint16_t*)0xB8000;

extern void irq0_stub(void);
extern void default_interrupt_stub(void);

static inline void enable_interrupts(void) {
    __asm__ volatile ("sti");
}

static inline void disable_interrupts(void) {
    __asm__ volatile ("cli");
}

static inline void halt_cpu(void) {
    __asm__ volatile ("hlt");
}

static void put_at(int x, int y, char c, uint8_t color) {
    if (x < 0 || x >= VGA_WIDTH || y < 0 || y >= VGA_HEIGHT) {
        return;
    }

    VGA[y * VGA_WIDTH + x] = ((uint16_t)color << 8) | (uint8_t)c;
}

static void clear_screen(void) {
    for (int y = 0; y < VGA_HEIGHT; y++) {
        for (int x = 0; x < VGA_WIDTH; x++) {
            put_at(x, y, '[', 0x07);
        }
    }
}

static void print_at(int x, int y, const char* text, uint8_t color) {
    while (*text) {
        put_at(x++, y, *text++, color);
    }
}

static void draw_menu() {
    clear_screen();
    uint_fast8_t start_x = VGA_WIDTH/2-6;
    print_at(start_x, 1, "----------", 0x0A);
    print_at(start_x, 2, "|TRASH-OS|", 0x0A);
    print_at(start_x, 3, "----------", 0x0A);
}

void kernel_main(void) {
    while (1) {
        draw_menu();
        for (int i = 0; i < VGA_WIDTH; ++i) {
            print_at(i, VGA_HEIGHT/2-1, "-", 0x0A);
        }
        halt_cpu();
    }
}
