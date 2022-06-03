#include "programcounter.hpp"


namespace cpu6502::registers{
    [[nodiscard]] ProgramCounter::RegisterStroedType ProgramCounter::get() const noexcept
    {
        return m_reg;
    }

    [[nodiscard]] ProgramCounter::RegisterStroedType &ProgramCounter::get() noexcept
    {
        return m_reg;
    }

    void ProgramCounter::set(const ProgramCounter::RegisterStroedType NewRegValue) noexcept
    {
        m_reg = NewRegValue;
    }

    void ProgramCounter::increment() noexcept
    {
        ++m_reg;
    }
    void ProgramCounter::decrement() noexcept
    {
        --m_reg;
    }


}