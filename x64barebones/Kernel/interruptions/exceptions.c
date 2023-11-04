#include <stdint.h>
#include <videoDriver.h>
#include <lib.h>
#include <time.h>

// Container defines
#define NAME "EXCEPTIONS"
#define CX0 200 //Constant X0
#define CY0 100 //Constant Y0
#define WIDTH 400
#define HEIGHT 600

#define ZERO_EXCEPTION_ID 0
#define OPCODE_EXCEPTION_ID 6

static char *regsNames[] = {"RAX <> ", "RBX <> ", "RCX <> ", "RDX <> " "RSI <> ", "RDI <> ", "RBP <> ", "RSP <> ", "R8 <>  ", "R9 <>  ", "R10 <> ", "R11 <> ", "R12 <> ", "R13 <> ", "R14 <> ", "R15 <> ", "RIP <> "};
// rsp 7 y rip 16
static uint64_t *rip;
static uint64_t *rsp;
static uint64_t * stack;
static int container_id;


static void zero_division();
static void op_code();
static void genericException(char* message, int len);

void exceptionDispatcher(int exception, uint64_t rsi, uint64_t rdx, uint64_t rcx){
	rip = (uint64_t*) rsi;
	rsp = (uint64_t*) rdx;
	stack = (uint64_t*) rcx;
	if (exception == ZERO_EXCEPTION_ID){
		zero_division();
	}else if(exception == OPCODE_EXCEPTION_ID){
		op_code();
	}
}


static void zero_division() {
	genericException("Zero Divsion Error \n", 20);
}

static void op_code(){
	genericException("Wrong Opcode Exception \n", 24);
}

static void genericException(char* message, int len){
	int aux = getContainer(NAME,CX0,CY0,WIDTH,HEIGHT); 
	container_id = aux;
	changeSize(container_id,2);

	drawString(container_id, message, len, &GREEN);
	printRegs();
	sleep(8000);
}


void printRegs(){
	uint64_t *regs = stack;
	char buff[25];
	for (int i = 0; i < 16; i++){		
		if(i == 7){
			itoa(rsp, buff, 16);
			drawString(container_id, regsNames[i], 7, &RED);
			drawStringNull(container_id, buff, &WHITE);
		}else if(i == 15){
			itoa(rip, buff, 16);
			drawString(container_id, regsNames[i], 7, &RED);
			drawStringNull(container_id, buff, &WHITE);
		}else{
			itoa(regs[14 - i], buff, 16);
			drawString(container_id, regsNames[i], 7, &RED);
			drawStringNull(container_id, buff, &WHITE);
		}
		drawCharInContainer(container_id, (char_t){'\n', WHITE});	
	}
}