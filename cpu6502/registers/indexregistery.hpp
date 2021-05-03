#ifndef CPU_6502_registers_indexregistery
#define CPU_6502_registers_indexregistery

#include "required.hpp"

namespace cpu6502::registers
{
    class IndexRegisterY
    {
        Byte _reg = 0;
        using RegisterStroedType = decltype(_reg);
    public:
        IndexRegisterY() = default;
        ~IndexRegisterY() = default;

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