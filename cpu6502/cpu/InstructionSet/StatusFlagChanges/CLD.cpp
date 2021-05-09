#include "cpu.hpp"
namespace cpu6502{
    void CPU::CLD() noexcept
    {
        using op = cpu6502::opcode::CLD;
        LookUpTable[static_cast<Byte>(op::Implied)] = [](u32& Cycles, CPU& cpu) -> void {
            // 1 Cycles
            cpu.cpu_reg.PS.set(PSFlags::DecimalMode, false);
            --Cycles;
            // 0 cycles
        };
    }
}