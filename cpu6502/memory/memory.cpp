#include "memory.hpp"

namespace cpu6502{

    void Memory::initialise() noexcept {
        for (auto &MemoryChain : data)
            MemoryChain = 0;
    }


    [[nodiscard]] Word Memory::read_word(const u64 Address) const noexcept
    {
        Word Data = data[Address];
        Data = static_cast<Word>(Data | (data[Address + 1] << 8));
        return Data;
    }

    void Memory::write_word(const Word Data, const u64 Address) noexcept
    {
        data[Address] = static_cast<Byte>(Data & 0x00FF);
        data[Address+1] = static_cast<Byte>(Data >> 8);
    }

    [[nodiscard]] Byte Memory::operator[](const u64 Address) const noexcept
    {
        assert(Address < data.size());
        return data[Address];
    }

    [[nodiscard]] Byte& Memory::operator[](const u64 Address) noexcept
    {
        assert(Address < data.size());
        return data[Address];
    }
}