#include "cpu.hpp"
namespace cpu6502{
    void CPU::TAX() noexcept
    {
        auto InitFlag = [this]()->void{
            cpu_reg.PS.set(PSFlags::ZeroFlag, !static_cast<bool>(cpu_reg.IRX.get()));
            cpu_reg.PS.set(PSFlags::NegativeFlag, cpu_reg.IRX.get() & 0x80);
        };

        using op = cpu6502::opcode::TAX;
        LookUpTable[static_cast<Byte>(op::Implied)] = [this, InitFlag](u32& Cycles) -> void {
            // 1 Cycles
            cpu_reg.IRX.set(cpu_reg.ACU.get());
            --Cycles;
            // 0 cycles
            InitFlag();
        };
    }
}