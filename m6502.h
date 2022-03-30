#pragma once
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

// Forward declaring bus
class Bus;

class m6502
{
private:
	/* data */
public:
	m6502(/* args */);
	~m6502();
public:
	void ConnectBus(Bus *n){
		bus = n;
	}
private:
	Bus *bus = nullptr;
	uint8_t read(uint16_t addr);
	void write(uint16_t addr, uint8_t data);
};

m6502::m6502(/* args */)
{
}

m6502::~m6502()
{
}

uint8_t m6502::read(uint16_t addr)
{
	return bus->read(addr, false);
}

void m6502::write(uint16_t addr, uint8_t data)
{
	return bus->write(addr, data);
}


// namespace m6502
// {
// 	using Byte = unsigned char;
// 	using Word = unsigned short;

// 	struct Mem;
// 	struct CPU;
// 	struct StatusFlags;
// }

// struct m6502::StatusFlags
// {
//   // Status flags
//   Byte C : 1;	//0: Carry Flag
// 	Byte Z : 1;	//1: Zero Flag
// 	Byte I : 1; //2: Interrupt disable
// 	Byte D : 1; //3: Decimal mode
// 	Byte B : 1; //4: Break
// 	Byte Unused : 1; //5: Unused
// 	Byte V : 1; //6: Overflow
// 	Byte N : 1; //7: Negative
// };

// struct m6502::CPU
// {

//   Word PC; //Program counter
//   Byte SP; //Stack pointer

//   Byte A, X, Y; //Registers
// };