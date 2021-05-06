#ifndef CPU_6502_registers_stackpointer
#define CPU_6502_registers_stackpointer

#include "../required.hpp"

namespace cpu6502::registers
{
    class StackPointer
    {
        Byte _reg = 0;
        using RegisterStroedType = decltype(_reg);
    public:
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