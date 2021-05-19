#include "cpu.hpp"

namespace cpu6502{
    void CPU::TSX() noexcept
    {
        using op = cpu6502::opcode::TSX;
        LookUpTable[static_cast<Byte>(op::Implied)] = [](u32 &Cycles, CPU &cpu) -> void {
            // 1 Cycles
            cpu.cpu_reg.IRX.set(cpu.cpu_reg.SP.get());
            --Cycles;
            //0 Cycles
            cpu.cpu_reg.PS.set(PSFlags::ZeroFlag, !static_cast<bool>(cpu.cpu_reg.IRX.get()));
            cpu.cpu_reg.PS.set(PSFlags::NegativeFlag, cpu.cpu_reg.IRX.get() & 0x80);
        };
    }
}