#include "cpu.hpp"
namespace cpu6502{
    [[nodiscard]] bool CPU::RTS(Byte Opcode, u32 &Cycles) noexcept
    {
        using RTSop = cpu6502::opcode::RTS;
        switch(static_cast<RTSop>(Opcode))
        {
            case RTSop::Implied:
            {
            }
                break;
            default:
                return false;
        }
        return true;
    }
}