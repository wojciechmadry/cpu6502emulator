#ifndef CPU_6502_registers_indexregisterx
#define CPU_6502_registers_indexregisterx

#include "required.hpp"

namespace cpu6502::registers
{
    class IndexRegisterX
    {
        Byte _reg = 0;
        using RegisterStroedType = decltype(_reg);
    public:
        IndexRegisterX() = default;
        ~IndexRegisterX() = default;

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