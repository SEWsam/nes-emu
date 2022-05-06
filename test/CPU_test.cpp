#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <CPU.hpp>
#include <util.hpp>
#include <debug/Debugger.hpp>
#include <Opcode.hpp>

#include "opcode_helper.hpp"

#include <vector>




TEST_CASE("The emulated CPU generates valid results for each instruction", "[CPU]") {
    NullStream ns;
    CPU cpu{};
    CPUDebugger cpuDbg{cpu};


    SECTION("AND") {
        auto testData = GENERATE(
            take(1, opcode(0x29, AddressingMode::Immediate)),
            take(1, opcode(0x25, AddressingMode::ZeroPage)),
            take(1, opcode(0x35, AddressingMode::ZeroPage_X))
        );
        // idea: 
        // op.setup(cpuDbg) -> {imm: A = _  | zpg: A = _, mem[(u16)zpg] = _}
        auto initialA = GENERATE(take(50 ,random(1, 255)));
        std::vector<uint8_t> prog = {static_cast<uint8_t>(testData.code), static_cast<uint8_t>(testData.genData)};

        /*
        SECTION("IMMEDIATE") {
            cpu.reset();

            auto operand = GENERATE(take(50, operand(AddressingMode::Immediate)));
            auto A = GENERATE(take(1, ))
        }
        */
    }

}