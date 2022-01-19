#include "indexregistery.hpp"

namespace cpu6502::registers{

    [[nodiscard]] IndexRegisterY::RegisterStroedType IndexRegisterY::get() const noexcept
    {
        return m_reg;
    }

    [[nodiscard]] IndexRegisterY::RegisterStroedType &IndexRegisterY::get() noexcept
    {
        return m_reg;
    }

    void IndexRegisterY::set(const IndexRegisterY::RegisterStroedType NewRegValue) noexcept
    {
        m_reg = NewRegValue;
    }


}
