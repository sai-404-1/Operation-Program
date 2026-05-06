#include <stdint.h>
#include "screen.h"
#include "cpu.h"
#include "keyboard.h"
#include "shell.c"

static void get_disk_status() {
    outb(0x1F6, 0xA0); // выбрать primary master disk
    outb(0x1F2, 0x00);
    outb(0x1F3, 0x00);
    outb(0x1F4, 0x00);
    outb(0x1F5, 0x00);

    print_int(inb(0x1F7), VGA_WIDTH-12, VGA_HEIGHT-2);
}

void kernel_main(void) {
    draw_logo();
    clear_screen();

    while (1) {
        get_disk_status();
        shell();
    }
}
