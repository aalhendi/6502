#include "m6502.h"
#include "Bus.h"

m6502::m6502()
{
    lookup = 
	{
		{ "BRK", &m6502::BRK, &m6502::IMM, 7 },{ "ORA", &m6502::ORA, &m6502::IZX, 6 },{ "???", &m6502::XXX, &m6502::IMP, 2 },{ "???", &m6502::XXX, &m6502::IMP, 8 },{ "???", &m6502::NOP, &m6502::IMP, 3 },{ "ORA", &m6502::ORA, &m6502::ZP0, 3 },{ "ASL", &m6502::ASL, &m6502::ZP0, 5 },{ "???", &m6502::XXX, &m6502::IMP, 5 },{ "PHP", &m6502::PHP, &m6502::IMP, 3 },{ "ORA", &m6502::ORA, &m6502::IMM, 2 },{ "ASL", &m6502::ASL, &m6502::IMP, 2 },{ "???", &m6502::XXX, &m6502::IMP, 2 },{ "???", &m6502::NOP, &m6502::IMP, 4 },{ "ORA", &m6502::ORA, &m6502::ABS, 4 },{ "ASL", &m6502::ASL, &m6502::ABS, 6 },{ "???", &m6502::XXX, &m6502::IMP, 6 },
		{ "BPL", &m6502::BPL, &m6502::REL, 2 },{ "ORA", &m6502::ORA, &m6502::IZY, 5 },{ "???", &m6502::XXX, &m6502::IMP, 2 },{ "???", &m6502::XXX, &m6502::IMP, 8 },{ "???", &m6502::NOP, &m6502::IMP, 4 },{ "ORA", &m6502::ORA, &m6502::ZPX, 4 },{ "ASL", &m6502::ASL, &m6502::ZPX, 6 },{ "???", &m6502::XXX, &m6502::IMP, 6 },{ "CLC", &m6502::CLC, &m6502::IMP, 2 },{ "ORA", &m6502::ORA, &m6502::ABY, 4 },{ "???", &m6502::NOP, &m6502::IMP, 2 },{ "???", &m6502::XXX, &m6502::IMP, 7 },{ "???", &m6502::NOP, &m6502::IMP, 4 },{ "ORA", &m6502::ORA, &m6502::ABX, 4 },{ "ASL", &m6502::ASL, &m6502::ABX, 7 },{ "???", &m6502::XXX, &m6502::IMP, 7 },
		{ "JSR", &m6502::JSR, &m6502::ABS, 6 },{ "AND", &m6502::AND, &m6502::IZX, 6 },{ "???", &m6502::XXX, &m6502::IMP, 2 },{ "???", &m6502::XXX, &m6502::IMP, 8 },{ "BIT", &m6502::BIT, &m6502::ZP0, 3 },{ "AND", &m6502::AND, &m6502::ZP0, 3 },{ "ROL", &m6502::ROL, &m6502::ZP0, 5 },{ "???", &m6502::XXX, &m6502::IMP, 5 },{ "PLP", &m6502::PLP, &m6502::IMP, 4 },{ "AND", &m6502::AND, &m6502::IMM, 2 },{ "ROL", &m6502::ROL, &m6502::IMP, 2 },{ "???", &m6502::XXX, &m6502::IMP, 2 },{ "BIT", &m6502::BIT, &m6502::ABS, 4 },{ "AND", &m6502::AND, &m6502::ABS, 4 },{ "ROL", &m6502::ROL, &m6502::ABS, 6 },{ "???", &m6502::XXX, &m6502::IMP, 6 },
		{ "BMI", &m6502::BMI, &m6502::REL, 2 },{ "AND", &m6502::AND, &m6502::IZY, 5 },{ "???", &m6502::XXX, &m6502::IMP, 2 },{ "???", &m6502::XXX, &m6502::IMP, 8 },{ "???", &m6502::NOP, &m6502::IMP, 4 },{ "AND", &m6502::AND, &m6502::ZPX, 4 },{ "ROL", &m6502::ROL, &m6502::ZPX, 6 },{ "???", &m6502::XXX, &m6502::IMP, 6 },{ "SEC", &m6502::SEC, &m6502::IMP, 2 },{ "AND", &m6502::AND, &m6502::ABY, 4 },{ "???", &m6502::NOP, &m6502::IMP, 2 },{ "???", &m6502::XXX, &m6502::IMP, 7 },{ "???", &m6502::NOP, &m6502::IMP, 4 },{ "AND", &m6502::AND, &m6502::ABX, 4 },{ "ROL", &m6502::ROL, &m6502::ABX, 7 },{ "???", &m6502::XXX, &m6502::IMP, 7 },
		{ "RTI", &m6502::RTI, &m6502::IMP, 6 },{ "EOR", &m6502::EOR, &m6502::IZX, 6 },{ "???", &m6502::XXX, &m6502::IMP, 2 },{ "???", &m6502::XXX, &m6502::IMP, 8 },{ "???", &m6502::NOP, &m6502::IMP, 3 },{ "EOR", &m6502::EOR, &m6502::ZP0, 3 },{ "LSR", &m6502::LSR, &m6502::ZP0, 5 },{ "???", &m6502::XXX, &m6502::IMP, 5 },{ "PHA", &m6502::PHA, &m6502::IMP, 3 },{ "EOR", &m6502::EOR, &m6502::IMM, 2 },{ "LSR", &m6502::LSR, &m6502::IMP, 2 },{ "???", &m6502::XXX, &m6502::IMP, 2 },{ "JMP", &m6502::JMP, &m6502::ABS, 3 },{ "EOR", &m6502::EOR, &m6502::ABS, 4 },{ "LSR", &m6502::LSR, &m6502::ABS, 6 },{ "???", &m6502::XXX, &m6502::IMP, 6 },
		{ "BVC", &m6502::BVC, &m6502::REL, 2 },{ "EOR", &m6502::EOR, &m6502::IZY, 5 },{ "???", &m6502::XXX, &m6502::IMP, 2 },{ "???", &m6502::XXX, &m6502::IMP, 8 },{ "???", &m6502::NOP, &m6502::IMP, 4 },{ "EOR", &m6502::EOR, &m6502::ZPX, 4 },{ "LSR", &m6502::LSR, &m6502::ZPX, 6 },{ "???", &m6502::XXX, &m6502::IMP, 6 },{ "CLI", &m6502::CLI, &m6502::IMP, 2 },{ "EOR", &m6502::EOR, &m6502::ABY, 4 },{ "???", &m6502::NOP, &m6502::IMP, 2 },{ "???", &m6502::XXX, &m6502::IMP, 7 },{ "???", &m6502::NOP, &m6502::IMP, 4 },{ "EOR", &m6502::EOR, &m6502::ABX, 4 },{ "LSR", &m6502::LSR, &m6502::ABX, 7 },{ "???", &m6502::XXX, &m6502::IMP, 7 },
		{ "RTS", &m6502::RTS, &m6502::IMP, 6 },{ "ADC", &m6502::ADC, &m6502::IZX, 6 },{ "???", &m6502::XXX, &m6502::IMP, 2 },{ "???", &m6502::XXX, &m6502::IMP, 8 },{ "???", &m6502::NOP, &m6502::IMP, 3 },{ "ADC", &m6502::ADC, &m6502::ZP0, 3 },{ "ROR", &m6502::ROR, &m6502::ZP0, 5 },{ "???", &m6502::XXX, &m6502::IMP, 5 },{ "PLA", &m6502::PLA, &m6502::IMP, 4 },{ "ADC", &m6502::ADC, &m6502::IMM, 2 },{ "ROR", &m6502::ROR, &m6502::IMP, 2 },{ "???", &m6502::XXX, &m6502::IMP, 2 },{ "JMP", &m6502::JMP, &m6502::IND, 5 },{ "ADC", &m6502::ADC, &m6502::ABS, 4 },{ "ROR", &m6502::ROR, &m6502::ABS, 6 },{ "???", &m6502::XXX, &m6502::IMP, 6 },
		{ "BVS", &m6502::BVS, &m6502::REL, 2 },{ "ADC", &m6502::ADC, &m6502::IZY, 5 },{ "???", &m6502::XXX, &m6502::IMP, 2 },{ "???", &m6502::XXX, &m6502::IMP, 8 },{ "???", &m6502::NOP, &m6502::IMP, 4 },{ "ADC", &m6502::ADC, &m6502::ZPX, 4 },{ "ROR", &m6502::ROR, &m6502::ZPX, 6 },{ "???", &m6502::XXX, &m6502::IMP, 6 },{ "SEI", &m6502::SEI, &m6502::IMP, 2 },{ "ADC", &m6502::ADC, &m6502::ABY, 4 },{ "???", &m6502::NOP, &m6502::IMP, 2 },{ "???", &m6502::XXX, &m6502::IMP, 7 },{ "???", &m6502::NOP, &m6502::IMP, 4 },{ "ADC", &m6502::ADC, &m6502::ABX, 4 },{ "ROR", &m6502::ROR, &m6502::ABX, 7 },{ "???", &m6502::XXX, &m6502::IMP, 7 },
		{ "???", &m6502::NOP, &m6502::IMP, 2 },{ "STA", &m6502::STA, &m6502::IZX, 6 },{ "???", &m6502::NOP, &m6502::IMP, 2 },{ "???", &m6502::XXX, &m6502::IMP, 6 },{ "STY", &m6502::STY, &m6502::ZP0, 3 },{ "STA", &m6502::STA, &m6502::ZP0, 3 },{ "STX", &m6502::STX, &m6502::ZP0, 3 },{ "???", &m6502::XXX, &m6502::IMP, 3 },{ "DEY", &m6502::DEY, &m6502::IMP, 2 },{ "???", &m6502::NOP, &m6502::IMP, 2 },{ "TXA", &m6502::TXA, &m6502::IMP, 2 },{ "???", &m6502::XXX, &m6502::IMP, 2 },{ "STY", &m6502::STY, &m6502::ABS, 4 },{ "STA", &m6502::STA, &m6502::ABS, 4 },{ "STX", &m6502::STX, &m6502::ABS, 4 },{ "???", &m6502::XXX, &m6502::IMP, 4 },
		{ "BCC", &m6502::BCC, &m6502::REL, 2 },{ "STA", &m6502::STA, &m6502::IZY, 6 },{ "???", &m6502::XXX, &m6502::IMP, 2 },{ "???", &m6502::XXX, &m6502::IMP, 6 },{ "STY", &m6502::STY, &m6502::ZPX, 4 },{ "STA", &m6502::STA, &m6502::ZPX, 4 },{ "STX", &m6502::STX, &m6502::ZPY, 4 },{ "???", &m6502::XXX, &m6502::IMP, 4 },{ "TYA", &m6502::TYA, &m6502::IMP, 2 },{ "STA", &m6502::STA, &m6502::ABY, 5 },{ "TXS", &m6502::TXS, &m6502::IMP, 2 },{ "???", &m6502::XXX, &m6502::IMP, 5 },{ "???", &m6502::NOP, &m6502::IMP, 5 },{ "STA", &m6502::STA, &m6502::ABX, 5 },{ "???", &m6502::XXX, &m6502::IMP, 5 },{ "???", &m6502::XXX, &m6502::IMP, 5 },
		{ "LDY", &m6502::LDY, &m6502::IMM, 2 },{ "LDA", &m6502::LDA, &m6502::IZX, 6 },{ "LDX", &m6502::LDX, &m6502::IMM, 2 },{ "???", &m6502::XXX, &m6502::IMP, 6 },{ "LDY", &m6502::LDY, &m6502::ZP0, 3 },{ "LDA", &m6502::LDA, &m6502::ZP0, 3 },{ "LDX", &m6502::LDX, &m6502::ZP0, 3 },{ "???", &m6502::XXX, &m6502::IMP, 3 },{ "TAY", &m6502::TAY, &m6502::IMP, 2 },{ "LDA", &m6502::LDA, &m6502::IMM, 2 },{ "TAX", &m6502::TAX, &m6502::IMP, 2 },{ "???", &m6502::XXX, &m6502::IMP, 2 },{ "LDY", &m6502::LDY, &m6502::ABS, 4 },{ "LDA", &m6502::LDA, &m6502::ABS, 4 },{ "LDX", &m6502::LDX, &m6502::ABS, 4 },{ "???", &m6502::XXX, &m6502::IMP, 4 },
		{ "BCS", &m6502::BCS, &m6502::REL, 2 },{ "LDA", &m6502::LDA, &m6502::IZY, 5 },{ "???", &m6502::XXX, &m6502::IMP, 2 },{ "???", &m6502::XXX, &m6502::IMP, 5 },{ "LDY", &m6502::LDY, &m6502::ZPX, 4 },{ "LDA", &m6502::LDA, &m6502::ZPX, 4 },{ "LDX", &m6502::LDX, &m6502::ZPY, 4 },{ "???", &m6502::XXX, &m6502::IMP, 4 },{ "CLV", &m6502::CLV, &m6502::IMP, 2 },{ "LDA", &m6502::LDA, &m6502::ABY, 4 },{ "TSX", &m6502::TSX, &m6502::IMP, 2 },{ "???", &m6502::XXX, &m6502::IMP, 4 },{ "LDY", &m6502::LDY, &m6502::ABX, 4 },{ "LDA", &m6502::LDA, &m6502::ABX, 4 },{ "LDX", &m6502::LDX, &m6502::ABY, 4 },{ "???", &m6502::XXX, &m6502::IMP, 4 },
		{ "CPY", &m6502::CPY, &m6502::IMM, 2 },{ "CMP", &m6502::CMP, &m6502::IZX, 6 },{ "???", &m6502::NOP, &m6502::IMP, 2 },{ "???", &m6502::XXX, &m6502::IMP, 8 },{ "CPY", &m6502::CPY, &m6502::ZP0, 3 },{ "CMP", &m6502::CMP, &m6502::ZP0, 3 },{ "DEC", &m6502::DEC, &m6502::ZP0, 5 },{ "???", &m6502::XXX, &m6502::IMP, 5 },{ "INY", &m6502::INY, &m6502::IMP, 2 },{ "CMP", &m6502::CMP, &m6502::IMM, 2 },{ "DEX", &m6502::DEX, &m6502::IMP, 2 },{ "???", &m6502::XXX, &m6502::IMP, 2 },{ "CPY", &m6502::CPY, &m6502::ABS, 4 },{ "CMP", &m6502::CMP, &m6502::ABS, 4 },{ "DEC", &m6502::DEC, &m6502::ABS, 6 },{ "???", &m6502::XXX, &m6502::IMP, 6 },
		{ "BNE", &m6502::BNE, &m6502::REL, 2 },{ "CMP", &m6502::CMP, &m6502::IZY, 5 },{ "???", &m6502::XXX, &m6502::IMP, 2 },{ "???", &m6502::XXX, &m6502::IMP, 8 },{ "???", &m6502::NOP, &m6502::IMP, 4 },{ "CMP", &m6502::CMP, &m6502::ZPX, 4 },{ "DEC", &m6502::DEC, &m6502::ZPX, 6 },{ "???", &m6502::XXX, &m6502::IMP, 6 },{ "CLD", &m6502::CLD, &m6502::IMP, 2 },{ "CMP", &m6502::CMP, &m6502::ABY, 4 },{ "NOP", &m6502::NOP, &m6502::IMP, 2 },{ "???", &m6502::XXX, &m6502::IMP, 7 },{ "???", &m6502::NOP, &m6502::IMP, 4 },{ "CMP", &m6502::CMP, &m6502::ABX, 4 },{ "DEC", &m6502::DEC, &m6502::ABX, 7 },{ "???", &m6502::XXX, &m6502::IMP, 7 },
		{ "CPX", &m6502::CPX, &m6502::IMM, 2 },{ "SBC", &m6502::SBC, &m6502::IZX, 6 },{ "???", &m6502::NOP, &m6502::IMP, 2 },{ "???", &m6502::XXX, &m6502::IMP, 8 },{ "CPX", &m6502::CPX, &m6502::ZP0, 3 },{ "SBC", &m6502::SBC, &m6502::ZP0, 3 },{ "INC", &m6502::INC, &m6502::ZP0, 5 },{ "???", &m6502::XXX, &m6502::IMP, 5 },{ "INX", &m6502::INX, &m6502::IMP, 2 },{ "SBC", &m6502::SBC, &m6502::IMM, 2 },{ "NOP", &m6502::NOP, &m6502::IMP, 2 },{ "???", &m6502::SBC, &m6502::IMP, 2 },{ "CPX", &m6502::CPX, &m6502::ABS, 4 },{ "SBC", &m6502::SBC, &m6502::ABS, 4 },{ "INC", &m6502::INC, &m6502::ABS, 6 },{ "???", &m6502::XXX, &m6502::IMP, 6 },
		{ "BEQ", &m6502::BEQ, &m6502::REL, 2 },{ "SBC", &m6502::SBC, &m6502::IZY, 5 },{ "???", &m6502::XXX, &m6502::IMP, 2 },{ "???", &m6502::XXX, &m6502::IMP, 8 },{ "???", &m6502::NOP, &m6502::IMP, 4 },{ "SBC", &m6502::SBC, &m6502::ZPX, 4 },{ "INC", &m6502::INC, &m6502::ZPX, 6 },{ "???", &m6502::XXX, &m6502::IMP, 6 },{ "SED", &m6502::SED, &m6502::IMP, 2 },{ "SBC", &m6502::SBC, &m6502::ABY, 4 },{ "NOP", &m6502::NOP, &m6502::IMP, 2 },{ "???", &m6502::XXX, &m6502::IMP, 7 },{ "???", &m6502::NOP, &m6502::IMP, 4 },{ "SBC", &m6502::SBC, &m6502::ABX, 4 },{ "INC", &m6502::INC, &m6502::ABX, 7 },{ "???", &m6502::XXX, &m6502::IMP, 7 },
	};


}


