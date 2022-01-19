#include "cpu.hpp"
namespace cpu6502{

    void CPU::SEDimplied(u32& Cycles) noexcept
    {
        // 1 Cycles
        cpu_reg.PS.set(PSFlags::DecimalMode, true);
        --Cycles;
        // 0 cycles
    }

}