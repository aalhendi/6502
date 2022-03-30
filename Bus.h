#pragma once
#include <cstdint>
#include <array>
#include "m6502.h"

class Bus
{
private:
    /* data */
public:
    Bus(/* args */);
    ~Bus();

public: // Bus devices
    m6502 CPU;
    std::array<uint8_t, 64*1024> RAM;
    

public: // Bus R/W 
   uint8_t read(uint16_t addr, bool isReadOnly = false);
   void write(uint16_t addr, uint8_t data);
};

Bus::Bus(/* args */)
{
    // Clear RAM contents, not actually needed
    for (auto &i : RAM){
        i = 0x00;
    }

    // Connect CPU to bus
    CPU.ConnectBus(this);
}

Bus::~Bus()
{
}

uint8_t Bus::read(uint16_t addr, bool isReadOnly)
{
    // Guard to make sure address is actually within the bus
    if (addr >= 0x0000 && addr <= 0xFFFF){
        return RAM[addr];// Can directly access ram since its only device on bus. 
    } else{
        return 0x0000;
    }

};

void Bus::write(uint16_t addr, uint8_t data)
{
    if (addr >= 0x0000 && addr <= 0xFFFF){
        RAM[addr] = data; 
    }
};
