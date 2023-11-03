#include <stdint.h>
#include <videoDriver.h>
#include <time.h>

#define ZERO_EXCEPTION_ID 0
#define OPCODE_EXCEPTION_ID 6

static char *regsName[] = {"RAX", "RBX", "RDX" "RSI", "RDI", "RBP", "RSP", "R8", "R9", "R10", "R11", "R12", "R13", "R14", "R15", "RIP"};

static void zero_division();
static void op_code();

void exceptionDispatcher(int exception){
	if (exception == ZERO_EXCEPTION_ID)
		zero_division();
	else if(exception == OPCODE_EXCEPTION_ID){
		op_code();
	}
}


static void zero_division() {
	
}

static void op_code(){

}