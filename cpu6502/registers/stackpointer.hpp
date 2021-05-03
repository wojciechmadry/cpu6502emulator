#ifndef CPU_6502_registers_stackpointer
#define CPU_6502_registers_stackpointer

#include "required.hpp"

namespace cpu6502::registers
{
    class StackPointer
    {
        Byte _reg = 0;
        using RegisterStroedType = decltype(_reg);
    public:
        StackPointer() = default;
        ~StackPointer() = default;

        [[nodiscard]] RegisterStroedType get() const noexcept
        {
            return _reg;
        }

        [[nodiscard]] RegisterStroedType& get() noexcept
        {
            return _reg;
        }

        void set(const RegisterStroedType NewRegValue) noexcept
        {
            _reg = NewRegValue;
        }

        void increment() noexcept
        {
            ++_reg;
        }
    };
}

#endif