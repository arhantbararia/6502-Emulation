#include <iostream>
#include <stdlib.h>

using Byte = unsigned char;			// used for 8 bits 
using word = unsigned short;		// used for 16 bits 

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
	
	

};


int main()
{
	CPU cpu;

	return 0; 
}