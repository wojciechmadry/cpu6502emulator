#ifndef CPU_6502_memory
#define CPU_6502_memory

#include "required.hpp"

namespace cpu6502{
    class Memory
    {
        std::vector<Byte> m_memory;

        void throw_out_of_range(const u64 Address) const;

    public:
        Memory() = delete;

        Memory(Memory&&);

        Memory(const Memory&);

        Memory clone() const noexcept;

        explicit Memory(const u64 BYTES_MEMORY) noexcept : m_memory(BYTES_MEMORY) {}
    
        ~Memory() = default;

        Memory& operator=(Memory&&);

        Memory& operator=(const Memory&);

        void initialise() noexcept;

        [[nodiscard]] Word read_word(u64 Address) const;

        void write_word(Word Data, u64 Address);

        [[nodiscard]] Byte operator[](u64 Address) const;

        [[nodiscard]] Byte& operator[](u64 Address);

    };
}
#endif