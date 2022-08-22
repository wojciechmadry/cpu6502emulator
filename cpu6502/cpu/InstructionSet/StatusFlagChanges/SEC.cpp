#include "cpu.hpp"
namespace cpu6502{

    void CPU::SECimplied(u32& Cycles) noexcept
    {
        // 1 Cycles
        cpu_reg.PS.set(PSFlags::CarryFlag, true);
        --Cycles;
        // 0 cycles
    }

}
