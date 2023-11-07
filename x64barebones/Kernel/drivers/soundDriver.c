#include <stdint.h>
#include <time.h> 
#include <lib.h>
#include <videoDriver.h>
#include <soundDriver.h>

extern void outb(uint16_t port, uint8_t val);
extern uint8_t inb(uint16_t port);
 
void play_sound(int frequency) {
 	uint32_t div;
 	uint8_t tmp;
 
 	div = 1193180 / frequency;
 	outb(0x43, 0xb6);
 	outb(0x42, (uint8_t) (div) );
 	outb(0x42, (uint8_t) (div >> 8));
 
 	tmp = inb(0x61);
  	if (tmp != (tmp | 3)) {
 		outb(0x61, tmp | 3);
 	}

}
 
void nosound(){
 	uint8_t tmp = inb(0x61) & 0xFC;
 
 	outb(0x61, tmp);
}
 
void beep(int frequency, int millisec){
 	 play_sound(frequency);
 	 sleep(millisec);
 	 nosound();
}







