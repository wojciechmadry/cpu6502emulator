#include "cpu.hpp"
namespace cpu6502{
    void CPU::TXA() noexcept
    {
        auto InitFlag = [this]()->void{
            cpu_reg.PS.set(PSFlags::ZeroFlag, !static_cast<bool>(cpu_reg.ACU.get()));
            cpu_reg.PS.set(PSFlags::NegativeFlag, cpu_reg.ACU.get() & 0x80);
        };

        using op = cpu6502::opcode::TXA;

        LookUpTable[static_cast<Byte>(op::Implied)] = [this, InitFlag](u32& Cycles) -> void {
            // 1 Cycles
            cpu_reg.ACU.set(cpu_reg.IRX.get());
            --Cycles;
            // 0 cycles
            InitFlag();
        };
    }
}