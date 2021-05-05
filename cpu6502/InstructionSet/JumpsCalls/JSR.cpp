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
                write_word(cpu_reg.PC.get() - 1, cpu_reg.SP.get(), Cycles);
                cpu_reg.SP.increment(2);
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