#include "cpu.hpp"

namespace cpu6502{

    void CPU::PHAimplied(u32& Cycles) noexcept
    {
       // 2 Cycles
        const Byte ACU = cpu_reg.ACU.get();
        push_byte_to_stack(ACU, Cycles);
        // 0 Cycles; 
    }
   
}