#ifndef KEYBOARD_DRIVER_H
#define KEYBOARD_DRIVER_H

#include <stdint.h>

    int keyboard_handler();
    int getKeyValue(uint8_t key);
    void saveCharToBuffer(char c);
    char getNextCharFromBuffer();

#endif