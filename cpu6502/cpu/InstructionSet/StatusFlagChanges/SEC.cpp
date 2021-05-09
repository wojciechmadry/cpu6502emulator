#include "cpu.hpp"
namespace cpu6502{
    void CPU::SEC() noexcept
    {
        using op = cpu6502::opcode::SEC;
        LookUpTable[static_cast<Byte>(op::Implied)] = [](u32& Cycles, CPU& cpu) -> void {
            // 1 Cycles
            cpu.cpu_reg.PS.set(PSFlags::CarryFlag, true);
            --Cycles;
            // 0 cycles
        };
    }
}