#include "cpu.hpp"

namespace cpu6502{

    void CPU::RTIimplied(u32& Cycles) noexcept
    {
        // 5 cycles
        const auto ps = pop_byte_from_stack(Cycles); // 2 cycle
        // 3 cycles
        const auto pc = pop_word_from_stack(Cycles); // 3 cycle
        // 0 cycles
        cpu_reg.PS.put_byte(ps);
        cpu_reg.PC.set(pc);
    }
   
}