// #include "kernel/screen.h"

// static void key_status(int current_scancode) {
//     int length_scancode = 8;
//     int result_scancode[length_scancode];
//     get_digits(current_scancode, result_scancode, length_scancode);

//     print_at(1, 1, "SCAN-CODE: ", SCREEN_STYLE);
//     int i = 0;
//     while (i < length_scancode) {
//         put_at(12+i, 1, (char)(result_scancode[i]+48), SCREEN_STYLE);
//         i++;
//     }
//     print_at(1, 2, "BUTTON:    ", SCREEN_STYLE);
//     put_at(12, 2, get_symbol(current_scancode), SCREEN_STYLE);
// }