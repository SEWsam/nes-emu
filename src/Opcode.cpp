#include "Opcode.hpp"

using namespace Instruction;


OpcodeTableMap OpcodeTable = {
    /* {Byte Code, Opcode {OpName name, int len, int cycles, AddressingMode mode}} */
    {0x00, {BRK, 1, 7, AddressingMode::Implicit}},
    {0x08, {PHP, }},
    {0x10, {BPL, }},
    {0x18, {CLC, }},
    {0x20, {JSR, }},
    {0x24, {BIT, }},
    {0x28, {PLP, }},
    {0x2c, {BIT, }},
    {0x30, {BMI, }},
    {0x38, {SEC, }},



    {0xaa, {TAX, 1, 2, AddressingMode::Implicit}},

    {0xa9, {LDA, 2, 2, AddressingMode::Immediate}},
    {0xa5, {LDA, 2, 3, AddressingMode::ZeroPage}},
    {0xb5, {LDA, 2, 4, AddressingMode::ZeroPage_X}},
    {0xad, {LDA, 3, 4, AddressingMode::Absolute}},
    {0xbd, {LDA, 3, 4 /* +1 if page crossed */, AddressingMode::Absolute_X}},
    {0xb9, {LDA, 3, 4 /* +1 if page crossed */, AddressingMode::Absolute_Y}},
    {0xa1, {LDA, 2, 6, AddressingMode::Indirect_X}},
    {0xb1, {LDA, 2, 5 /* +1 if page crossed */, AddressingMode::Indirect_Y}},
    
    {0x85, {STA, 2, 3, AddressingMode::ZeroPage}},
    {0x95, {STA, 2, 4, AddressingMode::ZeroPage_X}},
    {0x8d, {STA, 3, 4, AddressingMode::Absolute}},
    {0x9d, {STA, 3, 5, AddressingMode::Absolute_X}},
    {0x99, {STA, 3, 5, AddressingMode::Absolute_Y}},
    {0x81, {STA, 2, 6, AddressingMode::Indirect_X}},
    {0x91, {STA, 2, 6, AddressingMode::Indirect_Y}},

};
