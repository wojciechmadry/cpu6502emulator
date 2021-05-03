#include "cpu.hpp"
namespace cpu6502 {
    [[nodiscard]] bool CPU::JMP(Byte Opcode, u32& Cycles) noexcept
    {
        using JMPop = cpu6502::opcode::JMP;
        switch(static_cast<JMPop>(Opcode))
        {
            case JMPop::Absolute:
            {

            }
                break;
            case JMPop::Indirect:
            {

            }
            break;
            default:
                return false;
        }
        return true;
    }
}