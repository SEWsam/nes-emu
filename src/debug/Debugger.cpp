#include <debug/Debugger.hpp>

// std
#include <iostream>

void CPUDebugger::printRegisters(std::ostream& out)
{
    out <<
        "A: " << (int)cpuPtr->A << '\n' <<
        "X: " << (int)cpuPtr->X << '\n' <<
        "Y: " << (int)cpuPtr->Y << '\n' <<
        '\n' << 
        std::hex <<
        "PC: " << "0x" << (int)cpuPtr->PC << '\n' <<
        "SP: " << "0x" << (int)cpuPtr->SP << '\n';
}

void CPUDebugger::printRegisters()
{
    printRegisters(defaultConsole);
}

void CPUDebugger::executeInstruction(Byte opcode, uint16_t operand)
{
    auto op = OpcodeTable[opcode];
}