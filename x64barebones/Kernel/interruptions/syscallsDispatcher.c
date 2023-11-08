#include <stdint.h>
#include <videoDriver.h>
#include <soundDriver.h>
#include <registers.h>
#include <time.h>

#define BUFFER_KERNEL 0
#define BUFFER_USERSPACE 1


#define STDOUT 1

static void sys_write(uint64_t buffer, uint64_t longitud, uint64_t filedescriptor, uint64_t color, uint64_t container_id);
static void sys_read(uint64_t buffer, uint64_t longitud, uint64_t filedescriptor);
static void sys_get_time(uint64_t hours, uint64_t minutes, uint64_t seconds);
static uint64_t sys_get_registers();
static void sys_set_font_size(uint64_t size, uint64_t container_id);
static void sys_draw_rectangle(uint64_t posx, uint64_t posy, uint64_t sizex, uint64_t sizey, uint64_t color, uint64_t container_id);
void sys_play_beep(uint64_t frec, uint64_t millisec);
static void sys_sleep(uint64_t seconds);
static void sys_exit(uint64_t container_id);
static void sys_new_line(uint64_t container_id);
static void sys_clear_sb(uint64_t container_id);
static uint64_t sys_new_container(uint8_t * name, uint16_t X0, uint16_t Y0,uint16_t width, uint16_t height);
static void sys_set_background(uint64_t color, uint64_t container_id);
static void sys_set_border(uint64_t color, uint64_t container_id);
static uint64_t sys_was_redraw(uint64_t container_id);

uint64_t syscallsDispatcher(uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8, uint64_t r9, uint64_t aux){
	switch (rdi) {
		int flag = 0; 
		case 0:		
			sys_write(rsi, rdx, rcx, r8, r9);	// en rsi -> buffer
												// en rdx -> longitud
												// en rcx -> filedescriptor
												// en r8 -> color
												// en r9 -> container_id
			break;		
		case 1:
			sys_read(rsi, rdx, rcx);		   
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
			sys_play_beep(rsi, rdx);
			break;
		case 8:
			sys_sleep(rsi);
			break; 
		case 9:
			sys_exit_container(rsi);
			break;
		case 10:
			sys_new_line(rsi);
			break;	
		case 11:
			sys_clear_sb(rsi);
			break;	
		case 12:
			flag = sys_new_container(rsi,rdx,rcx,r8,r9);
			return flag;
			break;
		case 13:
			sys_set_background(rsi,rdx);
			break;
		case 14:
			sys_set_border(rsi,rdx);
			break;	
		case 15:
			return sys_was_redraw(rsi);
			break;	
	}
	return;
}

void sys_write(uint64_t buffer, uint64_t longitud, uint64_t filedescriptor, uint64_t color, uint64_t container_id){
	char* string = (char *) buffer;
	color_t* aux = (color_t*)color;
	if(filedescriptor == STDOUT){
		drawString(container_id, string, longitud, aux);
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
	emptyContainerByID(container_id);
}

void sys_get_time(uint64_t hrs, uint64_t min, uint64_t sec){	//son todos punteros a los buffers donde van
	*((unsigned int *)hrs) = hours();	
	*((unsigned int *)min) = minutes();
	*((unsigned int *)sec) = seconds();
}


uint64_t sys_get_registers(uint64_t *registers) {
	int flag = 0; 
	uint64_t *regs = getRegisters(&flag);
	if(flag == 1){
		for (int i = 0; i < 16; i++){		
			registers[i] = regs[i];
		}
		return flag;
	}else{
		return flag;
	}
}

void sys_set_font_size(uint64_t size, uint64_t container_id){
	changeSize(container_id, size);	
}


void sys_draw_rectangle(uint64_t posx, uint64_t posy, uint64_t sizex, uint64_t sizey, uint64_t color, uint64_t container_id){	
	color_t* aux = (color_t*)color;
	drawRectangle(aux, (int)posx, (int)posy, (int)sizex, (int)sizey);
}

void sys_play_beep(uint64_t frec, uint64_t millisec){
	beep(frec, millisec);
}

void sys_sleep(uint64_t seconds){
	sleep((int) seconds);
}

void sys_exit_container(uint64_t container_id){			
	exitContainer(container_id);
}

void sys_new_line(uint64_t container_id){
	drawCharInContainer(container_id, (char_t){'\n', WHITE});	
}


void sys_clear_sb(uint64_t container_id){
	emptyContainerByID(container_id);
	emptyBuffer(container_id);
}

uint64_t sys_new_container(uint8_t * name, uint16_t X0, uint16_t Y0,uint16_t width, uint16_t height){	
	int aux = getContainer(name,X0,Y0,width,height);
	return aux; 
}

void sys_set_background(uint64_t color, uint64_t container_id){
	color_t* aux = (color_t*)color;
	changeBackgroundColor(container_id,aux);
}

void sys_set_border(uint64_t color, uint64_t container_id){
	color_t* aux = (color_t*)color;
	changeBorderColor(container_id, aux);
}

uint64_t sys_was_redraw(uint64_t container_id){
	return wasRedraw(container_id); 
}
