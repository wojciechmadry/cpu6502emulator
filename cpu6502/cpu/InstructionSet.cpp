#include "cpu.hpp"

namespace cpu6502
{
    void CPU::make_instruction_set() noexcept
    {
#define CPU_MAKE_FUNC(_FUNCTION_)  [&](const Byte Opcode, u32& Cycles) -> bool { return _FUNCTION_(Opcode, Cycles); }

        InstructionSetArray[0] = CPU_MAKE_FUNC(CPU::LDA);
        InstructionSetArray[1] = CPU_MAKE_FUNC(CPU::JSR);
        InstructionSetArray[2] = CPU_MAKE_FUNC(CPU::JMP);
        InstructionSetArray[3] = CPU_MAKE_FUNC(CPU::RTS);

#undef CPU_MAKE_FUNC
    }
}