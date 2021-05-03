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

        [[nodiscard]] Byte operator[](const u64 Index) const noexcept
        {
            assert(Index < data.size());
            return data[Index];
        }

        [[nodiscard]] Byte& operator[](const u64 Index) noexcept
        {
            assert(Index < data.size());
            return data[Index];
        }
    };
}
#endif