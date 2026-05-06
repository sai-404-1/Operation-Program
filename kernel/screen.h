#include <stdint.h>
#define VGA_WIDTH  80
#define VGA_HEIGHT 25
#define SCREEN_STYLE 0x1F
#define BLACK_STYLE 0x0F

void put_at(int x, int y, char c, uint8_t color);
void clear_screen(void);
void clear_screen_color(int color);
void print_at(int x, int y, const char* text, uint8_t color);
void print(char* text);
char get_symbol(int scancode);
uint8_t get_scancode();
void print_int(int number, int x, int y);
void draw_logo();