m6502::~m6502(){

}

uint8_t m6502::read(uint16_t addr)
{
	return bus->read(addr, false);
}

void m6502::write(uint16_t addr, uint8_t data)
{
	return bus->write(addr, data);
}

// Can occur at anytime and behaves asynchronously
void m6502::reset(){
		PC = 0xFFFC; // TODO: Reset Vector &Memory
		// S = 0xFF; S was decremented by 3 but nothing was written to stack.
		SetFlag(D, 0x00); // NES actually used modified 6502 with no decimal mode
		SetFlag(I, 0x01);
		//TODO: Initialize memory
	}

// A single clock cycle
void m6502::clock(){
    // TODO: Make emulation clock cycle accurate.
    // Only exec instruction when internal cycles remaining is zero
    if (cycles == 0){
        // Read next instruction byte
        opcode = read(PC);
        
        // Always set U to true
        SetFlag(U, true);

        // Increment PC preparing for read of nxt byte
        PC++;

        // Lookup number of cycles for instruction
        cycles = lookup[opcode].cycles;

        // Call addressing mode function via pointer stored in lookup table.
        // Store number of extra cycles returned
        uint8_t addr_mode = (this->*lookup[opcode].addrmode)();

        // Repeat for operation function.
        uint8_t operation = (this->*lookup[opcode].operate)();

        // Adjust cycle math
        cycles += (addr_mode & operation);

        SetFlag(U, true);

    }
    // Unused global clock count for debugging
	clock_count++;

	// Cycle complete. Decrement remaining
	cycles--;
}

