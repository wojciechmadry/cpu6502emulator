#include "cpu.hpp"
namespace cpu6502{
    void CPU::SED() noexcept
    {
        using op = cpu6502::opcode::SED;
        LookUpTable[static_cast<Byte>(op::Implied)] = [](u32& Cycles, CPU& cpu) -> void {
            // 1 Cycles
            cpu.cpu_reg.PS.set(PSFlags::DecimalMode, true);
            --Cycles;
            // 0 cycles
        };
    }
}