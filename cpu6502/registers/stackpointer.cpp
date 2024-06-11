#include "stackpointer.hpp"

namespace cpu6502::registers {
[[nodiscard]] StackPointer::RegisterStroedType
StackPointer::get() const noexcept {
  return m_reg;
}

[[nodiscard]] StackPointer::RegisterStroedType &StackPointer::get() noexcept {
  return m_reg;
}

void StackPointer::set(
    const StackPointer::RegisterStroedType NewRegValue) noexcept {
  m_reg = NewRegValue;
}

void StackPointer::increment(const Byte i) noexcept {
  m_reg = static_cast<Byte>(m_reg + i);
}

void StackPointer::decrement(const Byte i) noexcept {
  m_reg = static_cast<Byte>(m_reg - i);
}

bool StackPointer::operator==(const StackPointer &other) const noexcept {
  return m_reg == other.m_reg;
}

} // namespace cpu6502::registers
