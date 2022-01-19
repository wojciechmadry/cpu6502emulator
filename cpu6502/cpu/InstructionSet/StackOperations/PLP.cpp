#include "cpu.hpp"

namespace cpu6502{

    void CPU::PLPimplied(u32& Cycles) noexcept
    {
        // 3 Cycles;
        Byte ProcessorStatus = pop_byte_from_stack(Cycles);
        // 1 Cycles;
        cpu_reg.PS.put_byte(ProcessorStatus);
        --Cycles;
        // 0 Cycles
    }
 
}