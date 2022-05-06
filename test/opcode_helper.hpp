#pragma once

#include <catch2/catch.hpp>

struct OpcodeGenPair
{
    unsigned char code;
    int genData;
};

struct GeneratedCPUData
{
    uint8_t A;
    uint8_t X;
    uint8_t Y;

    uint8_t memory[0xFFFF];

    uint16_t operand;
};


class OpcodePairGenerator : public Catch::Generators::IGenerator<OpcodeGenPair>
{
    OpcodeGenPair pair;

    unsigned char code;
    AddressingMode mode;

public:
    OpcodePairGenerator(unsigned char code, AddressingMode mode) : code(code), mode(mode)
    {
        static_cast<void>(next());
    }

    OpcodeGenPair const& get() const override;
    bool next() override
    {
        // todo: implement all cases, provide function to setup CPU based on addressing mode and sample values.
        switch (mode)
        {
            case AddressingMode::Immediate: {
                auto data = Catch::Generators::random(1, 255).get();
                pair = OpcodeGenPair{code, data};
                break;
            }
            
            case AddressingMode::ZeroPage: {
                auto data = Catch::Generators::random(20, 30).get();
                pair = OpcodeGenPair{code, data};
                break;
            }

            case AddressingMode::ZeroPage_X: {
                auto data = Catch::Generators::random(20, 30).get();
                pair = OpcodeGenPair{code, data};
                break;
            }
        }

        return true;
    }
};

OpcodeGenPair const& OpcodePairGenerator::get() const 
{
    return pair;
}

Catch::Generators::GeneratorWrapper<OpcodeGenPair> opcode(unsigned char code, AddressingMode mode)
{
    return Catch::Generators::GeneratorWrapper<OpcodeGenPair>(std::unique_ptr<Catch::Generators::IGenerator<OpcodeGenPair>>(new OpcodePairGenerator{code, mode}));
}


#define OPC(count, code, mode) take(count, opcode(code, mode))