#include "cpu.hpp"

namespace cpu6502{
    void CPU::PHP() noexcept
    {
        using op = cpu6502::opcode::PHP;
        LookUpTable[static_cast<Byte>(op::Implied)] = [](u32 &Cycles, CPU &cpu) -> void {
           // 2 Cycles
           Byte StatusFlag = cpu.cpu_reg.PS.pull_byte();
           --Cycles;
           // 1 Cycles
           cpu.push_byte_to_stack(StatusFlag, Cycles);
           // 0 Cycles
        };
    }
}