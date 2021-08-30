#include <iostream>
#include <stdlib.h>
//using data types 
using Byte = unsigned char;			// used for 8 bits 
using word = unsigned short;		// used for 16 bits 
using u32 = unsigned int;			// used for 32 bits 

struct MEM
{
	static constexpr u32 MEM_MAX = 1024 * 64;			//2^16
	Byte DATA[MEM_MAX];
	
	void initialise()
	{
		for (u32 i = 0; i < MEM_MAX; i++)
		{	
		  	DATA[i] = 0;

		}

	}

	//read  1 byte of memory
	Byte operator[](u32 Address) const
	{
		return DATA[Address];
	}

	// write 1 byte of memory
	Byte& operator[](u32 Address)
	{
		return DATA[Address];

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
	

	//opcodes
	static constexpr Byte INS_LDA_IM = 0xA9;		//INSert value to LoaD Accumulator by IMmediate mode
	static constexpr Byte INS_LDA_ZP = 0xA5;		// INSert value to Load Accumulator by Zero Page addressing mode 
	static constexpr Byte INS_LDA_ZPX = 0xB5;		// INSert value to Load Accumulator by Zero Page X  addressing mode 
	
	void Reset(MEM& Memory)
	{
		PC = 0xFFFC;
		SP = 0x0100;
		C = Z = I = D = B = V = N = 0;
		A = X = Y = 0;		// initialise registers to 0;

		Memory.initialise();

	}
	Byte FetchByte(u32& cycles,  MEM& memory)
	{
		Byte DATA =  memory[PC];
		PC++;
		cycles--;
		return DATA;
	}
	Byte ReadByte(u32& cycles, MEM& memory, Byte Address)
	{
		Byte DATA = memory[Address];
		cycles--;
		return DATA;

	}
	
	void execute(u32 cycles, MEM& Memory)		// CPU has a clock (cycles) for fetching out memory. 
	{
		while (cycles > 0)
		{
			Byte Ins = FetchByte(cycles,  Memory);		// instruction

			switch (Ins)
			{
				case INS_LDA_IM:
				{
					Byte Value = FetchByte(cycles , Memory);
					
					
					A = Value;		// Load accumulator with Value
					
					
					Z = (A == 0);		// SET STATUS FLAGS
					N = (A & 0b1000000) > 0;	

				}break;


				case INS_LDA_ZP:
				{
					Byte Zero_page_address = FetchByte(cycles, Memory);\

					A = ReadByte(cycles, Memory, Zero_page_address);		// Load accumulator with value stored at zero page address 



					Z = (A == 0);		// SET STATUS FLAGS
					N = (A & 0b1000000) > 0;
				}break;


				case INS_LDA_ZPX:
				{
					Byte Zero_page_address = FetchByte(cycles, Memory);

					Zero_page_address += X;
					cycles--;


					A = ReadByte(cycles, Memory, Zero_page_address);

					Z = (A == 0);		// SET STATUS FLAGS
					N = (A & 0b1000000) > 0;
				}
				default:
				{
					std::cout << "Instruction not handled / supported yet";
				}
			}




			

		}
	}

};


int main()
{
	CPU cpu;
	MEM MEMORY;
	cpu.Reset(MEMORY);
	MEMORY[0XFFFC] = cpu.INS_LDA_ZP;
	MEMORY[0XFFFD] = 0X42;
	MEMORY[0x0042] = 0x84;

	cpu.execute(3, MEMORY);


	return 0;
 
}