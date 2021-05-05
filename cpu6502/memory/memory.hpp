#ifndef CPU_6502_memory
#define CPU_6502_memory

#include "required.hpp"

namespace cpu6502{
    class Memory
    {
        std::vector<Byte> data;
    public:
        Memory() = delete;
        explicit Memory(u64 MAX_MEM) noexcept : data(MAX_MEM) {}
        ~Memory() = default;

        void initialise() noexcept;

        [[nodiscard]] Word read_word(u64 Address) const noexcept;

        void write_word(Word Data, u64 Address) noexcept;

        [[nodiscard]] Byte operator[](u64 Address) const noexcept;

        [[nodiscard]] Byte& operator[](u64 Address) noexcept;

    };
}
#endif