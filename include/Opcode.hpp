#pragma once

#include <iostream>
#include <unordered_map>
#include <cstddef>


using Byte = unsigned char;


enum class AddressingMode
{
    Immediate,
    ZeroPage,
    ZeroPage_X,
    ZeroPage_Y,
    Absolute,
    Absolute_X,
    Absolute_Y,
    Indirect_X,
    Indirect_Y,
    Accumulator,
    Relative,
    Implicit,
    Indirect
};

namespace Instruction {
    enum OpName
    {
        ADC, AND, ASL,
        BCC, BCS, BEQ, BIT, BMI, BNE, BPL, BRK, BVC, BVS,
        CLC, CLD, CLI, CLV, CMP, CPX, CPY, DEC, DEX, DEY,
        EOR, INC, INX, INY,
        JMP, JSR,
        LDA, LDX, LDY, LSR,
        NOP,
        ORA,
        PHA, PHP, PLA, PLP,
        ROL, ROR, RTI, RTS,
        SBC, SEC, SED, SEI, STA, STX, STY,
        TAX, TAY, TSX, TXA, TXS, TYA
    }; 
}


struct Opcode
{
    Instruction::OpName name;
    int len;
    int cycles;
    AddressingMode mode;
};


using OpcodeTableMap = std::unordered_map<Byte, Opcode>;


extern OpcodeTableMap OpcodeTable;