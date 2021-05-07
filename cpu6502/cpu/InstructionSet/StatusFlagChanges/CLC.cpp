#include "cpu.hpp"
namespace cpu6502{
    void CPU::CLC() noexcept
    {
        using op = cpu6502::opcode::CLC;
        LookUpTable[static_cast<Byte>(op::Implied)] = [this](u32& Cycles) -> void {
            // 1 Cycles
            cpu_reg.PS.set(PSFlags::CarryFlag, false);
            --Cycles;
            // 0 cycles
        };
    }
}