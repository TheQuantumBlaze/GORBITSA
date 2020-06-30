#ifndef MAIN_H
#define MAIN_H

typedef struct
{
	unsigned char* ins;
	unsigned char* mem;
	int* pcounter;
	unsigned char* x;

}memory_t;

int GettingInstructionSetFromFile(unsigned char*, const char*);
void GRAB(memory_t*,int);
void OFFER(memory_t*,int);
void RECEIVE(memory_t*);
void BRANCH(memory_t*,int);
void INCREASE(memory_t*,int);
void TRANSMIT(memory_t*);
void SET(memory_t*,int);
void ADD(memory_t*,int);
#endif
