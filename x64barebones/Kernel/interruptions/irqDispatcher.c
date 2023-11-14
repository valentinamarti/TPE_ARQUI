#include <time.h>
#include <stdint.h>
#include <keyboardDriver.h>

static void int_20();
static int int_21();
static int flag = 0; 

int irqDispatcher(uint64_t irq) {
	switch (irq) {
		case 0:		
			int_20();
			return -1;
			break;		
		case 1:
			flag = int_21();
			return flag;
			break;
	}
	return;
}

void int_20() {
	timer_handler();
}

int int_21(){
	int flagAux = keyboard_handler();
	if(flagAux == 1){
		return flagAux;
	}
	return 0; 
}
