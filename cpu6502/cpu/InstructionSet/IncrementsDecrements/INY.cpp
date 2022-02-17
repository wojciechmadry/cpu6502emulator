#include "cpu.hpp"

namespace cpu6502{

    void CPU::INYimplied(u32& Cycles) noexcept
    {
        const auto y_reg = cpu_reg.IRY.get();
        const auto increment = static_cast<Byte>(y_reg + 1);
        cpu_reg.IRY.set(increment);
        --Cycles;
        // 0 cycles

        cpu_reg.PS.set(PSFlags::ZeroFlag, increment == 0);
        cpu_reg.PS.set(PSFlags::NegativeFlag, static_cast<bool>(increment & 0x80));
    }
    
}