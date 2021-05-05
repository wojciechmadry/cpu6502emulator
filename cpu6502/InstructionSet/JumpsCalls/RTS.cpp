#include "cpu.hpp"
namespace cpu6502{
    [[nodiscard]] bool CPU::RTS(Byte Opcode, u32 &Cycles) noexcept
    {
        using RTSop = cpu6502::opcode::RTS;
        switch(static_cast<RTSop>(Opcode))
        {
            case RTSop::Implied: // 6 cycles
            {
                // 5 cycles
                Word PC = read_word(cpu_reg.SP.get() - 2,Cycles);
                cpu_reg.SP.decrement(2);
                cpu_reg.PC.set(PC + 1);
                Cycles -= 3;

            }
                break;
            default:
                return false;
        }
        return true;
    }
}