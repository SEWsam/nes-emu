#pragma once

#include "Opcode.hpp"

// std
#include <cstdint>
#include <limits>
#include <array>


class CPU
{
private:
    // Registers
    uint16_t PC;
    uint8_t SP;

    uint8_t A;
    uint8_t X;
    uint8_t Y;
    union
    {
        // P flags
        struct 
        {
            uint8_t C : 1;
            uint8_t Z : 1;
            uint8_t I : 1; 
            uint8_t D : 1;
            uint8_t B : 1;
            uint8_t _ : 1;
            uint8_t V : 1;
            uint8_t N : 1;
        };
        uint8_t raw;
    } P;


    std::array<uint8_t, 0xFFFF> memory;


public:
    uint8_t memRead(uint16_t addr);
    uint16_t memRead16(uint16_t addr);

    void memWrite(uint16_t addr, uint8_t data);
    void memWrite16(uint16_t addr, uint16_t data);

    uint16_t getOperandAddr(AddressingMode mode);

    void reset();
    void load(std::vector<uint8_t> prog);
    void loadRun(std::vector<uint8_t> prog);
    void run();
    void step();

    void execute();


};