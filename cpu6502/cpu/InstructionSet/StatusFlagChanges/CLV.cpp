#include "cpu.hpp"
namespace cpu6502{

    void CPU::CLVimplied(u32& Cycles) noexcept
    {
        // 1 Cycles
        cpu_reg.PS.set(PSFlags::OverflowFlag, false);
        --Cycles;
        // 0 cycles
    }
  
}
