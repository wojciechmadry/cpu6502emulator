#include "cpu.hpp"

namespace cpu6502{

    void CPU::PLAimplied(u32& Cycles) noexcept
    {
        // 3 cycles
        Byte ACU = pop_byte_from_stack(Cycles);
        // 1 cycles
        cpu_reg.ACU.set(ACU);
        --Cycles;
        // 0 Cycles
        cpu_reg.PS.set(PSFlags::ZeroFlag, !static_cast<bool>(cpu_reg.ACU.get()));
        cpu_reg.PS.set(PSFlags::NegativeFlag, cpu_reg.ACU.get() & 0x80);
    }
  
}