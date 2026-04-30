#include <stdint.h>
#include "screen.h"
#include "cpu.h"

static void draw_menu() {
    clear_screen_color(0x00);
    uint_fast8_t start_x = VGA_WIDTH/2-6;
    print_at(start_x, 1, "--------------", 0x0A);
    print_at(start_x, 2, "|  TRASH-OS  |", 0x0A);
    print_at(start_x, 3, "--------------", 0x0A);
    print_at(start_x, 4, "Enter any key.", 0x0A);
}

void kernel_main(void) {
    draw_menu();
    int keyboard_scan = inb(0x60);
    while (1) {
        char symbols[] = {'-', '/', '\\'};
        char ASCII_NUMBERS = 48;
        char idk[16];
        for (int i = 0; i < 10; i++){
            idk[0x0000010+i] = (char)(uintptr_t)i;
        }
        
        while (keyboard_scan == inb(0x60)) {;}
        clear_screen();

        for (int i = 0; i <= 20; i++) {
            for (int j = 0; j <= 20; j++) {
                print_at(VGA_WIDTH-j, i+1, " ", 0x0A+(i*15)+(j));
            }
        }
        int step = {0};
        int max_width = 20;
        int max_height = 20;
        for (int i = 0; i < max_height;){
            for (int j = 0; j < max_width; j++) {
                put_at(1+j, 1+i+step, (char)(uintptr_t)(idk[keyboard_scan]+48+j+1+(step*max_width)), 0x0A);
            }
            if (step+i < VGA_HEIGHT-5) step++;
        }
        halt_cpu();
    }
}
