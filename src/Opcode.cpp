#include <Opcode.hpp>

using namespace Instruction;


OpcodeTableMap OpcodeTable = {
    /* {Byte Code, Opcode {OpName name, int len, int cycles, AddressingMode mode}} */

    {0x69, {ADC, 2, 2, AddressingMode::Immediate}},
    {0x65, {ADC, 2, 3, AddressingMode::ZeroPage}},
    {0x75, {ADC, 2, 4, AddressingMode::ZeroPage_X}},
    {0x6d, {ADC, 3, 4, AddressingMode::Absolute}},
    {0x7d, {ADC, 3, 4 /*(+1 if page crossed)*/, AddressingMode::Absolute_X}},
    {0x79, {ADC, 3, 4 /*(+1 if page crossed)*/, AddressingMode::Absolute_Y}},
    {0x61, {ADC, 2, 6, AddressingMode::Indirect_X}},
    {0x71, {ADC, 2, 5 /*(+1 if page crossed)*/, AddressingMode::Indirect_Y}},

    {0x29, {AND, 2, 2, AddressingMode::Immediate}},
    {0x25, {AND, 2, 3, AddressingMode::ZeroPage}},
    {0x35, {AND, 2, 4, AddressingMode::ZeroPage_X}},
    {0x2d, {AND, 3, 4, AddressingMode::Absolute}},
    {0x3d, {AND, 3, 4 /*(+1 if page crossed)*/, AddressingMode::Absolute_X}},
    {0x39, {AND, 3, 4 /*(+1 if page crossed)*/, AddressingMode::Absolute_Y}},
    {0x21, {AND, 2, 6, AddressingMode::Indirect_X}},
    {0x31, {AND, 2, 5 /*(+1 if page crossed)*/, AddressingMode::Indirect_Y}},

    {0x0a, {ASL, 1, 2, AddressingMode::Accumulator}},
    {0x06, {ASL, 2, 5, AddressingMode::ZeroPage}},
    {0x16, {ASL, 2, 6, AddressingMode::ZeroPage_X}},
    {0x0e, {ASL, 3, 6, AddressingMode::Absolute}},
    {0x1e, {ASL, 3, 7, AddressingMode::Absolute_X}},
    {0x90, {BCC, 2, 2 /*(+1 if branch succeeds, +2 if to a new page)*/, AddressingMode::Relative}},
    {0xb0, {BCS, 2, 2 /*(+1 if branch succeeds, +2 if to a new page)*/, AddressingMode::Relative}},
    {0xf0, {BEQ, 2, 2 /*(+1 if branch succeeds, +2 if to a new page)*/, AddressingMode::Relative}},
    {0x24, {BIT, 2, 3, AddressingMode::ZeroPage}},
    {0x2c, {BIT, 3, 4, AddressingMode::Absolute}},
    {0x30, {BMI, 2, 2 /*(+1 if branch succeeds, +2 if to a new page)*/, AddressingMode::Relative}},
    {0xd0, {BNE, 2, 2 /*(+1 if branch succeeds, +2 if to a new page)*/, AddressingMode::Relative}},
    {0x10, {BPL, 2, 2 /*(+1 if branch succeeds, +2 if to a new page)*/, AddressingMode::Relative}},
    {0x00, {BRK, 1, 7, AddressingMode::Implicit}},
    {0x50, {BVC, 2, 2 /*(+1 if branch succeeds, +2 if to a new page)*/, AddressingMode::Relative}},
    {0x70, {BVS, 2, 2 /*(+1 if branch succeeds, +2 if to a new page)*/, AddressingMode::Relative}},
    {0x18, {CLC, 1, 2, AddressingMode::Implicit}},
    {0xd8, {CLD, 1, 2, AddressingMode::Implicit}},
    {0x58, {CLI, 1, 2, AddressingMode::Implicit}},
    {0xb8, {CLV, 1, 2, AddressingMode::Implicit}},
    {0xc9, {CMP, 2, 2, AddressingMode::Immediate}},
    {0xc5, {CMP, 2, 3, AddressingMode::ZeroPage}},
    {0xd5, {CMP, 2, 4, AddressingMode::ZeroPage_X}},
    {0xcd, {CMP, 3, 4, AddressingMode::Absolute}},
    {0xdd, {CMP, 3, 4 /*(+1 if page crossed)*/, AddressingMode::Absolute_X}},
    {0xd9, {CMP, 3, 4 /*(+1 if page crossed)*/, AddressingMode::Absolute_Y}},
    {0xc1, {CMP, 2, 6, AddressingMode::Indirect_X}},
    {0xd1, {CMP, 2, 5 /*(+1 if page crossed)*/, AddressingMode::Indirect_Y}},
    {0xe0, {CPX, 2, 2, AddressingMode::Immediate}},
    {0xe4, {CPX, 2, 3, AddressingMode::ZeroPage}},
    {0xec, {CPX, 3, 4, AddressingMode::Absolute}},
    {0xc0, {CPY, 2, 2, AddressingMode::Immediate}},
    {0xc4, {CPY, 2, 3, AddressingMode::ZeroPage}},
    {0xcc, {CPY, 3, 4, AddressingMode::Absolute}},
    {0xc6, {DEC, 2, 5, AddressingMode::ZeroPage}},
    {0xd6, {DEC, 2, 6, AddressingMode::ZeroPage_X}},
    {0xce, {DEC, 3, 6, AddressingMode::Absolute}},
    {0xde, {DEC, 3, 7, AddressingMode::Absolute_X}},
    {0xca, {DEX, 1, 2, AddressingMode::Implicit}},
    {0x88, {DEY, 1, 2, AddressingMode::Implicit}},
    {0x49, {EOR, 2, 2, AddressingMode::Immediate}},
    {0x45, {EOR, 2, 3, AddressingMode::ZeroPage}},
    {0x55, {EOR, 2, 4, AddressingMode::ZeroPage_X}},
    {0x4d, {EOR, 3, 4, AddressingMode::Absolute}},
    {0x5d, {EOR, 3, 4 /*(+1 if page crossed)*/, AddressingMode::Absolute_X}},
    {0x59, {EOR, 3, 4 /*(+1 if page crossed)*/, AddressingMode::Absolute_Y}},
    {0x41, {EOR, 2, 6, AddressingMode::Indirect_X}},
    {0x51, {EOR, 2, 5 /*(+1 if page crossed)*/, AddressingMode::Indirect_Y}},
    {0xe6, {INC, 2, 5, AddressingMode::ZeroPage}},
    {0xf6, {INC, 2, 6, AddressingMode::ZeroPage_X}},
    {0xee, {INC, 3, 6, AddressingMode::Absolute}},
    {0xfe, {INC, 3, 7, AddressingMode::Absolute_X}},
    {0xe8, {INX, 1, 2, AddressingMode::Implicit}},
    {0xc8, {INY, 1, 2, AddressingMode::Implicit}},
    {0x4c, {JMP, 3, 3, AddressingMode::Absolute}},
    {0x6c, {JMP, 3, 5, AddressingMode::Indirect}},
    {0x20, {JSR, 3, 6, AddressingMode::Absolute}},
    {0xa9, {LDA, 2, 2, AddressingMode::Immediate}},
    {0xa5, {LDA, 2, 3, AddressingMode::ZeroPage}},
    {0xb5, {LDA, 2, 4, AddressingMode::ZeroPage_X}},
    {0xad, {LDA, 3, 4, AddressingMode::Absolute}},
    {0xbd, {LDA, 3, 4 /*(+1 if page crossed)*/, AddressingMode::Absolute_X}},
    {0xb9, {LDA, 3, 4 /*(+1 if page crossed)*/, AddressingMode::Absolute_Y}},
    {0xa1, {LDA, 2, 6, AddressingMode::Indirect_X}},
    {0xb1, {LDA, 2, 5 /*(+1 if page crossed)*/, AddressingMode::Indirect_Y}},
    {0xa2, {LDX, 2, 2, AddressingMode::Immediate}},
    {0xa6, {LDX, 2, 3, AddressingMode::ZeroPage}},
    {0xb6, {LDX, 2, 4, AddressingMode::ZeroPage_Y}},
    {0xae, {LDX, 3, 4, AddressingMode::Absolute}},
    {0xbe, {LDX, 3, 4 /*(+1 if page crossed)*/, AddressingMode::Absolute_Y}},
    {0xa0, {LDY, 2, 2, AddressingMode::Immediate}},
    {0xa4, {LDY, 2, 3, AddressingMode::ZeroPage}},
    {0xb4, {LDY, 2, 4, AddressingMode::ZeroPage_X}},
    {0xac, {LDY, 3, 4, AddressingMode::Absolute}},
    {0xbc, {LDY, 3, 4 /*(+1 if page crossed)*/, AddressingMode::Absolute_X}},
    {0x4a, {LSR, 1, 2, AddressingMode::Accumulator}},
    {0x46, {LSR, 2, 5, AddressingMode::ZeroPage}},
    {0x56, {LSR, 2, 6, AddressingMode::ZeroPage_X}},
    {0x4e, {LSR, 3, 6, AddressingMode::Absolute}},
    {0x5e, {LSR, 3, 7, AddressingMode::Absolute_X}},
    {0xea, {NOP, 1, 2, AddressingMode::Implicit}},
    {0x09, {ORA, 2, 2, AddressingMode::Immediate}},
    {0x05, {ORA, 2, 3, AddressingMode::ZeroPage}},
    {0x15, {ORA, 2, 4, AddressingMode::ZeroPage_X}},
    {0x0d, {ORA, 3, 4, AddressingMode::Absolute}},
    {0x1d, {ORA, 3, 4 /*(+1 if page crossed)*/, AddressingMode::Absolute_X}},
    {0x19, {ORA, 3, 4 /*(+1 if page crossed)*/, AddressingMode::Absolute_Y}},
    {0x01, {ORA, 2, 6, AddressingMode::Indirect_X}},
    {0x11, {ORA, 2, 5 /*(+1 if page crossed)*/, AddressingMode::Indirect_Y}},
    {0x48, {PHA, 1, 3, AddressingMode::Implicit}},
    {0x08, {PHP, 1, 3, AddressingMode::Implicit}},
    {0x68, {PLA, 1, 4, AddressingMode::Implicit}},
    {0x28, {PLP, 1, 4, AddressingMode::Implicit}},
    {0x2a, {ROL, 1, 2, AddressingMode::Accumulator}},
    {0x26, {ROL, 2, 5, AddressingMode::ZeroPage}},
    {0x36, {ROL, 2, 6, AddressingMode::ZeroPage_X}},
    {0x2e, {ROL, 3, 6, AddressingMode::Absolute}},
    {0x3e, {ROL, 3, 7, AddressingMode::Absolute_X}},
    {0x6a, {ROR, 1, 2, AddressingMode::Accumulator}},
    {0x66, {ROR, 2, 5, AddressingMode::ZeroPage}},
    {0x76, {ROR, 2, 6, AddressingMode::ZeroPage_X}},
    {0x6e, {ROR, 3, 6, AddressingMode::Absolute}},
    {0x7e, {ROR, 3, 7, AddressingMode::Absolute_X}},
    {0x40, {RTI, 1, 6, AddressingMode::Implicit}},
    {0x60, {RTS, 1, 6, AddressingMode::Implicit}},
    {0xe9, {SBC, 2, 2, AddressingMode::Immediate}},
    {0xe5, {SBC, 2, 3, AddressingMode::ZeroPage}},
    {0xf5, {SBC, 2, 4, AddressingMode::ZeroPage_X}},
    {0xed, {SBC, 3, 4, AddressingMode::Absolute}},
    {0xfd, {SBC, 3, 4 /*(+1 if page crossed)*/, AddressingMode::Absolute_X}},
    {0xf9, {SBC, 3, 4 /*(+1 if page crossed)*/, AddressingMode::Absolute_Y}},
    {0xe1, {SBC, 2, 6, AddressingMode::Indirect_X}},
    {0xf1, {SBC, 2, 5 /*(+1 if page crossed)*/, AddressingMode::Indirect_Y}},
    {0x38, {SEC, 1, 2, AddressingMode::Implicit}},
    {0xf8, {SED, 1, 2, AddressingMode::Implicit}},
    {0x78, {SEI, 1, 2, AddressingMode::Implicit}},
    {0x85, {STA, 2, 3, AddressingMode::ZeroPage}},
    {0x95, {STA, 2, 4, AddressingMode::ZeroPage_X}},
    {0x8d, {STA, 3, 4, AddressingMode::Absolute}},
    {0x9d, {STA, 3, 5, AddressingMode::Absolute_X}},
    {0x99, {STA, 3, 5, AddressingMode::Absolute_Y}},
    {0x81, {STA, 2, 6, AddressingMode::Indirect_X}},
    {0x91, {STA, 2, 6, AddressingMode::Indirect_Y}},
    {0x86, {STX, 2, 3, AddressingMode::ZeroPage}},
    {0x96, {STX, 2, 4, AddressingMode::ZeroPage_Y}},
    {0x8e, {STX, 3, 4, AddressingMode::Absolute}},
    {0x84, {STY, 2, 3, AddressingMode::ZeroPage}},
    {0x94, {STY, 2, 4, AddressingMode::ZeroPage_X}},
    {0x8c, {STY, 3, 4, AddressingMode::Absolute}},
    {0xaa, {TAX, 1, 2, AddressingMode::Implicit}},
    {0xa8, {TAY, 1, 2, AddressingMode::Implicit}},
    {0xba, {TSX, 1, 2, AddressingMode::Implicit}},
    {0x8a, {TXA, 1, 2, AddressingMode::Implicit}},
    {0x9a, {TXS, 1, 2, AddressingMode::Implicit}},
    {0x98, {TYA, 1, 2, AddressingMode::Implicit}} 

};
