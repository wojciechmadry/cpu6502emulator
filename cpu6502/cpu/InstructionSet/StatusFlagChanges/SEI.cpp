#include "cpu.hpp"
namespace cpu6502{

    void CPU::SEIimplied(u32& Cycles) noexcept
    {
        // 1 Cycles
        cpu_reg.PS.set(PSFlags::InterruptDisable, true);
        --Cycles;
        // 0 cycles
    }
    
}
