#pragma once


#include <optional>
#include <vector>

inline std::vector<uint8_t> program(unsigned char opcode, std::optional<uint16_t> operand = std::nullopt) 
{
    std::vector<uint8_t> prog;
    prog.push_back(opcode);
    if (operand)
    {
        auto op = *operand;
        if ((op >> 8) != 0) 
        {
            uint8_t leastSigByte = (op & 0xff);
            uint8_t mostSigByte = (op >> 8);
            prog.push_back(leastSigByte);
            prog.push_back(mostSigByte);
        }
        else
        {
            prog.push_back((op & 0xff));
        }
    }

    return prog;
}

#define BRANCH_TEST(opcode, flag_name, val) \
    auto rel = GENERATE(range(1, 255)); \
    auto flag_name = GENERATE(0, 1); \
    auto prog = program(opcode, rel); \
    cpu.load(prog); \
    cpu.reset(); \
    uint16_t startPC = dbg.PC(); \
    dbg.P().flag_name = flag_name; \
    cpu.step(); \
    if (flag_name == val) { \
        REQUIRE(dbg.PC() == (startPC + rel)); \
    } else { \
        REQUIRE(dbg.PC() == (startPC + 2)); \
    }

