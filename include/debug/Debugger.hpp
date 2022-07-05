#pragma once

#include "../CPU.hpp"

#ifndef CPUDEBUGGER_USE_NULL_DEFAULT_CONSOLE
#include <iostream>
#define DEFAULT_CONSOLE std::cout
#else
#include "../util.hpp"
#define DEFAULT_CONSOLE  nullstream
#endif


class CPUDebugger
{
private:
    CPU* cpuPtr;
    std::ostream& defaultConsole;

    void checkPtr();
public:
    CPUDebugger(CPU& cpu) : cpuPtr(&cpu), defaultConsole(DEFAULT_CONSOLE) {}
    CPUDebugger(CPU& cpu, std::ostream& c) : cpuPtr(&cpu), defaultConsole(c) {}
    ~CPUDebugger() {detach(); }

    void attach(CPU& cpu) {cpuPtr = &cpu; }
    void detach() {cpuPtr = nullptr; }

    void printRegisters(std::ostream& out);
    void printRegisters();

    void executeInstruction(Byte opcode, uint16_t operand);

    const uint8_t& A() const& {return cpuPtr->A;};
    uint8_t& A() & {return cpuPtr->A;};
    uint8_t&& A() && {return std::move(cpuPtr->A);};

    const uint8_t& X() const& {return cpuPtr->X;};
    uint8_t& X() & {return cpuPtr->X;};
    uint8_t&& X() && {return std::move(cpuPtr->X);};
    
    const uint8_t& Y() const& {return cpuPtr->Y;};
    uint8_t& Y() & {return cpuPtr->Y;};
    uint8_t&& Y() && {return std::move(cpuPtr->Y);};

    const CPUFlags& P() const& {return cpuPtr->P;};
    CPUFlags& P() & {return cpuPtr->P;};
    CPUFlags&& P() && {return std::move(cpuPtr->P);};

    const uint16_t& PC() const& {return cpuPtr->PC;};

    void memWrite(uint16_t addr, uint8_t val);
    void memWrite16(uint16_t addr, uint16_t val);

    uint8_t memRead(uint16_t addr);
    uint16_t memRead16(uint16_t addr);

    void sPush8(uint8_t val);
    void sPush16(uint16_t val);
    uint8_t sPop8();
    uint16_t sPop16();

    // todo: once busses are implemented, allow both bus-based "safe" memory writing, and forced "unsafe" writes.
};