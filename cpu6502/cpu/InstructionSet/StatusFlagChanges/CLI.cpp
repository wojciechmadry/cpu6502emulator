#include "cpu.hpp"
namespace cpu6502{

    void CPU::CLIimplied(u32& Cycles) noexcept
    {
        // 1 Cycles
        cpu_reg.PS.set(PSFlags::InterruptDisable, false);
        --Cycles;
        // 0 cycles
    }
  
}
