#include "accumulator.hpp"

namespace cpu6502::registers{
    [[nodiscard]] Accumulator::RegisterStroedType Accumulator::get() const noexcept
    {
        return _reg;
    }

    [[nodiscard]] Accumulator::RegisterStroedType &Accumulator::get() noexcept
    {
        return _reg;
    }

    void Accumulator::set(const Accumulator::RegisterStroedType NewRegValue) noexcept
    {
        _reg = NewRegValue;
    }
}
