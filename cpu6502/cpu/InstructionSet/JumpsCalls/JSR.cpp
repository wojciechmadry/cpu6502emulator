#include "cpu.hpp"
namespace cpu6502 {

    void CPU::JSRabsolute(u32& Cycles) noexcept
    {
        // 5 cycles
        Word SubRoutineAddress = fetch_word(Cycles);
        // 3 cycles
        push_word_to_stack(cpu_reg.PC.get() - 1 , Cycles);
        // 1 cycles
        cpu_reg.PC.set(SubRoutineAddress);
        --Cycles;
        // 0 cycles
    }

    // remove this
    /*
    void CPU::JSR() noexcept
    {
        using op = cpu6502::opcode::JSR;

        auto cast = [](op Opcode) -> Byte {
            return static_cast<Byte>(Opcode);
        };

        LookUpTable[cast(op::Absolute)] = [](u32& Cycles, CPU& cpu) -> void
        {
            // 5 cycles
            Word SubRoutineAddress = cpu.fetch_word(Cycles);
            // 3 cycles
            cpu.push_word_to_stack(cpu.cpu_reg.PC.get() - 1 , Cycles);
            // 1 cycles
            cpu.cpu_reg.PC.set(SubRoutineAddress);
            --Cycles;
            // 0 cycles
        };
    }*/
}