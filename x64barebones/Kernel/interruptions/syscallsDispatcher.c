#include <stdint.h>
#include <naiveConsole.h>

#define BUFFER_KERNEL 0
#define BUFFER_USERSPACE 1

static void sys_read(uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t indicador);
static void sys_write(uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t indicador);

void syscallsDispatcher(uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t indicador){
	switch (rdi) {
		case 0:		
			sys_write(rsi, rdx, rcx, indicador);	        // en rsi -> buffer
												// en rdx -> longitud
												// en rcx -> filedescriptor
			break;		
		case 1:
			sys_read(rsi, rdx, rcx, indicador);		    // idem que el write
			break;
	}
	return;
}

void sys_write(uint64_t buffer, uint64_t longitud, uint64_t filedescriptor, uint64_t indicador){
	//drawString((char*) buffer, longitud, filedescriptor);	// falta ver si el x y lo dejamos en videoDriver o si lo pasamos por paramtero
}

void sys_read(uint64_t buffer, uint64_t longitud, uint64_t filedescriptor, uint64_t indicador){
    // if(indicador == BUFFER_KERNEL){

	// }
}

