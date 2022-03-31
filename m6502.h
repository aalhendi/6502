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
		U = (1 << 5), 	//5: Unused
		V = (1 << 6), 	//6: Overflow
		N = (1 << 7),	//7: Negative
	};

	uint16_t PC = 0x0000; //Program counter
  	uint8_t S = 0xFD; //Stack pointer
  	uint8_t A = 0x00, X = 0x00, Y = 0x00; //Registers
	uint8_t P = 0x34; // Processor Status Register

public:
	void ConnectBus(Bus *n){
		bus = n;
	}
	
	void Reset(){
		PC = 0xFFFC; // TODO: Reset Vector &Memory
		// S = 0xFF; S was decremented by 3 but nothing was written to stack.
		SetFlag(D, 0x00); // NES actually used modified 6502 with no decimal mode
		SetFlag(I, 0x01);
		//TODO: Initialize memory
	}

	// Addressing Modes
	//TODO?: Accumulator adressing
	// Immediate Addressing: second byte of instruction contains operand, with no further memory addressing required.
	uint8_t IMM();	
	// Absolute Adressing: Allows access to entire 64k of addressible memory.
	// second byte -> 8 low order bits of effective address, third byte -> 8 high order bits of effective address. 
	uint8_t ABS();	
	// Zero Page Adressing: fetch only second byte assuming 0 high address byte. shorter code execution time.
	uint8_t ZP0();
	// Indexed Zero Page Adressing: effective address = sencond byte + index register. 
	// Because this is "zero page" addressing no carry added to high order bits and no page boundry crossing.
	uint8_t ZPX();	
	uint8_t ZPY();
	// Indexed Absolute Adressing: Address = Index Register + second & third bytes.
	// Index contains index/count & instruction contains base address. Allows referencing to any location.
	// Index may modify multiple fields -> slower coding and execution time.
	uint8_t ABX();	
	uint8_t ABY();
	// Implied Addressing: The address containing the operand is implicitly stated in the OPCODE of the instruction.
	uint8_t IMP();
	// Relative Addressing: only used with branch instruction and establishes destination for conditional branch
	// second byte is operand. Operand is an offset which is added to PC when PC is set at next instruction
	// offset range is -128 to +127 bytes
	uint8_t REL();
	// Indirect Indexed Addressing: second byte added to contents of index register discarding the carry.
	// result points to mem location in zero page which contains low order byte of effective address.
	// next mem location in zero page contains high order byte of effective address. Both memory locations must be in zero page
	uint8_t IZX();
	// Indirect Indexed Addressing: second byte points to mem location in zero page. contents added to index register
	// result of addition is low order byte of effective address. Carry from addition is added to contents of next
	// zero page memory location to form high order byte of effective address.
	uint8_t IZY();
	// Absolute Indirect Adressing: second byte contains low order byte of memory location.
	// high order 8-bits in third byte. Contents of fully specified mem location are low order byte of effective address
	// next mem location contains high order byte of effective address which is loaded into 16-bits of PC (JMP (IND) only)
	uint8_t IND();

private:
	Bus *bus = nullptr;
	uint8_t read(uint16_t addr);
	void write(uint16_t addr, uint8_t data);
	
	// Functions for Status register
	uint8_t GetFlag(StatusFlags flag);
	void SetFlag(StatusFlags flag, bool value);

	void Reset();

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
