#include "Opcode.hpp"
#include "CPU.hpp"

// std
#include <vector>
#include <iostream>


std::vector<uint8_t> prog = {
    0xa9, 0x08,
    0x8d, 0x10
};

int main(int argc, char** argv) {
    CPU cpu{};
    cpu.loadRun(prog);

        cpu.step();
        cpu.step();

    assert(cpu.memRead(0x0010) == 5);
    return 0;
}
