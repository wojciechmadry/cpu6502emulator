#include "cpu.hpp"
namespace cpu6502 {
    [[nodiscard]] bool CPU::JSR(Byte Opcode, u32& Cycles) noexcept
    {
        using JSRop = cpu6502::opcode::JSR;
        switch(static_cast<JSRop>(Opcode))
        {
            case JSRop::Absolute:
            {
                Word SubRoutineAddress = fetch_word(Cycles);
                write_word(cpu_reg.PC.get() - 1, cpu_reg.SP.get(), Cycles);
                cpu_reg.SP.increment();
                cpu_reg.PC.set(SubRoutineAddress);
                --Cycles;
            }
                break;
            default:
                return false;
        }
        return true;
    }
}