#include "keyboard.h"
#include "screen.h"
#include "string.c"

//      bg / letter
#define BLACK_WHITE 0x0F

#define BACKSPACE 0x0E
#define ENTER 0x1C

#define BUFFER_LEN 16

int something() {
    print("Hello world");
    return 12345678;
}

void clean_buffer(char command_buffer[]) {
    for (int i = 0; i < BUFFER_LEN; i++) {
        command_buffer[i] = '\0';
    }
}

void add_to_buffer(char command_buffer[], char symbol, int current_pos) {
    command_buffer[current_pos] = symbol;
    command_buffer[current_pos+1] = '\0';
}

int shell_line_x  =   {0};
int shell_line_y  =   {0};

void shell_print(char message[]) {
    while(*message != '\0') {
        put_at(1, VGA_HEIGHT-1, *message, BLACK_WHITE);
        // *message++;
    }
}

void shell() {
    int early_scancode   =  {0};
    int current_scancode =  {0};
    char symbol =   {0};
    int result  =   {0};
    int current_pos = {0};

    int (*commands[10])(void) = {&something};
    char command_buffer[] = {"\0"};
    uint8_t screen_cleen = 0;

    while (1) {
        int current_scancode = get_scancode();
        if (current_scancode & 0x80) {
            early_scancode = current_scancode;
            continue;
        }

        // letter typing
        while (current_scancode != early_scancode) {
            // подтверждаем ввод
            if (current_scancode == ENTER) {
                result = compare_strings(command_buffer, "TEST");
                if (!result) {
                    result = commands[0]();
                } else {
                    screen_cleen = 1;
                    clean_buffer(command_buffer);
                    print_at(1, VGA_HEIGHT-1, "COMMAND NOT FOUND", BLACK_WHITE);
                }
                print_int(result, 0, VGA_HEIGHT-1);
                shell_line_y++;
                shell_line_x = 0;
                result = 0;
                clean_buffer(command_buffer);
            } else

            // стираем введённое
            if (current_scancode == BACKSPACE) {
                shell_line_x-=1;
                put_at(shell_line_x, shell_line_y, ' ', BLACK_WHITE);
                if (shell_line_x < 0) {shell_line_y--; shell_line_x=0;};
                if (shell_line_y < 0) shell_line_y=0;
            }
            
            // записываем команду
            else {
                // if (screen_cleen == 1) {
                //     clear_screen();
                //     screen_cleen = 0;
                //     shell_line_x=0; shell_line_y=0;
                // }
                symbol = get_symbol(current_scancode);
                put_at(shell_line_x, shell_line_y, symbol, BLACK_WHITE);
                add_to_buffer(command_buffer, symbol, current_pos);
                current_pos++;
                shell_line_x++;
            }
            early_scancode = current_scancode;
        }
    }
}