#include "indexregisterx.hpp"


namespace cpu6502::registers{

    [[nodiscard]] IndexRegisterX::RegisterStroedType IndexRegisterX::get() const noexcept
    {
        return _reg;
    }

    [[nodiscard]] IndexRegisterX::RegisterStroedType &IndexRegisterX::get() noexcept
    {
        return _reg;
    }

    void IndexRegisterX::set(const IndexRegisterX::RegisterStroedType NewRegValue) noexcept
    {
        _reg = NewRegValue;
    }


}