#include "cpu.hpp"

namespace cpu6502{

    void CPU::SBCimmediate(u32& Cycles) noexcept
    {
        (void) Cycles;
    }

    void CPU::SBCzeropage(u32& Cycles) noexcept
    {
        (void) Cycles;
    }

    void CPU::SBCzeropagex(u32& Cycles) noexcept
    {
        (void) Cycles;
    }

    void CPU::SBCabsolute(u32& Cycles) noexcept
    {
        (void) Cycles;
    }


    void CPU::SBCabsolutex(u32& Cycles) noexcept
    {
        (void) Cycles;
    }


    void CPU::SBCabsolutey(u32& Cycles) noexcept
    {
        (void) Cycles;
    }


    void CPU::SBCindirectx(u32& Cycles) noexcept
    {
        (void) Cycles;
    }


    void CPU::SBCindirecty(u32& Cycles) noexcept
    {
        (void) Cycles;
    }

    // remove this
    /*
    void CPU::SBC() noexcept
    {
        using op = cpu6502::opcode::SBC;

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

        LookUpTable[cast(op::ZeroPageX)] = [](u32& Cycles, CPU& cpu) -> void
        {
            (void) Cycles;
            (void) cpu;
        };

        LookUpTable[cast(op::Absolute)] = [](u32& Cycles, CPU& cpu) -> void
        {
            (void) Cycles;
            (void) cpu;
        };

        LookUpTable[cast(op::AbsoluteX)] = [](u32& Cycles, CPU& cpu) -> void
        {
            (void) Cycles;
            (void) cpu;
        };

        LookUpTable[cast(op::AbsoluteY)] = [](u32& Cycles, CPU& cpu) -> void
        {
            (void) Cycles;
            (void) cpu;
        };

        LookUpTable[cast(op::IndirectX)] = [](u32& Cycles, CPU& cpu) -> void
        {
            (void) Cycles;
            (void) cpu;
        };

        LookUpTable[cast(op::IndirectY)] = [](u32& Cycles, CPU& cpu) -> void
        {
            (void) Cycles;
            (void) cpu;
        };
    }*/
}