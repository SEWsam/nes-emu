#include "CPU.hpp"

#include "Opcode.hpp"

// std
#include <iostream>
#include <exception>
#include <vector>
#include <algorithm>

uint8_t CPU::memRead(uint16_t addr)
{
    return memory[addr];
}

uint16_t CPU::memRead16(uint16_t addr)
{
    // if the 16 bit val at addr is 0x2543

    // this is 43
    uint16_t leastSigByte = memRead(addr);
    // this is 25
    uint16_t mostSigByte = memRead(addr + 1);

    // for my dumbass:
    // why is the left side (of the literal value) most significant?
    // Because of how binary works:
    // 8 bit example:
    // 2^7 <- 2^0
    // 1 ...   1
    // the left most "1" is more valuable (more significant) than the rightmost 1.
    return (mostSigByte << 8) | leastSigByte;
}

void CPU::memWrite(uint16_t addr, uint8_t data)
{
    memory[addr] = data;
}

void CPU::memWrite16(uint16_t addr, uint16_t data)
{
    uint8_t leastSigByte = (data & 0xff);
    uint8_t mostSigByte = (data >> 8);
    memWrite(addr, leastSigByte);
    memWrite(addr + 1, mostSigByte);
}


uint16_t CPU::getOperandAddr(AddressingMode mode) 
{
    uint16_t imm = PC + 1;

    switch (mode)
    {
        case AddressingMode::Immediate: {
            return imm;
        }
        
        case AddressingMode::ZeroPage: {
            return (uint16_t)memRead(imm);
        }
        
        case AddressingMode::Absolute: {
            return memRead16(imm);
        }
        
        case AddressingMode::ZeroPage_X: {
            // todo: test this
            // implicit cast could cause some bullshit down the line.
            uint16_t base = (uint16_t)memRead(imm);
            uint16_t addr = base + X;
            return addr;
        }

        case AddressingMode::ZeroPage_Y: {
            uint16_t base = (uint16_t)memRead(imm);
            uint16_t addr = base + Y;
            return addr;
        }

        case AddressingMode::Absolute_X: {
            uint16_t base = memRead16(imm);
            uint16_t addr = base + X;
            return addr;
        }

        case AddressingMode::Absolute_Y: {
            uint16_t base = memRead16(imm);
            uint16_t addr = base + Y;
            return addr;
        }

        case AddressingMode::Indirect_X: {
            // more implicit casting...
            uint16_t base = memRead(imm);
            uint16_t ptr = base + X;

            uint16_t deref = memRead16(ptr);

            return deref;
        }

        case AddressingMode::Indirect_Y: {
            // more implicit casting...
            
            // ($01) -> $0001
            uint16_t ptr = memRead(imm);

            // $0001 -> val of $0001
            uint16_t deref = memRead16(ptr);

            // val of $0001 + Y -> final addr
            uint16_t addr = deref + Y;
            return addr;
        }

        default: 
            throw std::runtime_error("Unsupported/Unknown Addressing mode.");
            break;
    }
}


void CPU::reset()
{
    A = 0;
    X = 0;
    Y = 0;
    P.raw = 0;

    PC = memRead16(0xFFFC);
}

// todo: better container for program data
void CPU::load(std::vector<uint8_t> prog)
{
    // todo: this shouldn't be fixed
    std::copy(prog.begin(), prog.end(), memory.begin() + 0x8000);
    memWrite16(0xFFFC, 0x8000);
}

void CPU::loadRun(std::vector<uint8_t> prog)
{
    load(prog);
    reset();
    run();
}

void CPU::run()
{
    return;
}

void CPU::step() 
{
    execute();
    return;
}

void CPU::execute()
{
    using namespace Instruction;
    // move to loop / run?
    Opcode opcode = OpcodeTable[memRead(PC)];
    uint16_t nextPC = PC + opcode.len;
    uint16_t opaddr = getOperandAddr(opcode.mode);

    switch (opcode.name) 
    {
        case LDA: {
            // todo: overflow flag and whatnot
            A += memRead(opaddr);
            break;
        }

        case STA: {
            memWrite(opaddr, A);
            break;
        }
        
        case LDY: {
            memWrite(opaddr, Y);
            break;
        }

        default:
            throw std::runtime_error("Unimplemented instruction.");
            break;
    }

    // todo: is this right?
    PC = nextPC;
}
