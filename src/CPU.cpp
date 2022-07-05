#include <CPU.hpp>

#include <Opcode.hpp>
#include <util.hpp>

// std
#include <iostream>
#include <exception>
#include <vector>
#include <algorithm>


// inline flag calculation
namespace {
    inline bool checkZero(uint8_t val)
    {
        if (val == 0)
        {
            return true;
        }

        return false; 
    }

    inline bool checkNegative(uint8_t val)
    {
        if (nth_bit(val, 7))
        {
            return true;
        }

        return false;
    }
}

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

uint8_t CPU::genericRead()
{
    if (currentOpcode.mode == AddressingMode::Accumulator)
    {
        return A;
    }
    else
    {
        return memRead(getOperandAddr(currentOpcode.mode));
    }
}

// branch or jump
uint16_t CPU::genericRead16()
{

}

void CPU::genericWrite(uint8_t data)
{
    if (currentOpcode.mode == AddressingMode::Accumulator)
    {
        A = data;
    }
    else
    {
        memWrite(getOperandAddr(currentOpcode.mode), data);
    }
}

void CPU::sPush8(uint8_t val)
{
    // use var for stack base? (0x0100)
    memWrite(0x0100 + SP--, val);
}

void CPU::sPush16(uint16_t val)
{
    sPush8((val >> 8));
    sPush8((val & 0xff));
}

uint8_t CPU::sPop8()
{
    ++SP;
    return memRead(0x0100 + SP);
}

uint16_t CPU::sPop16()
{
    uint8_t leastSigByte = sPop8();
    uint8_t mostSigByte = sPop8();
    return (mostSigByte << 8) | leastSigByte;
}

