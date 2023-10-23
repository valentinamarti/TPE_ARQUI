#ifndef KEYBOARD_DRIVER_H
#define KEYBOARD_DRIVER_H

#include <stdint.h>

    void keyboard_handler();
    void getKeyValue(uint8_t key);
    void saveCharToBuffer(char c);
    char getNextCharFromBuffer();

#endif