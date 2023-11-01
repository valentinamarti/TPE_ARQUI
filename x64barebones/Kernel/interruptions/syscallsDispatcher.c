#include <stdint.h>
#include <naiveConsole.h>
#include <videoDriver.h>

#define BUFFER_KERNEL 0
#define BUFFER_USERSPACE 1
#define STDOUT 1	// para imprimir en pantalla el fd 

static void sys_read(uint64_t buffer, uint64_t longitud, uint64_t filedescriptor);
static void sys_write(uint64_t buffer, uint64_t longitud, uint64_t filedescriptor, uint64_t color);
static void sys_get_time(uint64_t hours, uint64_t minutes, uint64_t seconds);
static void sys_get_registers(uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8, uint64_t r9);
static void sys_set_font_size(uint64_t size);
static void sys_draw_rectangle(uint64_t posx, uint64_t posy, uint64_t sizex, uint64_t sizey, uint64_t color);
static void sys_play_sound();
static void sys_sleep(uint64_t seconds);
static void sys_exit();

void syscallsDispatcher(uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8, uint64_t r9){
	switch (rdi) {
		case 0:		
			sys_write(rsi, rdx, rcx, r8);	    // en rsi -> buffer
												// en rdx -> longitud
												// en rcx -> filedescriptor
			break;		
		case 1:
			sys_read(rsi, rdx, rcx);		    // idem que el write
			break;
		case 2:
			sys_clear();
			break;
		case 3:
			sys_get_time(rsi, rdx, rcx);
			break;
		case 4:
			sys_get_registers(rdi, rsi, rdx, rcx, r8, r9);
			break;
		case 5:
			sys_set_font_size(rsi);
			break;
		case 6:
			sys_draw_rectangle(rsi, rdx, rcx, r8, r9);
			break;
		case 7:
			sys_play_sound();
			break;
		case 8:
			sys_sleep(rsi);
			break; 
		case 9:
			sys_exit();
			break;
	}
	return;
}

void sys_write(uint64_t buffer, uint64_t longitud, uint64_t filedescriptor, uint64_t color){
	char* string = (char *) buffer;
	if(filedescriptor == STDOUT){
		drawString(WHITE, string, longitud);
	}else{
		return;
	}
}	

void sys_read(uint64_t buffer, uint64_t longitud, uint64_t filedescriptor){
    if(filedescriptor == BUFFER_KERNEL){
		char* buffAux = (char *) buffer;
		for(int i = 0; i < longitud; i++){
			buffAux[i] =  getNextCharFromBuffer();
		}
		return;
	}else if(filedescriptor == BUFFER_USERSPACE){
		return; 		// aca hay que terminar
	}
}

void sys_clear(){
	emptyScreen();
}

void sys_get_time(uint64_t hours, uint64_t minutes, uint64_t seconds){	//son todos punteros a los buffers donde van
	*((int *)hours) = getHours();	//	probar
	*((int *)minutes) = getMinutes();
	*((int *)seconds) = getSeconds();
}

void sys_get_registers(uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8, uint64_t r9){
	// para que la completes matu 
}

void sys_set_font_size(uint64_t size){
	changeSize(size);
}

void sys_draw_rectangle(uint64_t posx, uint64_t posy, uint64_t sizex, uint64_t sizey, uint64_t color){	
	drawRectangle(WHITE, posx, posy, sizex, sizey);
}

void sys_play_sound(){
	// a completar
}

void sys_sleep(uint64_t seconds){
	sleep((int) seconds);
}

void sys_exit(){
	// ??????
}

