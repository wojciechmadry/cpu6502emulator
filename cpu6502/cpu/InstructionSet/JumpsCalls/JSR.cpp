#include "cpu.hpp"
namespace cpu6502 {
    [[nodiscard]] bool CPU::JSR(Byte Opcode, u32& Cycles) noexcept
    {
        using JSRop = cpu6502::opcode::JSR;
        switch(static_cast<JSRop>(Opcode))
        {
            case JSRop::Absolute: // 6 cycles
            {
                // 5 cycles
                Word SubRoutineAddress = fetch_word(Cycles);
                // 3 cycles
                push_word_to_stack(cpu_reg.PC.get() - 1 , Cycles);
                // 1 cycles
                cpu_reg.PC.set(SubRoutineAddress);
                --Cycles;
                // 0 cycles
            }
                break;
            default:
                return false;
        }
        return true;
    }
}