#include "indexregistery.hpp"

namespace cpu6502::registers{

    [[nodiscard]] IndexRegisterY::RegisterStroedType IndexRegisterY::get() const noexcept
    {
        return _reg;
    }

    [[nodiscard]] IndexRegisterY::RegisterStroedType &IndexRegisterY::get() noexcept
    {
        return _reg;
    }

    void IndexRegisterY::set(const IndexRegisterY::RegisterStroedType NewRegValue) noexcept
    {
        _reg = NewRegValue;
    }


}
