#include "stackpointer.hpp"

namespace cpu6502::registers{
    [[nodiscard]] StackPointer::RegisterStroedType StackPointer::get() const noexcept
    {
        return _reg;
    }

    [[nodiscard]] StackPointer::RegisterStroedType &StackPointer::get() noexcept
    {
        return _reg;
    }

    void StackPointer::set(const StackPointer::RegisterStroedType NewRegValue) noexcept
    {
        _reg = NewRegValue;
    }

    void StackPointer::increment(const Byte i) noexcept
    {
        _reg += i;
    }

    void StackPointer::decrement(const Byte i) noexcept
    {
        _reg -= i;
    }
}