#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include "main.h"

int GettingInstructionSetFromFile(unsigned char* ins, const char* location)
{
	FILE* fp = fopen(location, "r");
	bool hasEOF = false;

	char buffer[256];

	bool expectInstruction = true;

	int instructionPointer = 0;
	int bufferPointer = 0;

	while(!hasEOF)
	{
		char c = fgetc(fp);
		if(c == EOF)
		{
			if(!(instructionPointer >= (256*2)-1))
			{
				ins[instructionPointer] = '!';
			}
			hasEOF = true;
		}
		else
		{
			if(c == ' ')
			{
				//this is the end of a memory address or something like that
				//c has one so we all good
				if(bufferPointer > 0)
				{
					//there is a number in here
					buffer[bufferPointer] = '\0';
					//appending a null terminator so we can convert it as a string
				        unsigned char num = atoi(buffer);
					ins[instructionPointer] = num;
					instructionPointer++;
					expectInstruction = true;
					bufferPointer = 0;

				}
				else
				{
					ins[instructionPointer] = 0;
					instructionPointer++;
					expectInstruction = true;
				}
				continue;
			}
			if(isalpha(c))
			{
				if(expectInstruction)
				{
					ins[instructionPointer] = c;
					instructionPointer++;
					expectInstruction = false;
				}
				else
				{
					return 1;
				}
			}
			else if(isdigit(c))
			{
				if(!expectInstruction)
				{
					buffer[bufferPointer] = c;
					bufferPointer++;
				}
				else
				{
					return 2;
				}
			}
		}
	}
	fclose(fp);
	return 0;
}

int main()
{
	//working on the memory for the esolang, this is gonna be a malloc
	memory_t* mem = malloc(sizeof(memory_t));
	mem->ins = malloc(256*2*sizeof(unsigned char));
	mem->mem = malloc(256*sizeof(unsigned char));
	mem->pcounter = malloc(sizeof(int));
	mem->x = malloc(sizeof(char));

	//unsigned char* memory = malloc(256 * sizeof(unsigned char));
	//unsigned char* instructions = malloc(256*2*sizeof(unsigned char));

	//int* pcounter = malloc(sizeof(int));
	*(mem->pcounter) = 0;

	//unsigned char* x = malloc(sizeof(char));
	*(mem->x) = 0;

	//for now we are just going to have it read in a file and out put each command to a new line
	
	int err = GettingInstructionSetFromFile(mem->ins,"input.txt");
	if(err != 0) return err;

	bool isI = true;

	//printf("We got past the input\n");

	while(*(mem->pcounter) < 256 * 2-1)
	{
		//printf("Instruction: %d", *(mem->pcounter));
		switch(mem->ins[*(mem->pcounter)])
		{
				case 'G':
					GRAB(mem,mem->ins[*(mem->pcounter) + 1]);
					*(mem->pcounter) += 2;
					break;
				case 'O':
					OFFER(mem,mem->ins[*(mem->pcounter) + 1]);
					*(mem->pcounter) += 2;
					break;
				case 'R':
					RECEIVE(mem);
					*(mem->pcounter) += 2;
					break;
				case 'B':
					BRANCH(mem, mem->ins[*(mem->pcounter) + 1]);
					break;
				case 'I':
					INCREASE(mem, mem->ins[*(mem->pcounter) + 1]);
					*(mem->pcounter) += 2;
					break;
				case 'T':
					TRANSMIT(mem);
					*(mem->pcounter) += 2;
					break;
				case 'S':
					SET(mem,mem->ins[*(mem->pcounter) + 1]);
					*(mem->pcounter) += 2;
					break;
				case 'A':
					ADD(mem,mem->ins[*(mem->pcounter) + 1]);
					*(mem->pcounter) += 2;
					break;
				case '!':
					*(mem->pcounter) = 999;
					break;
				default:
					*(mem->pcounter) += 2;
					break;

		}	
	}

	free(mem->mem);
	free(mem->pcounter);
	free(mem->x);
	free(mem->ins);
	free(mem);

	return 0;
}

void GRAB(memory_t* m,int n)
{
	*(m->x) = m->mem[n];
}
void OFFER(memory_t* m,int n)
{
	m->mem[n] = *(m->x);
}
void RECEIVE(memory_t* m)
{
	*(m->x) = getchar();
}
void BRANCH(memory_t* m,int n)
{
	if(*(m->x) == 0)
	{
		*(m->pcounter) = n * 2;
	}
}
void INCREASE(memory_t* m,int n)
{
	*(m->x) += n;
}
void TRANSMIT(memory_t* m)
{
	printf("%c",*(m->x));
}
void SET(memory_t* m,int n)
{
	*(m->x) = n;
}
void ADD(memory_t* m,int n)
{
	*(m->x) += m->mem[n];
}
