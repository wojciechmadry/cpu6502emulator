#include "cpu.hpp"
namespace cpu6502 {

    void CPU::JMPabsolute(u32& Cycles) noexcept
    {
        // 2 cycles
        cpu_reg.PC.set(fetch_word(Cycles));
        // 0 cycles
    }

    void CPU::JMPindirect(u32& Cycles) noexcept
    {
        // 4 cycles
        Word Address = fetch_word(Cycles);
        // 2 cycles
        cpu_reg.PC.set(read_word(Address, Cycles));
        // 0 cycles
    }

    // remove this
    /*
    void CPU::JMP() noexcept
    {
        using op = cpu6502::opcode::JMP;

        auto cast = [](op Opcode) -> Byte {
            return static_cast<Byte>(Opcode);
        };

        LookUpTable[cast(op::Absolute)] = [](u32& Cycles, CPU& cpu) -> void
        {
            // 2 cycles
            cpu.cpu_reg.PC.set(cpu.fetch_word(Cycles));
            // 0 cycles
        };

        LookUpTable[cast(op::Indirect)] = [](u32& Cycles, CPU& cpu) -> void
        {
            // 4 cycles
            Word Address = cpu.fetch_word(Cycles);
            // 2 cycles
            cpu.cpu_reg.PC.set(cpu.read_word(Address, Cycles));
            // 0 cycles
        };

    }*/
}