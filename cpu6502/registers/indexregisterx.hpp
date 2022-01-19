#ifndef CPU_6502_registers_indexregisterx
#define CPU_6502_registers_indexregisterx

#include "../required.hpp"

namespace cpu6502::registers
{
    class IndexRegisterX
    {
        Byte m_reg = 0;
        using RegisterStroedType = decltype(m_reg);
    public:
        IndexRegisterX() = default;
        ~IndexRegisterX() = default;

        [[nodiscard]] RegisterStroedType get() const noexcept;

        [[nodiscard]] RegisterStroedType& get() noexcept;

        void set(RegisterStroedType NewRegValue) noexcept;
    };

}

#endif