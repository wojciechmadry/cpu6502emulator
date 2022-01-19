#include "stackpointer.hpp"

namespace cpu6502::registers{
    [[nodiscard]] StackPointer::RegisterStroedType StackPointer::get() const noexcept
    {
        return m_reg;
    }

    [[nodiscard]] StackPointer::RegisterStroedType &StackPointer::get() noexcept
    {
        return m_reg;
    }

    void StackPointer::set(const StackPointer::RegisterStroedType NewRegValue) noexcept
    {
        m_reg = NewRegValue;
    }

    void StackPointer::increment(const Byte i) noexcept
    {
        m_reg += i;
    }

    void StackPointer::decrement(const Byte i) noexcept
    {
        m_reg -= i;
    }
}