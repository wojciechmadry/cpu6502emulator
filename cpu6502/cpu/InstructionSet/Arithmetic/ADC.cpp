#include "cpu.hpp"

namespace cpu6502{
    void CPU::ADCimmediate(u32& Cycles) noexcept
    {
        (void) Cycles;
    }

    void CPU::ADCzeropage(u32& Cycles) noexcept
    {
        (void) Cycles;
    }

    void CPU::ADCzeropagex(u32& Cycles) noexcept
    {
        (void) Cycles;
    }

    void CPU::ADCabsolute(u32& Cycles) noexcept
    {
        (void) Cycles;
    }


    void CPU::ADCabsolutex(u32& Cycles) noexcept
    {
        (void) Cycles;
    }


    void CPU::ADCabsolutey(u32& Cycles) noexcept
    {
        (void) Cycles;
    }


    void CPU::ADCindirectx(u32& Cycles) noexcept
    {
        (void) Cycles;
    }


    void CPU::ADCindirecty(u32& Cycles) noexcept
    {
        (void) Cycles;
    }
/*
    void CPU::ADC() noexcept
    {
        using op = cpu6502::opcode::ADC;

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
    }
    */
}