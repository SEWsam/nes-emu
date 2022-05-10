#include <debug/Debugger.hpp>

// std
#include <iostream>


void CPUDebugger::checkPtr()
{
    if (cpuPtr == nullptr)
    {
        throw std::runtime_error("Pointer to CPU in CPUDebugger is invalid.");
    }
}


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


void CPUDebugger::memWrite(uint16_t addr, uint8_t val)
{
    checkPtr();
    cpuPtr->memWrite(addr, val);
}

void CPUDebugger::memWrite16(uint16_t addr, uint16_t val)
{
    checkPtr();
    cpuPtr->memWrite16(addr, val);
}

uint8_t CPUDebugger::memRead(uint16_t addr)
{
    checkPtr();
    return cpuPtr->memRead(addr);
}

uint16_t CPUDebugger::memRead16(uint16_t addr)
{
    checkPtr();
    return cpuPtr->memRead16(addr);
}