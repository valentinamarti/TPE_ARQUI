#include <time.h>
#include <miniDriverVideo.h>
#include <naiveConsole.h>

extern unsigned int getSeconds();
extern unsigned int getMinutes();
extern unsigned int getHours(); 

static unsigned long ticks = 0;
static uint8_t * currentVideo = (uint8_t*)0xB8000;
static flag = 0; 

void timer_handler() {
	ticks++;
	if(flag == 1 && ticks == 7){		// hago lo de ticks == 7 para alcanzar a leer el mnsj 
		printMessageBackwards("            ", 0x00, 0x00);
		flag = 0; 
	}
	if(seconds_elapsed() == 5){
		printMessageSpecificColor("INTERRUPCION", 0xFF, 0xDD);
		ticks = 0; 
		flag = 1; 
	}

}

int ticks_elapsed() {
	return ticks;
}

void sleep(int seconds){
	ticks = 0; 
	while(seconds_elapsed() < seconds){
		_hlt();
	}
}

int seconds_elapsed() {
	return ticks / 18;
}

int hours(){
	return getHours();
}

int minutes(){
	return getMinutes();
}

int seconds(){
	return getSeconds();
}


