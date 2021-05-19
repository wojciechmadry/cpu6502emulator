#include "cpu.hpp"

namespace cpu6502{
    void CPU::PHA() noexcept
    {
        using op = cpu6502::opcode::PHA;
        LookUpTable[static_cast<Byte>(op::Implied)] = [](u32 &Cycles, CPU &cpu) -> void {
            // 2 Cycles
            Byte ACU = cpu.cpu_reg.ACU.get();
            --Cycles;
            // 1 Cycles
            cpu.push_byte_to_stack(ACU, Cycles);
            // 0 Cycles;
        };
    }
}