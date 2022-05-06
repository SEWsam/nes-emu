#pragma once

#include "../CPU.hpp"

#ifndef CPUDEBUGGER_USE_NULL_DEFAULT_CONSOLE
#include <iostream>
#define DEFAULT_CONSOLE std::cout
#else
#include "global_ns.hpp"
#define DEFAULT_CONSOLE  global_ns
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

    const PFlags& P() const& {return cpuPtr->P;};
    PFlags& P() & {return cpuPtr->P;};
    PFlags&& P() && {return std::move(cpuPtr->P);};
    // todo: once busses are implemented, allow both bus-based "safe" memory writing, and forced "unsafe" writes.
};