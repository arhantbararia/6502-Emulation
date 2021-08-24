#include <iostream>
#include <stdlib.h>

using Byte = unsigned char;			// used for 8 bits 
using word = unsigned short;		// used for 16 bits 
using u32 = unsigned int;			// used for 32 bits 

struct mem
{
	static constexpr u32 MEM_MAX = 1024 * 64;
	Byte DATA[MEM_MAX];
	
	void initialise()
	{
		for (u32 i = 0; i < MEM_MAX; i++)
		{	
			DATA[i] = 0;

		}

	}

};
struct CPU
{
	word PC;		// program counter
	word SP;		// stack pointers

	Byte A, X, Y;	 // registers 

	/*
	*  a bit field is a data structure that allows 
	the programmer to allocate memory to structures and 
	unions in bits in order to utilize computer memory in an efficient manner.
	*/

	// Using bit fields here
	// Status flags 
	Byte C : 1;		// Carry flag 
	Byte Z : 1;		// Zero flag
	Byte I : 1;		// IRQ Disable flag 
	Byte D : 1;		// Decimal mode flag
	Byte B : 1;		// Break command flag
	Byte U : 1;		// Unused flag
	Byte V : 1;		//Overflow flag
	Byte N : 1;		// Negative flag 
	
	void Reset(mem& Memory)
	{
		PC = 0xFFFC;
		SP = 0x0100;
		C = Z = I = D = B = V = N = 0;
		A = X = Y = 0;

		Memory.initialise();

	}

};


int main()
{
	CPU cpu;
	mem MEMORY;
	return 0; 
	cpu.Reset(MEMORY);
}