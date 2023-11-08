#ifndef MINI_DRIVER_KEYBOARD_H
#define MINI_DRIVER_KEYBOARD_H

#include <stdint.h>

void keyboard_handler1();
char* getStringFromCode(char code);
char getPressedKeyCode();

#endif