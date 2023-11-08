#include <time.h>
#include <miniDriverVideo.h>
#include <naiveConsole.h>


extern unsigned int getSeconds();
extern unsigned int getMinutes();
extern unsigned int getHours(); 

static unsigned long ticks = 0;
static unsigned long millis_ellapsed = 0; 
static uint8_t * currentVideo = (uint8_t*)0xB8000;
static flag = 0; 

void timer_handler() {
	ticks++;
	millis_ellapsed += 55;
}

int ticks_elapsed() {
	return ticks;
}

void sleep(int xmillis){
	int currentmillis = millis_ellapsed;
	while(millis_ellapsed - currentmillis < xmillis){
		hlt();
	}
}

int seconds_elapsed() {
	return ticks / 18;
}

int hours(){
	int aux = changeFormat(getHours());
	if(aux < 3){
		if(aux == 0){
			aux = 21;
		}else if(aux == 1){
			aux = 22;
		}else if(aux == 2){
			aux = 23;
		}
	}else{
		aux -= 3;
	}
	return aux; 
}

int minutes(){
	return changeFormat(getMinutes());
}

int seconds(){
	return changeFormat(getSeconds());
}

int changeFormat(int num){
	int decena = num & 240; 
	decena = decena >> 4;
	int unidades = num & 15; 
	return decena*10 + unidades;
}


