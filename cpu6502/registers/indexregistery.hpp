#ifndef CPU_6502_registers_indexregistery
#define CPU_6502_registers_indexregistery

#include "../required.hpp"

namespace cpu6502::registers
{
    class IndexRegisterY
    {
        Byte m_reg = 0;
    public:
        using RegisterStroedType = decltype(m_reg);
        IndexRegisterY() = default;
        ~IndexRegisterY() = default;

        [[nodiscard]] RegisterStroedType get() const noexcept;

        [[nodiscard]] RegisterStroedType& get() noexcept;

        void set(RegisterStroedType NewRegValue) noexcept;
    };

}

#endif