uint16_t CPU::getOperandAddr(AddressingMode mode) 
{
    uint16_t imm = PC + 1;

    switch (mode)
    {
        // relative and immediate both return an immediate value
        case AddressingMode::Relative:
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
    currentOpcode = OpcodeTable[memRead(PC)];
    uint16_t nextPC = PC + currentOpcode.len;
    bool branched = false;

    switch (currentOpcode.name) 
    {
        case AND: { 
            const auto opaddr = getOperandAddr(currentOpcode.mode);
            A = A & memRead(opaddr);
            
            P.Z = checkZero(A);
            P.N = checkNegative(A);
            break;
        }

        case ASL: {
            auto operand = genericRead();
            P.C = nth_bit(operand, 7);

            operand <<= 1;
            genericWrite(operand);

            P.Z = checkZero(operand);
            P.N = checkNegative(operand);
            break;
        }

        case BCC: {
            // todo: branch instructions - advance cycles properly.
            const auto opaddr = getOperandAddr(currentOpcode.mode);
            if (P.C == 0)
            {
                nextPC = PC + memRead(opaddr);
            }
            break;
        }

        case BCS: {
            const auto opaddr = getOperandAddr(currentOpcode.mode);
            if (P.C == 1)
            {
                nextPC = PC + memRead(opaddr);
            }
            break;
        }

        case BEQ: {
            const auto opaddr = getOperandAddr(currentOpcode.mode);
            if (P.Z == 1)
            {
                nextPC = PC + memRead(opaddr);
            }
            break;
        }

        case BIT: {
            const auto opaddr = getOperandAddr(currentOpcode.mode);
            const auto operand = memRead(opaddr);

            P.Z = (A & operand) == 0;
            P.V = nth_bit(operand, 6);
            P.N = nth_bit(operand, 7);
            break;
        }

        case BMI: {
            const auto opaddr = getOperandAddr(currentOpcode.mode);
            if (P.N == 1)
            {
                nextPC = PC + memRead(opaddr);
            }
            break;
        }

        case BNE: {
            const auto opaddr = getOperandAddr(currentOpcode.mode);
            if (P.Z == 0)
            {
                nextPC = PC + memRead(opaddr);
            }
            break;
        }

        case BPL: {
            const auto opaddr = getOperandAddr(currentOpcode.mode);
            if (P.N == 0)
            {
                nextPC = PC + memRead(opaddr);
            }
            break;
        }

        case BVC: {
            const auto opaddr = getOperandAddr(currentOpcode.mode);
            if (P.V == 0)
            {
                nextPC = PC + memRead(opaddr);
            }
            break;
        }

        case BVS: {
            const auto opaddr = getOperandAddr(currentOpcode.mode);
            if (P.V == 1)
            {
                nextPC = PC + memRead(opaddr);
            }
            break;
        }

        case CLC: {
            P.C = 0;
            break;
        }

        case CLD: {
            P.D = 0;
            break;
        }

        case CLI: {
            P.I = 0;
            break;
        }

        case CLV: {
            P.V = 0;
            break;
        }

        case CMP: {
            const auto opaddr = getOperandAddr(currentOpcode.mode);
            const uint8_t op = memRead(opaddr);
            const uint8_t res = A - op;

            P.C = (A >= op);
            P.Z = checkZero(res);
            
            P.N = checkNegative(res);
            break;
        }

        case CPX: {
            const auto opaddr = getOperandAddr(currentOpcode.mode);
            const uint8_t op = memRead(opaddr);
            const uint8_t res = X - op;

            P.C = (X >= op);
            P.Z = checkZero(res);
            P.N = checkNegative(res);
            break;
        }
        
        case CPY: {
            const auto opaddr = getOperandAddr(currentOpcode.mode);
            const uint8_t op = memRead(opaddr);
            const uint8_t res = Y - op;

            P.C = (Y >= op);
            P.Z = checkZero(res);
            P.N = checkNegative(res);
            break;
        }

        case DEC: {
            const auto opaddr = getOperandAddr(currentOpcode.mode);
            const uint8_t op = memRead(opaddr);
            const uint8_t res = op - 1;

            memWrite(opaddr, res);

            P.Z = checkZero(res);
            P.N = checkNegative(res);
            break;
        }

        case DEX: {
            X -= 1;
            P.Z = checkZero(X);
            P.N = checkNegative(X);
            break;
        }

        case DEY: {
            Y -= 1;
            P.Z = checkZero(Y);
            P.N = checkNegative(Y);
            break;
        }

        case EOR: {
            const auto opaddr = getOperandAddr(currentOpcode.mode);
            const uint8_t op = memRead(opaddr);
            
            A ^= op;

            P.Z = checkZero(A);
            P.N = checkNegative(A);
            break;
        }

        case INC: {
            const auto opaddr = getOperandAddr(currentOpcode.mode);
            const uint8_t op = memRead(opaddr);
            const uint8_t res = op + 1;

            memWrite(opaddr, res);

            P.Z = checkZero(res);
            P.N = checkNegative(res);
            break;
        }

        case INX: {
            X += 1;
            P.Z = checkZero(X);
            P.N = checkNegative(X);
            break;
        }
        
        case INY: {
            Y += 1;
            P.Z = checkZero(Y);
            P.N = checkNegative(Y);
            break;
        }

        case JMP: {
            const auto opaddr = getOperandAddr(currentOpcode.mode);
            nextPC = memRead16(opaddr);
            break;
        }

        case JSR: {
            const auto opaddr = getOperandAddr(currentOpcode.mode);
            // bug prone?
            SP = PC - 1;
            nextPC = memRead16(opaddr); 
            break;
        }

        case LDA: {
            const auto opaddr = getOperandAddr(currentOpcode.mode);
            A = memRead(opaddr);
            P.Z = checkZero(A);
            P.N = checkNegative(A);
            break;
        }

        case LDX: {
            const auto opaddr = getOperandAddr(currentOpcode.mode);
            X = memRead(opaddr);
            P.Z = checkZero(X);
            P.N = checkNegative(X);
            break;
        }
        
        case LDY: {
            const auto opaddr = getOperandAddr(currentOpcode.mode);
            Y = memRead(opaddr);
            P.Z = checkZero(Y);
            P.N = checkNegative(Y);
            break;
        }

        case LSR: {
            auto operand = genericRead();
            P.C = nth_bit(operand, 0);

            operand >>= 1;
            genericWrite(operand);

            P.Z = checkZero(operand);
            break;
        }

        case NOP: {
            // me when
            break;
        }

        case ORA: {
            const auto opaddr = getOperandAddr(currentOpcode.mode);
            A |= memRead(opaddr);
            P.Z = checkZero(A);
            P.N = checkNegative(A);
            break;
        }

        case PHA: {
            sPush8(A);
            break;
        }

        case PHP: {
            sPush8(P.raw);
            break;
        }

        case PLA: {
            A = sPop8();
            break;
        }

        case PLP: {
            P.raw = sPop8();
            break;
        }


        default:
            throw std::runtime_error("Unimplemented instruction.");
            break;
    }

    // todo: is this right?
    if (!branched)
    {
        PC = nextPC;
    }
}
