#include "cpu.hpp"

namespace cpu6502{

    void CPU::PHAimplied(u32& Cycles) noexcept
    {
        const Byte ACU = cpu_reg.ACU.get();
        push_byte_to_stack(ACU, Cycles);
    }
   
}
