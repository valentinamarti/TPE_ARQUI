#ifndef _REGISTERS_H_
#define _REGISTERS_H_

#include <stdint.h>

void saveRegisters(uint64_t rsi, uint64_t rdx, uint64_t rcx);
void genericException(char* message, int len, uint64_t ripaux, uint64_t rspaux, uint64_t stackaux);
void genericMemoryDump(char* message, int len);
void saveRegsInfo();
void printRegisters();
uint64_t* getRegisters();

#endif