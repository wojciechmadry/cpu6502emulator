#ifndef CPU_6502_registers_indexregisterx
#define CPU_6502_registers_indexregisterx

#include "../required.hpp"

namespace cpu6502::registers
{
    class IndexRegisterX
    {
        Byte m_reg = 0;
    public:
        using RegisterStroedType = decltype(m_reg);

        [[nodiscard]] RegisterStroedType get() const noexcept;

        [[nodiscard]] RegisterStroedType& get() noexcept;

        void set(RegisterStroedType NewRegValue) noexcept;

        bool operator==(const IndexRegisterX& other) const noexcept;
    };

}

#endif
