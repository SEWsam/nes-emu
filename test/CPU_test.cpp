#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <CPU.hpp>
#include <util.hpp>
#include <debug/Debugger.hpp>
#include <Opcode.hpp>

#include "instruction_helper.hpp"

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
        BRANCH_TEST(0x90, C, 0);
    }

    SECTION("BCS (RELATIVE)") {
        BRANCH_TEST(0xb0, C, 1);
    }
    
    SECTION("BEQ (RELATIVE)") {
        BRANCH_TEST(0xf0, Z, 1);
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
        BRANCH_TEST(0x30, N, 1);
    }
    
    SECTION("BNE (RELATIVE)") {
        BRANCH_TEST(0xd0, Z, 0);
    }

    SECTION("BPL (RELATIVE)") {
        BRANCH_TEST(0x10, N, 0);
    }

    SECTION("BVC (RELATIVE)") {
        BRANCH_TEST(0x50, V, 0);
    }

    SECTION("BVS (RELATIVE)") {
        BRANCH_TEST(0x70, V, 1);
    }

    SECTION("CLC (Implied)") {
        auto prog = program(0x18);
        cpu.load(prog);
        cpu.reset();
        cpu.step();

        REQUIRE(dbg.P().C == 0);
    }
    
    SECTION("CLD (Implied)") {
        auto prog = program(0x18);
        cpu.load(prog);
        cpu.reset();
        cpu.step();

        REQUIRE(dbg.P().D == 0);
    }

    SECTION("CLI (Implied)") {
        auto prog = program(0x58);
        cpu.load(prog);
        cpu.reset();
        cpu.step();

        REQUIRE(dbg.P().I == 0);
    }

    SECTION("CLV (Implied)") {
        auto prog = program(0xb8);
        cpu.load(prog);
        cpu.reset();
        cpu.step();

        REQUIRE(dbg.P().V == 0);
    }

    SECTION("CMP (Immediate)") {
        auto A = GENERATE(range(0, 255));
        auto val = GENERATE(range(0, 255));
        
        const uint8_t res = A - val;

        auto prog = program(0xc9, val);
        cpu.load(prog);
        cpu.reset();

        dbg.A() = A;

        cpu.step();

        if (A >= val)
        {
            REQUIRE(dbg.P().C == 1);
        }
        if (A == val)
        {
            REQUIRE(dbg.P().Z == 1);
        }
        if (nth_bit(res, 7))
        {
            REQUIRE(dbg.P().N == 1);
        }
    }

    SECTION("CPX (Immediate)") {
        auto X = GENERATE(range(0, 255));
        auto val = GENERATE(range(0, 255));

        const uint8_t res = X - val;

        auto prog = program(0xe0, val);
        cpu.load(prog);
        cpu.reset();

        dbg.X() = X;

        cpu.step();

        if (X >= val)
        {
            REQUIRE(dbg.P().C == 1);
        }
        if (X == val)
        {
            REQUIRE(dbg.P().Z == 1);
        }
        if (nth_bit(res, 7))
        {
            REQUIRE(dbg.P().N == 1);
        }
    }

    SECTION("CPY (Immediate)") {
        auto Y = GENERATE(range(0, 255));
        auto val = GENERATE(range(0, 255));

        const uint8_t res = Y - val;

        auto prog = program(0xc0, val);
        cpu.load(prog);
        cpu.reset();

        dbg.Y() = Y;

        cpu.step();

        if (Y >= val)
        {
            REQUIRE(dbg.P().C == 1);
        }
        if (Y == val)
        {
            REQUIRE(dbg.P().Z == 1);
        }
        if (nth_bit(res, 7))
        {
            REQUIRE(dbg.P().N == 1);
        }
    }

    SECTION("DEC (ZeroPage)") {
        uint8_t addr = GENERATE(range(0, 255));
        auto val = GENERATE(range(0, 255));

        const uint8_t res = val - 1;

        auto prog = program(0xc6, addr);
        cpu.load(prog);
        cpu.reset();

        dbg.memWrite(addr, val);
        
        cpu.step();

        if (res == 0)
        {
            REQUIRE(dbg.P().Z == 1);
        }
        if (nth_bit(res, 7))
        {
            REQUIRE(dbg.P().N == 1);
        }

        REQUIRE(dbg.memRead(addr) == res);
    }

    SECTION("PHA (Accumulator)") {
        uint8_t A = GENERATE(range(0, 255));

        auto prog = program(0x48);
        cpu.load(prog);
        cpu.reset();

        dbg.A() = A;

        cpu.step();

        REQUIRE(dbg.sPop8() == A);
    }

}