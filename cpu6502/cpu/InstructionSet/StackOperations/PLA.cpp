#include "cpu.hpp"

namespace cpu6502{
    void CPU::PLA() noexcept
    {
        using op = cpu6502::opcode::PLA;
        LookUpTable[static_cast<Byte>(op::Implied)] = [](u32 &Cycles, CPU &cpu) -> void {
            // 3 cycles
            Byte ACU = cpu.pop_byte_from_stack(Cycles);
            // 1 cycles
            cpu.cpu_reg.ACU.set(ACU);
            --Cycles;
            // 0 Cycles
            cpu.cpu_reg.PS.set(PSFlags::ZeroFlag, !static_cast<bool>(cpu.cpu_reg.ACU.get()));
            cpu.cpu_reg.PS.set(PSFlags::NegativeFlag, cpu.cpu_reg.ACU.get() & 0x80);
        };
    }
}