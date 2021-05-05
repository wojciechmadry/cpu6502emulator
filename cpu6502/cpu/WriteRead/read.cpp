#include "cpu.hpp"

namespace cpu6502{

    [[nodiscard]] Byte CPU::fetch_byte(u32 &Cycles) noexcept
    {
        Byte Data = mem.get()[cpu_reg.PC.get()];
        cpu_reg.PC.increment();
        --Cycles;
        return Data;
    }

    [[nodiscard]] Byte CPU::read_byte(const u32 Address, u32 &Cycles) const noexcept
    {
        --Cycles;
        return mem.get()[Address];
    }

    [[nodiscard]] Word CPU::fetch_word(u32 &Cycles) noexcept
    {
        //little endian
        auto Data = static_cast<Word>(fetch_byte(Cycles));
        Data = static_cast<Word>(Data | ( fetch_byte(Cycles) << 8 ));
        return Data;
    }

    [[nodiscard]] Word CPU::read_word(const u32 Address, u32 &Cycles) noexcept
    {
        //little endian
        Cycles -= 2;
        return mem.get().read_word(Address);
    }

    [[nodiscard]] Word CPU::fetch_word_from_stack(u32& Cycles) noexcept
    {
        Word Data = read_word(cpu_reg.SP.get() - 2,Cycles);
        cpu_reg.SP.decrement(2);
        return Data;
    }

    [[nodiscard]] Byte CPU::fetch_byte_from_stack(u32& Cycles) noexcept
    {
        Byte Data = read_byte(cpu_reg.SP.get() - 1,Cycles);
        cpu_reg.SP.decrement();
        return Data;
    }
}