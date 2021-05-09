#include "cpu.hpp"

namespace cpu6502{
    void CPU::TAX() noexcept
    {
        using op = cpu6502::opcode::TAX;
        LookUpTable[static_cast<Byte>(op::Implied)] = [](u32 &Cycles, CPU &cpu) -> void {
            // 1 Cycles
            cpu.cpu_reg.IRX.set(cpu.cpu_reg.ACU.get());
            --Cycles;
            // 0 cycles
            cpu.cpu_reg.PS.set(PSFlags::ZeroFlag, !static_cast<bool>(cpu.cpu_reg.IRX.get()));
            cpu.cpu_reg.PS.set(PSFlags::NegativeFlag, cpu.cpu_reg.IRX.get() & 0x80);
        };
    }
}