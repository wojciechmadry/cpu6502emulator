#include "cpu.hpp"

namespace cpu6502{

    void CPU::INXimplied(u32& Cycles) noexcept
    {
        const auto x_reg = cpu_reg.IRX.get();
        const auto increment = static_cast<Byte>(x_reg + 1);
        cpu_reg.IRX.set(increment);
        --Cycles;
        // 0 cycles

        cpu_reg.PS.set(PSFlags::ZeroFlag, increment == 0);
        cpu_reg.PS.set(PSFlags::NegativeFlag, static_cast<bool>(increment & 0x80));
    }
    
}
