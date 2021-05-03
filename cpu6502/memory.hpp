#ifndef CPU_6502_memory
#define CPU_6502_memory

#include "required.hpp"

namespace cpu6502{
    class Memory
    {
        std::vector<Byte> data;
    public:
        Memory() = delete;
        explicit Memory(u64 MAX_MEM) noexcept : data(MAX_MEM)
        {}
        ~Memory() = default;

        void initialise() noexcept {
            for (auto &MemoryChain : data)
                MemoryChain = 0;
        }

        [[nodiscard]] Word read_word(const u64 Address) const noexcept
        {
            Word Data = data[Address];
            Data = static_cast<Word>(Data | (data[Address + 1] << 8));
            return Data;
        }
        void write_word(const Word Data, const u64 Address) noexcept
        {
            data[Address] = static_cast<Byte>(Data & 0x00FF);
            data[Address+1] = static_cast<Byte>(Data >> 8);
        }

        [[nodiscard]] Byte operator[](const u64 Address) const noexcept
        {
            assert(Address < data.size());
            return data[Address];
        }

        [[nodiscard]] Byte& operator[](const u64 Address) noexcept
        {
            assert(Address < data.size());
            return data[Address];
        }
    };
}
#endif