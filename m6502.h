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
	enum StatusFlags
	{
		C = (1 << 0),	//0: Carry Flag
		Z = (1 << 1),	//1: Zero Flag
		I = (1 << 2), 	//2: Interrupt disable
		D = (1 << 3), 	//3: Decimal mode
		B = (1 << 4), 	//4: Break
		U= (1 << 5), 	//5: Unused
		V = (1 << 6), 	//6: Overflow
		N = (1 << 7),	//7: Negative
	};

	uint16_t PC = 0x00; //Program counter
  	uint8_t SP = 0x00; //Stack pointer
  	uint8_t A = 0x00, X = 0x00, Y = 0x00; //Registers
	uint8_t PS = 0x00; // Processor Status Register

public:
	void ConnectBus(Bus *n){
		bus = n;
	}
	
	// TODO: 12 Adressing modes

private:
	Bus *bus = nullptr;
	uint8_t read(uint16_t addr);
	void write(uint16_t addr, uint8_t data);
	
	// Functions for Status register
	uint8_t GetFlag(StatusFlags flag);
	void SetFlag(StatusFlags flag, bool value);

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
