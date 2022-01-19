#include "cpu.hpp"
namespace cpu6502{

    void CPU::CLDimplied(u32& Cycles) noexcept
    {
        // 1 Cycles
        cpu_reg.PS.set(PSFlags::DecimalMode, false);
        --Cycles;
        // 0 cycles
    }

}