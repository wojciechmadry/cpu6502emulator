#ifndef CPU_6502_registers_accumulator
#define CPU_6502_registers_accumulator

#include "required.hpp"
namespace cpu6502::registers
{
    class Accumulator
    {
        Byte _reg = 0;
        using RegisterStroedType = decltype(_reg);
    public:
        Accumulator() = default;
        ~Accumulator() = default;

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
    };
}

#endif