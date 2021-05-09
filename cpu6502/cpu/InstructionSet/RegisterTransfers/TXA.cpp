#include "cpu.hpp"
namespace cpu6502{
    void CPU::TXA() noexcept
    {

        using op = cpu6502::opcode::TXA;

        LookUpTable[static_cast<Byte>(op::Implied)] = [](u32& Cycles, CPU& cpu) -> void {
            // 1 Cycles
            cpu.cpu_reg.ACU.set(cpu.cpu_reg.IRX.get());
            --Cycles;
            // 0 cycles
            cpu.cpu_reg.PS.set(PSFlags::ZeroFlag, !static_cast<bool>(cpu.cpu_reg.ACU.get()));
            cpu.cpu_reg.PS.set(PSFlags::NegativeFlag, cpu.cpu_reg.ACU.get() & 0x80);
        };
    }
}