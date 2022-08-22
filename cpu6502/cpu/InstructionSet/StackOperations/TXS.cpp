#include "cpu.hpp"

namespace cpu6502{

    void CPU::TXSimplied(u32& Cycles) noexcept
    {
        // 1 cycles
        cpu_reg.SP.set(cpu_reg.IRX.get());
        --Cycles;
        // 0 cycles
    }
 
}
