#include "cpu.hpp"
namespace cpu6502{
    void CPU::branch_if(u32& Cycles, bool If) noexcept
    {
        // 3 cycles
        auto Fetched = static_cast<SByte>(fetch_byte(Cycles));
        // 2 Cycles
        if( If )
        {
            Word PC = cpu_reg.PC.get();
            cpu_reg.PC.set(static_cast<Word>(PC + Fetched));
            --Cycles;

            // 1 Cycles
            if ( (cpu_reg.PC.get() >> 8) != (PC>>8) ) // Page cross
            {
                --Cycles;
                // 0 Cycles
            }
        }

    }

    void CPU::BRANCHbcc(u32& Cycles) noexcept
    {
        branch_if(Cycles, !cpu_reg.PS.get(PSFlags::CarryFlag));
    }

    void CPU::BRANCHbcs(u32& Cycles) noexcept
    {
        branch_if(Cycles, cpu_reg.PS.get(PSFlags::CarryFlag));
    }

    void CPU::BRANCHbeq(u32& Cycles) noexcept
    {
        branch_if(Cycles, cpu_reg.PS.get(PSFlags::ZeroFlag));
    }

    void CPU::BRANCHbmi(u32& Cycles) noexcept
    {
        branch_if(Cycles, cpu_reg.PS.get(PSFlags::NegativeFlag));
    }

    void CPU::BRANCHbne(u32& Cycles) noexcept
    {
        branch_if(Cycles, !cpu_reg.PS.get(PSFlags::ZeroFlag));
    }

    void CPU::BRANCHbpl(u32& Cycles) noexcept
    {
        branch_if(Cycles, !cpu_reg.PS.get(PSFlags::NegativeFlag));
    }

    void CPU::BRANCHbvc(u32& Cycles) noexcept
    {
        branch_if(Cycles, !cpu_reg.PS.get(PSFlags::OverflowFlag));
    }

    void CPU::BRANCHbvs(u32& Cycles) noexcept
    {
        branch_if(Cycles, cpu_reg.PS.get(PSFlags::OverflowFlag));
    }

}