// Addressing Modes

// Implied Addressing: The address containing the operand is implicitly stated in the OPCODE of the instruction.
uint8_t m6502::IMP(){
    // Implied could act on accumulator 
    fetched = A;
    return 0;
}

// Immediate Addressing: second byte of instruction contains operand, with no further memory addressing required.
uint8_t m6502::IMM(){
    addr_abs = PC++;
    return 0;
}

// Zero Page Adressing: fetch only second byte assuming 0 high address byte. shorter code execution time.
uint8_t m6502::ZP0(){
    addr_abs = read(PC);
    PC++;
    addr_abs &= 0x00FF;
    return 0;
}

// Indexed Zero Page Adressing: effective address = sencond byte + index register. 
// Because this is "zero page" addressing no carry added to high order bits and no page boundry crossing.
uint8_t m6502::ZPX(){
    addr_abs = (read(PC) + X);
    PC++;
    addr_abs &= 0x00FF;
    return 0;
}

uint8_t m6502::ZPY(){
    addr_abs = (read(PC) + Y);
    PC++;
    addr_abs &= 0x00FF;
    return 0;
}

// Absolute Adressing: Allows access to entire 64k of addressible memory.
// second byte -> 8 low order bits of effective address, third byte -> 8 high order bits of effective address. 
uint8_t m6502::ABS(){
    uint8_t lo = read(PC); 
    PC++;
    uint8_t hi = read(PC);
    PC++;

    addr_abs = (hi << 8) | lo;

    return 0;
}


// Indexed Absolute Adressing: Address = Index Register + second & third bytes.
// Index contains index/count & instruction contains base address. Allows referencing to any location.
// Index may modify multiple fields -> slower coding and execution time.
uint8_t m6502::ABX(){
    uint8_t lo = read(PC); 
    PC++;
    uint8_t hi = read(PC);
    PC++;

    addr_abs = (hi << 8) | lo;
    addr_abs += X;

    // Check if high byte has changed due to overflow from the carry bit in the low byte.
    if((addr_abs & 0xFF00) != (hi << 8)){
        return 1;
    } else{
        return 0;
    }
}

uint8_t m6502::ABY(){
    uint8_t lo = read(PC); 
    PC++;
    uint8_t hi = read(PC);
    PC++;

    addr_abs = (hi << 8) | lo;
    addr_abs += Y;

    // Check if high byte has changed due to overflow from the carry bit in the low byte.
    if((addr_abs & 0xFF00) != (hi << 8)){
        return 1;
    } else{
        return 0;
    }
}