#include <stdint.h>
#include <videoDriver.h>
#include <lib.h>
#include <time.h>
#include <registers.h>

#define ZERO_EXCEPTION_ID 0
#define OPCODE_EXCEPTION_ID 6

static void zero_division(uint64_t rsi, uint64_t rdx, uint64_t rcx);
static void op_code(uint64_t rsi, uint64_t rdx, uint64_t rcx);

void exceptionDispatcher(int exception, uint64_t rsi, uint64_t rdx, uint64_t rcx){
	if (exception == ZERO_EXCEPTION_ID){
		zero_division(rsi, rdx, rcx);
	}else if(exception == OPCODE_EXCEPTION_ID){
		op_code(rsi, rdx, rcx);
	}
}


static void zero_division(uint64_t rsi, uint64_t rdx, uint64_t rcx) {
	genericException("Zero Divsion Error \n", 20, rsi, rdx, rcx);
}

static void op_code(uint64_t rsi, uint64_t rdx, uint64_t rcx){
	genericException("Wrong Opcode Exception \n", 24, rsi, rdx, rcx);
}

