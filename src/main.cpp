#include "Opcode.hpp"
#include "CPU.hpp"
#include "debug/Debugger.hpp"

// std
#include <vector>
#include <iostream>


std::vector<uint8_t> prog = {
    0xa9, 0x0c,        // LDA #$0c
    0x8d, 0x20, 0x00,  // STA $0020
    0xa9, 0x1f,
    0x85, 0x10,
    0xa9, 0x00, 
    0x85, 0x11,
    0xa0, 0x01,
    0xb1, 0x10,
    0x19 // error 
};

int main(int argc, char** argv) {
    CPU cpu{};
    cpu.loadRun(prog);

    while (true)
    {
        try {
            cpu.step();
        }
        catch (std::exception& e) {
            std::cout << e.what() << '\n';
            break;
        }
    }

    CPUDebugger dbg{std::cout, cpu};
    dbg.printRegisters();

    return 0;
}
