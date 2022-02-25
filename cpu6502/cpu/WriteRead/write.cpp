#include "cpu.hpp"
#include "exceptions/cpu_except.hpp"

namespace cpu6502{
    void CPU::write_word(const Word Data, u32 Address, u32& Cycles) noexcept
    {
        mem.get().write_word(Data, Address);
        Cycles -= 2;
    }

    void CPU::write_byte(const Byte Data, u32 Address, u32& Cycles) noexcept
    {
        mem.get()[Address] = Data;
        --Cycles;
    }
    void CPU::push_word_to_stack(const Word Data, u32& Cycles)
    {
        if (cpu_reg.SP.get() <= 1)
        {
            throw std::out_of_range("Cant push word to stack (stack full).");
        }
        write_word(Data, static_cast<u32>(cpu_reg.SP.get()) + STACK_BEGIN, Cycles);
        cpu_reg.SP.decrement(2);
    }

    void CPU::push_byte_to_stack(const Byte Data, u32& Cycles)
    {
        if (cpu_reg.SP.get() == 0)
        {
            throw std::out_of_range("Cant push byte to stack (stack full).");
        }
        write_byte(Data, static_cast<u32>(cpu_reg.SP.get()) + STACK_BEGIN, Cycles);
        cpu_reg.SP.decrement();
        --Cycles;
    }
}