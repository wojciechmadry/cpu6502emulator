#include "cpu.hpp"
namespace cpu6502{

    void CPU::RTSimplied(u32& Cycles) noexcept
    {
        // 5 cycles
        const Word PC = pop_word_from_stack(Cycles);
        // 2 cycles
        cpu_reg.PC.set(PC + 1);
        Cycles -= 2; // ?????????
        // 0 cycles
    }
    
}