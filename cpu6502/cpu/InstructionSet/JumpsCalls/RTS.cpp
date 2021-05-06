#include "cpu.hpp"
namespace cpu6502{
    void CPU::RTS() noexcept
    {
        using op = cpu6502::opcode::RTS;

        auto cast = [](op Opcode) -> Byte {
            return static_cast<Byte>(Opcode);
        };

        LookUpTable[cast(op::Implied)] = [this](u32& Cycles) -> void
        {
            // 5 cycles
            Word PC = fetch_word_from_stack(Cycles);
            cpu_reg.PC.set(PC + 1);
            Cycles -= 3;
        };
    }
}