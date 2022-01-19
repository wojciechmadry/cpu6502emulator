#include "cpu.hpp"
namespace cpu6502{

    void CPU::CLCimplied(u32& Cycles) noexcept
    {
        // 1 Cycles
        cpu_reg.PS.set(PSFlags::CarryFlag, false);
        --Cycles;
        // 0 cycles
    }
  
}