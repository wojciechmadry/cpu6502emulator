#include "cpu.hpp"

namespace cpu6502{
    
    void CPU::CMPimmediate(u32& Cycles) noexcept
    {
        (void) Cycles;
    }

    void CPU::CMPzeropage(u32& Cycles) noexcept
    {
        (void) Cycles;
    }

    void CPU::CMPzeropagex(u32& Cycles) noexcept
    {
        (void) Cycles;
    }

    void CPU::CMPabsolute(u32& Cycles) noexcept
    {
        (void) Cycles;
    }


    void CPU::CMPabsolutex(u32& Cycles) noexcept
    {
        (void) Cycles;
    }


    void CPU::CMPabsolutey(u32& Cycles) noexcept
    {
        (void) Cycles;
    }


    void CPU::CMPindirectx(u32& Cycles) noexcept
    {
        (void) Cycles;
    }


    void CPU::CMPindirecty(u32& Cycles) noexcept
    {
        (void) Cycles;
    }
    
    // remove this
    /*void CPU::CMP() noexcept
    {
        using op = cpu6502::opcode::CMP;

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