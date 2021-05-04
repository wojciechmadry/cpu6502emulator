#include "cpu.hpp"
namespace cpu6502 {
    [[nodiscard]] bool CPU::JMP(Byte Opcode, u32& Cycles) noexcept
    {
        using JMPop = cpu6502::opcode::JMP;
        switch(static_cast<JMPop>(Opcode))
        {
            case JMPop::Absolute:
            {
                cpu_reg.PC.set(fetch_word(Cycles));
            }
                break;
            case JMPop::Indirect:
            {
                Word Address = fetch_word(Cycles);
                cpu_reg.PC.set(read_word(Address, Cycles));
            }
            break;
            default:
                return false;
        }
        return true;
    }
}