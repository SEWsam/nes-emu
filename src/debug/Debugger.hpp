#pragma once

#include "../CPU.hpp"


class CPUDebugger
{
private:
    CPU* cpuPtr;
    std::ostream& console;
public:
    CPUDebugger(std::ostream& c) : console(c), cpuPtr(nullptr) {}
    CPUDebugger(std::ostream& c, CPU& cpu) : console(c), cpuPtr(&cpu) {}
    ~CPUDebugger() {detach(); }

    void attach(CPU& cpu) {cpuPtr = &cpu; }
    void detach() {cpuPtr = nullptr; }

    void printRegisters(std::ostream& out);
    void printRegisters();

    uint8_t getA() {return cpuPtr->A;};
    uint8_t getX() {return cpuPtr->X;};
    uint8_t getY() {return cpuPtr->Y;};
    void setA(uint8_t val) {cpuPtr->A = val;};
    void setX(uint8_t val) {cpuPtr->X = val;};
    void setY(uint8_t val) {cpuPtr->Y = val;};
    // todo: once busses are implemented, allow both bus-based "safe" memory writing, and forced "unsafe" writes.
};