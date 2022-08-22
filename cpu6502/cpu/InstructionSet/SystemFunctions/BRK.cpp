#include "cpu.hpp"

namespace cpu6502{

    void CPU::BRKimplied(u32& Cycles) noexcept
    {
        // 6 cycles
        const auto pc = cpu_reg.PC.get();
        const auto ps = cpu_reg.PS.pull_byte();
        push_word_to_stack(pc, Cycles);
        // 4 cycles
        push_byte_to_stack(ps, Cycles);
        // 2 cycles
        const auto interrupt_vector = read_word(IRQ, Cycles);
        // 0 cycles
        cpu_reg.PC.set(interrupt_vector);
        cpu_reg.PS.set(PSFlags::BreakCommand, true);
    }
   
}
