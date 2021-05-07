#include "cpu.hpp"
namespace cpu6502 {
    void CPU::JMP() noexcept
    {
        using op = cpu6502::opcode::JMP;

        auto cast = [](op Opcode) -> Byte {
            return static_cast<Byte>(Opcode);
        };

        LookUpTable[cast(op::Absolute)] = [this](u32& Cycles) -> void
        {
            // 2 cycles
            cpu_reg.PC.set(fetch_word(Cycles));
            // 0 cycles
        };

        LookUpTable[cast(op::Indirect)] = [this](u32& Cycles) -> void
        {
            // 4 cycles
            Word Address = fetch_word(Cycles);
            // 2 cycles
            cpu_reg.PC.set(read_word(Address, Cycles));
            // 0 cycles
        };

    }
}