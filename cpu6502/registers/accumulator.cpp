#include "accumulator.hpp"

namespace cpu6502::registers {
[[nodiscard]] Accumulator::RegisterStroedType
Accumulator::get() const noexcept {
  return m_reg;
}

[[nodiscard]] Accumulator::RegisterStroedType &Accumulator::get() noexcept {
  return m_reg;
}

void Accumulator::set(
    const Accumulator::RegisterStroedType NewRegValue) noexcept {
  m_reg = NewRegValue;
}

bool Accumulator::operator==(const Accumulator &other) const noexcept {
  return m_reg == other.m_reg;
}

} // namespace cpu6502::registers
