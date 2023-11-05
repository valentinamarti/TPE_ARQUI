#include <registers.h>
#include <videoDriver.h>
#include <interrupts.h>

// Container defines
#define NAME "REGISTERS_DUMP"
#define CX0 275 //Constant X0
#define CY0 100 //Constant Y0
#define WIDTH 450
#define HEIGHT 580

static char *regsNames[] = {"RAX <> ", "RBX <> ", "RCX <> ", "RDX <> " "RSI <> ", "RDI <> ", "RBP <> ", "RSP <> ", "R8 <>  ", "R9 <>  ", "R10 <> ", "R11 <> ", "R12 <> ", "R13 <> ", "R14 <> ", "R15 <> ", "RIP <> "};
static uint64_t *rip;
static uint64_t *rsp;
static uint64_t *stack;
static int container_id;

void saveRegisters(uint64_t rsi, uint64_t rdx, uint64_t rcx){
    rip = (uint64_t*) rsi;
	rsp = (uint64_t*) rdx;
	stack = (uint64_t*) rcx;
    genericMemoryDump("Registers dump \n", 16);
}

void genericException(char* message, int len, uint64_t *ripaux, uint64_t *rspaux, uint64_t *stackaux){
    rip = (uint64_t*) ripaux;
	rsp = (uint64_t*) rspaux;
	stack = (uint64_t*) stackaux;
    genericMemoryDump(message, len);
}

static void genericMemoryDump(char* message, int len){
    container_id = getContainer(NAME,CX0,CY0,WIDTH,HEIGHT); 
	changeSize(container_id,2);

	drawString(container_id, message, len, &GREEN);
	printRegisters();
	sleep(8000);

	exitContainer(container_id);
	return;
}


static void printRegisters(){
	uint64_t *regs = stack;
	char buff[25];
	for (int i = 0; i < 16; i++){		
		if(i == 7){
			itoa(*rsp, buff, 16);
			drawString(container_id, regsNames[i], 7, &RED);
			drawStringNull(container_id, buff, &WHITE);
		}else if(i == 15){
			itoa(*rip, buff, 16);
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