#ifndef MINI_DRIVER_KEYBOARD_H
#define MINI_DRIVER_KEYBOARD_H

#include <stdint.h>

void keyboard_hanlder();
char* getStringFromCode(char code);
char getPressedKeyCode();

#endif