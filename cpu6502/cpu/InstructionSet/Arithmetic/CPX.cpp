#include "cpu.hpp"

namespace cpu6502{

    void CPU::CPXimmediate(u32& Cycles) noexcept
    {
        (void) Cycles;
    }

    void CPU::CPXzeropage(u32& Cycles) noexcept
    {
        (void) Cycles;
    }

    void CPU::CPXabsolute(u32& Cycles) noexcept
    {
        (void) Cycles;
    }

    // remove this
    /*
    void CPU::CPX() noexcept
    {
        using op = cpu6502::opcode::CPX;

        auto cast = [](op Opcode) -> Byte {
            return static_cast<Byte>(Opcode);
        };

        LookUpTable[cast(op::Immediate)] = [](u32& Cycles, CPU& cpu) -> void
        {
            (void) Cycles;
            (void) cpu;
        };

        LookUpTable[cast(op::ZeroPage)] = [](u32& Cycles, CPU& cpu) -> void
        {
            (void) Cycles;
            (void) cpu;
        };

        LookUpTable[cast(op::Absolute)] = [](u32& Cycles, CPU& cpu) -> void
        {
            (void) Cycles;
            (void) cpu;
        };

    }*/
}