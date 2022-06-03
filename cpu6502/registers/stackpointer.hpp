#ifndef CPU_6502_registers_stackpointer
#define CPU_6502_registers_stackpointer

#include "../required.hpp"

namespace cpu6502::registers
{
    class StackPointer
    {
        Byte m_reg = 0;
    public:
        using RegisterStroedType = decltype(m_reg);
        StackPointer() = default;
        ~StackPointer() = default;

        [[nodiscard]] RegisterStroedType get() const noexcept;

        [[nodiscard]] RegisterStroedType& get() noexcept;

        void set(RegisterStroedType NewRegValue) noexcept;

        void increment(Byte i = 1) noexcept;

        void decrement(Byte i = 1) noexcept;
    };
}

#endif