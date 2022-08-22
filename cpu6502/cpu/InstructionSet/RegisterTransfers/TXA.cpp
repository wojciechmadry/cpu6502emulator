#include "cpu.hpp"
namespace cpu6502{

    void CPU::TXAimplied(u32& Cycles) noexcept
    {
        // 1 Cycles
        cpu_reg.ACU.set(cpu_reg.IRX.get());
        --Cycles;
        // 0 cycles
        cpu_reg.PS.set(PSFlags::ZeroFlag, !static_cast<bool>(cpu_reg.ACU.get()));
        cpu_reg.PS.set(PSFlags::NegativeFlag, cpu_reg.ACU.get() & 0x80);
    }
   
}
