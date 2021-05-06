#include "cpu.hpp"

namespace cpu6502 {
    [[nodiscard]] bool CPU::LDX(Byte Opcode, u32 &Cycles) noexcept
    {
        using LDXop = cpu6502::opcode::LDX;
        switch (static_cast<LDXop>(Opcode)) {
            case LDXop::Immediate:
            {

            }break;
            case LDXop::ZeroPage:
            {

            }break;
            case LDXop::ZeroPageY:
            {

            }break;
            case LDXop::Absolute:
            {

            }break;
            case LDXop::AbsoluteY:
            {

            }break;
            default:
                return false;
        }

        return true;
    }
}