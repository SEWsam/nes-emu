#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <CPU.hpp>
#include <util.hpp>
#include <debug/Debugger.hpp>
#include <Opcode.hpp>

#include "opcode_helper.hpp"

#include <vector>




TEST_CASE("The emulated CPU generates valid results for each instruction", "[CPU]") {
    CPU cpu{};
    CPUDebugger dbg{cpu};


    SECTION("AND (IMMEDIATE)") {

        // generation
        auto operand = GENERATE(take(50, random(0, 255)));
        auto A = GENERATE(take(1, random(0, 255)));

        // setup
        auto prog = program(0x29, operand);
        cpu.load(prog);
        cpu.reset();

        dbg.A() = A;


        cpu.step();
        REQUIRE((int)dbg.A() == (A & operand));  // result == A & imm
        REQUIRE((int)dbg.P().Z == (dbg.A() == 0)); // P.Z == 1 -> if result == 0
        REQUIRE((int)dbg.P().N == (nth_bit(dbg.A(), 7))); // P.N == 1 -> if result is signed (7th bit)
    }

    SECTION("ASL (ACCUMULATOR)") {
        // generation
        uint8_t A = GENERATE(take(50, random(0, 255)));

        // setup
        auto prog = program(0x0a);
        cpu.load(prog);
        cpu.reset();

        dbg.A() = A;

        cpu.step();
        REQUIRE(dbg.A() == ((A << 1) & 0xff));  // result == A << 1, truncated to 8 bits. (x & 0xff)
        REQUIRE(dbg.P().C == nth_bit(A, 7));  // C == 7th bit of original A value.
        REQUIRE(dbg.P().Z == (dbg.A() == 0));  // Z == 1 -> if result == 0
        REQUIRE(dbg.P().N == nth_bit(dbg.A(), 7));  // N == 1 -> if result is signed (7th bit)
    }

    SECTION("BCC (RELATIVE)") {
        auto rel = GENERATE(take(50, random(1, 255)));
        auto C = GENERATE(0, 1);

        auto prog = program(0x90, rel);
        cpu.load(prog);
        cpu.reset();

        uint16_t startPC = dbg.PC();

        dbg.P().C = C;

        cpu.step();

        // carry set
        if (C == 1) {
            REQUIRE(dbg.PC() == (startPC + 2));
        } else {  // carry not set
            REQUIRE(dbg.PC() == (startPC + rel));
        }
    }

    SECTION("BCS (RELATIVE)") {
        auto rel = GENERATE(take(50, random(1, 255)));
        auto C = GENERATE(0, 1);

        auto prog = program(0xB0, rel);
        cpu.load(prog);
        cpu.reset();

        uint16_t startPC = dbg.PC();

        dbg.P().C = C;

        cpu.step();

        // carry not set
        if (C == 0) {
            REQUIRE(dbg.PC() == (startPC + 2));
        } else {  // carry set
            REQUIRE(dbg.PC() == (startPC + rel));
        }
    }
    
    SECTION("BEQ (RELATIVE)") {
        auto rel = GENERATE(take(50, random(1, 255)));
        auto Z = GENERATE(0, 1);

        auto prog = program(0xf0, rel);
        cpu.load(prog);
        cpu.reset();

        uint16_t startPC = dbg.PC();

        dbg.P().Z = Z;

        cpu.step();

        // zero not set
        if (Z == 0) {
            REQUIRE(dbg.PC() == (startPC + 2));

        } else {  // zero set
            REQUIRE(dbg.PC() == (startPC + rel));
        }
    }

    SECTION("BIT (ZeroPage)") {
        auto addr = GENERATE(take(50, random(0, 255)));
        auto val = GENERATE(take(1, random(0, 255)));
        auto A_mask = GENERATE(take(1, random(1, 255)));

        auto prog = program(0x24, addr);
        cpu.load(prog);
        cpu.reset();

        dbg.memWrite(addr, val);
        dbg.A() = A_mask;

        cpu.step();
        REQUIRE(dbg.A() == A_mask);  // value is not kept
        REQUIRE(dbg.P().Z == ((A_mask & val) == 0));  // Z == 1 -> if A & operand is 0
        REQUIRE(dbg.P().V == nth_bit(val, 6));  // V = 6th bit of val
        REQUIRE(dbg.P().N == nth_bit(val, 7));  // N = 7th bit of val
    }

    SECTION("BMI (RELATIVE)") {
        auto rel = GENERATE(take(50, random(1, 255)));
        auto N = GENERATE(0, 1);

        auto prog = program(0x30, rel);
        cpu.load(prog);
        cpu.reset();

        uint16_t startPC = dbg.PC();

        dbg.P().N = N;

        cpu.step();

        // negative not set
        if (N == 0) {
            REQUIRE(dbg.PC() == (startPC + 2));
        } else {  // negative set
            REQUIRE(dbg.PC() == (startPC + rel));
        }
    }
    
    SECTION("BNE (RELATIVE)") {
        auto rel = GENERATE(take(50, random(1, 255)));
        auto Z = GENERATE(0, 1);

        auto prog = program(0xd0, rel);
        cpu.load(prog);
        cpu.reset();

        uint16_t startPC = dbg.PC();

        dbg.P().Z = Z;

        cpu.step();

        // zero set
        if (Z == 1) {
            REQUIRE(dbg.PC() == (startPC + 2));
        } else {  // zero clear
            REQUIRE(dbg.PC() == (startPC + rel));
        }
    }

    SECTION("BPL (RELATIVE)") {
        auto rel = GENERATE(take(50, random(1, 255)));
        auto N = GENERATE(0, 1);

        auto prog = program(0x10, rel);
        cpu.load(prog);
        cpu.reset();

        uint16_t startPC = dbg.PC();

        dbg.P().N = N;

        cpu.step();

        // negative set
        if (N == 1) {
            REQUIRE(dbg.PC() == (startPC + 2));
        } else {  // negative clear
            REQUIRE(dbg.PC() == (startPC + rel));
        }
    }

    
}