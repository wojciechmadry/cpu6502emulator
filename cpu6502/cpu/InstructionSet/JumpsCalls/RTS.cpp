#include "cpu.hpp"
namespace cpu6502{
    void CPU::RTS() noexcept
    {
        using op = cpu6502::opcode::RTS;

        auto cast = [](op Opcode) -> Byte {
            return static_cast<Byte>(Opcode);
        };

        LookUpTable[cast(op::Implied)] = [](u32& Cycles, CPU& cpu) -> void
        {
            // 5 cycles
            Word PC = cpu.pop_word_from_stack(Cycles);
            // 2 cycles
            cpu.cpu_reg.PC.set(PC + 1);
            Cycles -= 2; // ?????????
            // 0 cycles
        };
    }
}