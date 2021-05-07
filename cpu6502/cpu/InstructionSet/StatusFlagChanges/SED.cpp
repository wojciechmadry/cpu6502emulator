#include "cpu.hpp"
namespace cpu6502{
    void CPU::SED() noexcept
    {
        using op = cpu6502::opcode::SED;
        LookUpTable[static_cast<Byte>(op::Implied)] = [this](u32& Cycles) -> void {
            // 1 Cycles
            cpu_reg.PS.set(PSFlags::DecimalMode, true);
            --Cycles;
            // 0 cycles
        };
    }
}