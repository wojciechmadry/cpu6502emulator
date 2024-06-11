#include "indexregistery.hpp"

namespace cpu6502::registers {

bool IndexRegisterY::operator==(const IndexRegisterY &other) const noexcept {
  return m_reg == other.m_reg;
}

[[nodiscard]] IndexRegisterY::RegisterStroedType
IndexRegisterY::get() const noexcept {
  return m_reg;
}

[[nodiscard]] IndexRegisterY::RegisterStroedType &
IndexRegisterY::get() noexcept {
  return m_reg;
}

void IndexRegisterY::set(
    const IndexRegisterY::RegisterStroedType NewRegValue) noexcept {
  m_reg = NewRegValue;
}

} // namespace cpu6502::registers
