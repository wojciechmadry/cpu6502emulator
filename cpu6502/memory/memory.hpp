#ifndef CPU_6502_memory
#define CPU_6502_memory

#include "required.hpp"
#include <type_traits>

namespace cpu6502{
    class Memory
    {
        std::vector<Byte> m_memory;

        void throw_out_of_range(const u64 Address) const;

    public:
        Memory() = delete;

        Memory(Memory&&) noexcept;

        Memory(const Memory&);

        Memory clone() const noexcept;

		template<typename INTEGER>
		requires(std::is_integral_v<INTEGER>)
        explicit Memory(const INTEGER BYTES_MEMORY) noexcept : m_memory(static_cast<u64>(BYTES_MEMORY)) {}
    
        ~Memory() = default;

        Memory& operator=(Memory&&) noexcept;

        Memory& operator=(const Memory&);

        bool operator==(const Memory& other) const noexcept;

        void initialise() noexcept;

        [[nodiscard]] Word read_word(u64 Address) const;

        void write_word(Word Data, u64 Address);

        [[nodiscard]] Byte operator[](u64 Address) const;

        [[nodiscard]] Byte& operator[](u64 Address);

    };
}
#endif
