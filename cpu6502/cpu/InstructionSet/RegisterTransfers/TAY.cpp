#include "cpu.hpp"
namespace cpu6502{

    void CPU::TAYimplied(u32& Cycles) noexcept
    {
        // 1 Cycles
        cpu_reg.IRY.set(cpu_reg.ACU.get());
        --Cycles;
        // 0 cycles
        cpu_reg.PS.set(PSFlags::ZeroFlag, !static_cast<bool>(cpu_reg.IRY.get()));
        cpu_reg.PS.set(PSFlags::NegativeFlag, cpu_reg.IRY.get() & 0x80);
    }
    // remove this
    /*
    void CPU::TAY() noexcept
    {
        using op = cpu6502::opcode::TAY;
        LookUpTable[static_cast<Byte>(op::Implied)] = [](u32& Cycles, CPU& cpu) -> void {
            // 1 Cycles
            cpu.cpu_reg.IRY.set(cpu.cpu_reg.ACU.get());
            --Cycles;
            // 0 cycles
            cpu.cpu_reg.PS.set(PSFlags::ZeroFlag, !static_cast<bool>(cpu.cpu_reg.IRY.get()));
            cpu.cpu_reg.PS.set(PSFlags::NegativeFlag, cpu.cpu_reg.IRY.get() & 0x80);
        };
    }*/
}