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

    [[nodiscard]] Word CPU::pop_word_from_stack(u32& Cycles) noexcept
    {
        assert(cpu_reg.SP.get() < 254);
        Word Data = read_word(cpu_reg.SP.get() + 2,Cycles);
        cpu_reg.SP.increment(2);
        --Cycles;
        return Data;
    }

    [[nodiscard]] Byte CPU::pop_byte_from_stack(u32& Cycles) noexcept
    {
        assert(cpu_reg.SP.get() != 255);
        Byte Data = read_byte(cpu_reg.SP.get() + 1,Cycles);
        cpu_reg.SP.increment();
        --Cycles;
        return Data;
    }
}