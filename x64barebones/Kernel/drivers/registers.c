#include <registers.h>
#include <videoDriver.h>
#include <interrupts.h>
#include <time.h>
#include <lib.h>

// Container defines
#define NAME "REGISTERS_DUMP"
#define CX0 275 //Constant X0
#define CY0 50 //Constant Y0
#define WIDTH 450
#define HEIGHT 700


static char *regsNames[] = {"RAX <> ", "RBX <> ", "RCX <> ", "RDX <> ", "RBP <> ", "RDI <> ", "RSI <> ", "RSP <> ", "R8  <> ", "R9  <> ", "R10 <> ", "R11 <> ", "R12 <> ", "R13 <> ", "R14 <> ", "R15 <> ", "RIP <> "};

static uint64_t *rip;
static uint64_t *rsp;
static uint64_t *stack;
static uint64_t savedRegisters[17] = {0};

static int container_id;
static int saved = 0;

void saveRegisters(uint64_t rsi, uint64_t rdx, uint64_t rcx){
	rip = (uint64_t*) rsi;
	rsp = (uint64_t*) rdx;
	stack = (uint64_t*) rcx;
	saved = 1;
	saveRegsInfo();
    genericMemoryDump("Registers dump \n", 16);
}

void genericException(char* message, int len, uint64_t ripaux, uint64_t rspaux, uint64_t stackaux){
    rip =  (uint64_t*) ripaux;
	rsp =  (uint64_t*) rspaux;
	stack =  (uint64_t*) stackaux;
	saved = 0;
	saveRegsInfo();
    genericMemoryDump(message, len);
}

void genericMemoryDump(char* message, int len){
    container_id = getContainer((uint8_t *)NAME,CX0,CY0,WIDTH,HEIGHT); 
	changeSize(container_id,2);
	changeBackgroundColor(container_id, &REGISTERS_DUMP_BACKGROUND);
	changeBorderColor(container_id, &REGISTERS_DUMP_BORDER);

	drawString(container_id,(uint8_t *) message, len, &REGISTERS_DUMP_TITTLE);
	printRegisters();
	sleep(5000);

	exitContainer(container_id);
	return;
}

void saveRegsInfo(){
	uint64_t *regs = stack;
	int flag = 0;
	int j = 0;			// con este itero el stack
	for (int i = 0; i < 17; i++){		
		if(i == 7 && flag == 0){
			savedRegisters[i] =(uint64_t) rsp;
			flag = 1;
		}else if(i == 16){
			savedRegisters[i] =(uint64_t) rip;
		}else{
			savedRegisters[i] = regs[14 - j];
			j++;
		}
	}
}

void printRegisters(){
	char buff[25];
	for (int i = 0; i < 17; i++){		
		itoa(savedRegisters[i], buff, 16);
		drawString(container_id, (uint8_t *) regsNames[i], 7, &REGISTERS_DUMP_REGS);
		drawStringNull(container_id,(uint8_t *) buff, &REGISTERS_DUMP_LETTER);
		drawCharInContainer(container_id, (char_t){'\n', WHITE});	
	}
}

uint64_t* getRegisters(int* flag){
	*flag = saved;
	return savedRegisters;
}