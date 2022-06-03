#ifndef CPU_6502_registers_accumulator
#define CPU_6502_registers_accumulator

#include "../required.hpp"

namespace cpu6502::registers
{
    class Accumulator
    {
        Byte m_reg = 0;
    public:
        using RegisterStroedType = decltype(m_reg);
        Accumulator() = default;
        ~Accumulator() = default;

        [[nodiscard]] RegisterStroedType get() const noexcept;

        [[nodiscard]] RegisterStroedType& get() noexcept;

        void set(RegisterStroedType NewRegValue) noexcept;
    };
}

#endif