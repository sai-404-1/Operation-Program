#include "math.h"

int get_digits(int number, int* resulting, int length) {
    // дробление числа на цифры

    for (int i = 0; i < length; i++) {resulting[i] = 0;}
    int digits[length], result;
    int orig = number;
    int copy = orig;
    int i = 0;
    while (orig > 0) {
        orig=(orig/10)*10;  // обнуление последней цифры
        result=copy-orig;   // разница с оригиналом
        orig=copy/=10;      // срез последней цифры копии
        resulting[length-i-1] = result; // запись цифры в массив
        i++;
    }
    return 0;
}