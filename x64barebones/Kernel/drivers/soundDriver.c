#include <time.h> 
#include <lib.h>
#include <soundDriver.h>

extern void outb(uint16_t port, uint8_t val);
extern uint8_t inb(uint16_t port);
 
void playSound(int frequency){
 
 	unsigned int div = 1193180 / frequency;		//Calculates the divisor necessary for the specified frecuency: 
												// div = 1193180 / frequency. It does this becuase the 
												//the speaker controler uses a timer of 1.193180 MHz as reference

 	outb(0x43, 0xb6);							//it writes in the specific ports in order to set the speakers  
 	outb(0x42, (div) );							//with the desired tone
 	outb(0x42, (div >> 8));					
 
 	unsigned char state = inb(0x61);				//reads the actual state of the 0x61 
  	if (state != (state | 3)) {						// enables the speaker
 		outb(0x61, state | 3);
 	}

}
 
void stopSound(){
 	unsigned char state = inb(0x61) & 0xFC;	
 	outb(0x61, state);				//it diables the speaker
}
 
void beep(int frequency, int millisec){
 	 playSound(frequency);			
 	 sleep(millisec);		
 	 stopSound();
}







