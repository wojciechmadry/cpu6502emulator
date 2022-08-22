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

        [[nodiscard]] RegisterStroedType get() const noexcept;

        [[nodiscard]] RegisterStroedType& get() noexcept;

        void set(RegisterStroedType NewRegValue) noexcept;

        bool operator==(const IndexRegisterY& other) const noexcept;

    };

}

#endif
