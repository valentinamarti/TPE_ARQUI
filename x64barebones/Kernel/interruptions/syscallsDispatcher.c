#include <stdint.h>
#include <naiveConsole.h>
#include <videoDriver.h>
#include <time.h>

#define BUFFER_KERNEL 0
#define BUFFER_USERSPACE 1

#define STDOUT 1	// para imprimir en pantalla el fd 

static void sys_write(uint64_t buffer, uint64_t longitud, uint64_t filedescriptor, uint64_t color, uint64_t container_id);
static void sys_read(uint64_t buffer, uint64_t longitud, uint64_t filedescriptor);
static void sys_get_time(uint64_t hours, uint64_t minutes, uint64_t seconds);
static void sys_get_registers(uint64_t *registers);
static void sys_set_font_size(uint64_t size, uint64_t container_id);
static void sys_draw_rectangle(uint64_t posx, uint64_t posy, uint64_t sizex, uint64_t sizey, uint64_t color, uint64_t container_id);
static void sys_play_sound();
static void sys_sleep(uint64_t seconds);
static void sys_exit(uint64_t container_id);
static void sys_new_line(uint64_t container_id);
static void sys_clear_sb(uint64_t container_id);
static uint16_t sys_call_div(uint64_t dividendo, uint64_t divisor);
static uint64_t sys_new_container(char * name, int X0, int Y0,int width, int height, uint64_t container_id);

void syscallsDispatcher(uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8, uint64_t r9, uint64_t aux){
	switch (rdi) {
		case 0:		
			sys_write(rsi, rdx, rcx, r8, r9);	// en rsi -> buffer
												// en rdx -> longitud
												// en rcx -> filedescriptor
												// en r8 -> color
												// en r9 -> container_id
			break;		
		case 1:
			sys_read(rsi, rdx, rcx);		    // idem que el write
			break;
		case 2:
			sys_clear(rsi);
			break;
		case 3:
			sys_get_time(rsi, rdx, rcx);
			break;
		case 4:
			sys_get_registers(rsi);
			break;
		case 5:
			sys_set_font_size(rsi, rdx);
			break;
		case 6:
			sys_draw_rectangle(rsi, rdx, rcx, r8, r9, aux);
			break;
		case 7:
			sys_play_sound();
			break;
		case 8:
			sys_sleep(rsi);
			break; 
		case 9:
			sys_exit(rsi);
			break;
		case 10:
			sys_new_line(rsi);
			break;	
		case 11:
			sys_clear_sb(rsi);
			break;	
		case 12:
			sys_call_div(rsi, rdx);		
			break;
		case 13:
			sys_new_container(rsi,rdx,rcx,r8,r9, aux);
			break;
	}
	return;
}

void sys_write(uint64_t buffer, uint64_t longitud, uint64_t filedescriptor, uint64_t color, uint64_t container_id){
	char* string = (char *) buffer;


	if(filedescriptor == STDOUT){
		drawString(container_id, string, longitud,WHITE);
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

void sys_clear(uint64_t container_id){
	emptyContainer(container_id);
}

void sys_get_time(uint64_t hrs, uint64_t min, uint64_t sec){	//son todos punteros a los buffers donde van
	*((unsigned int *)hrs) = hours();	
	*((unsigned int *)min) = minutes();
	*((unsigned int *)sec) = seconds();
}

void sys_get_registers(uint64_t *registers) {
    uint64_t *regs = getRegisters();
    for (int i = 0; i < 17; i++) {
        registers[i] = regs[i];
    }
}



void sys_set_font_size(uint64_t size, uint64_t container_id){
	changeSize(container_id,size);	// desps pasarle el container id
}


void sys_draw_rectangle(uint64_t posx, uint64_t posy, uint64_t sizex, uint64_t sizey, uint64_t color, uint64_t container_id){	
	drawRectangle(WHITE, (int)posx, (int)posy, (int)sizex, (int)sizey);
}

void sys_play_sound(){
	// a completar
}

void sys_sleep(uint64_t seconds){
	sleep((int) seconds);
}

void sys_exit(uint64_t container_id){			
	//delete_container(conteiner_id);			// ver si asi estaria bien 
}

void sys_new_line(uint64_t container_id){
	newLine(container_id);		
}

void sys_clear_sb(uint64_t container_id){
	emptyBuffer(container_id);
}

uint16_t sys_call_div(uint64_t dividendo, uint64_t divisor){
	return dividendo / divisor;
}

uint64_t sys_new_container(char * name, int X0, int Y0,int width, int height, uint64_t container_id){
	int i= getContainer(name,X0,Y0,width,height);
	*((int *)container_id)= i;  

}
