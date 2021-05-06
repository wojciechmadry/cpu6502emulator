#include "programcounter.hpp"


namespace cpu6502::registers{
    [[nodiscard]] ProgramCounter::RegisterStroedType ProgramCounter::get() const noexcept
    {
        return _reg;
    }

    [[nodiscard]] ProgramCounter::RegisterStroedType &ProgramCounter::get() noexcept
    {
        return _reg;
    }

    void ProgramCounter::set(const ProgramCounter::RegisterStroedType NewRegValue) noexcept
    {
        _reg = NewRegValue;
    }

    void ProgramCounter::increment() noexcept
    {
        ++_reg;
    }

}