#include <stdio.h>
#include <stdlib.h>

/* 
https://web.archive.org/web/20210909190432/http://www.obelisk.me.uk/6502/
https://www.nesdev.org/wiki/Nesdev_Wiki
*/

/*
Program Counter (PC) / Instruction Pointer (IP): Pointer to the address that the CPU is executing the code for. Whatever address is thereis the next instruction that is going to be executed. Found even in modern intel x86 processors. 

Stack Pointer (SP): Pointer to the address of the next free location in the stack via holding the low 8-bits. 256 byte stack on the 6502 from $0100 to $01FF.

Index registers X, Y and Accumulator (A): The 6502 had 3 registers (only!). All 8-bit.
*/

struct CPU
{
  using Byte = unsigned char;
  using Word = unsigned short;

  Word PC; //Program counter
  Byte SP; //Stack pointer

  Byte A, X, Y; //Registers
  
  // Status flags
  Byte C : 1;	//0: Carry Flag
	Byte Z : 1;	//1: Zero Flag
	Byte I : 1; //2: Interrupt disable
	Byte D : 1; //3: Decimal mode
	Byte B : 1; //4: Break
	Byte Unused : 1; //5: Unused
	Byte V : 1; //6: Overflow
	Byte N : 1; //7: Negative
};

int main()
{


  return 0;
}
