#ifndef _SOUND_DRIVER_H
#define _SOUND_DRIVER_H
#include <stdint.h>

void playSound(int frequency);
void stopSound();
void beep(int frequency, int millisec);

#endif