#ifndef MINI_DRIVER_VIDEO_H
#define MINI_DRIVER_VIDEO_H

#include <stdint.h>

void printMessageSpecificColor(const char * string, uint8_t colorLetra, uint8_t colorFondo);
void printCharSpecificColor(char character, uint8_t colorLetra, uint8_t colorFondo);
void printCharBackwards(char character, uint8_t colorLetra, uint8_t colorFondo);
void printMessageBackwards(const char * string, uint8_t colorLetra, uint8_t colorFondo);

#endif