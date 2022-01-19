#include "cpu.hpp"

namespace cpu6502{

    void CPU::TXSimplied(u32& Cycles) noexcept
    {
        // 1 cycles
        cpu_reg.SP.set(cpu_reg.IRX.get());
        --Cycles;
        // 0 cycles
    }
    // remove this
    /*
    void CPU::TXS() noexcept
    {
        using op = cpu6502::opcode::TXS;
        LookUpTable[static_cast<Byte>(op::Implied)] = [](u32 &Cycles, CPU &cpu) -> void {
            // 1 cycles
            cpu.cpu_reg.SP.set(cpu.cpu_reg.IRX.get());
            --Cycles;
            // 0 cycles
        };
    }*/
}