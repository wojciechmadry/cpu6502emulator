#include "cpu.hpp"

namespace cpu6502{
    void CPU::CPY() noexcept
    {
        using op = cpu6502::opcode::CPY;

        auto cast = [](op Opcode) -> Byte {
            return static_cast<Byte>(Opcode);
        };

        LookUpTable[cast(op::Immediate)] = [](u32& Cycles, CPU& cpu) -> void
        {
            (void) Cycles;
            (void) cpu;
        };

        LookUpTable[cast(op::ZeroPage)] = [](u32& Cycles, CPU& cpu) -> void
        {
            (void) Cycles;
            (void) cpu;
        };

        LookUpTable[cast(op::Absolute)] = [](u32& Cycles, CPU& cpu) -> void
        {
            (void) Cycles;
            (void) cpu;
        };
    }
}