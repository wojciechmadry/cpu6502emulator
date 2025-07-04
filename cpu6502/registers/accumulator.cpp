#include "accumulator.hpp"

namespace cpu6502::registers {
[[nodiscard]] Accumulator::RegisterStoredType
Accumulator::get() const noexcept {
  return m_reg;
}

[[nodiscard]] Accumulator::RegisterStoredType &Accumulator::get() noexcept {
  return m_reg;
}

void Accumulator::set(
    const Accumulator::RegisterStoredType NewRegValue) noexcept {
  m_reg = NewRegValue;
}

bool Accumulator::operator==(const Accumulator &other) const noexcept {
  return m_reg == other.m_reg;
}

} // namespace cpu6502::registers
