#include "indexregisterx.hpp"


namespace cpu6502::registers{

    [[nodiscard]] IndexRegisterX::RegisterStroedType IndexRegisterX::get() const noexcept
    {
        return m_reg;
    }

    [[nodiscard]] IndexRegisterX::RegisterStroedType &IndexRegisterX::get() noexcept
    {
        return m_reg;
    }

    void IndexRegisterX::set(const IndexRegisterX::RegisterStroedType NewRegValue) noexcept
    {
        m_reg = NewRegValue;
    }


}