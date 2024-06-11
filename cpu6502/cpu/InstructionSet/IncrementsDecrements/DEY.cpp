#include "cpu.hpp"

namespace cpu6502 {

void CPU::DEYimplied(u32 &Cycles) noexcept {
  const auto y_reg = cpu_reg.IRY.get();
  const auto decrement = static_cast<Byte>(y_reg - 1);
  cpu_reg.IRY.set(decrement);
  --Cycles;
  // 0 cycles

  cpu_reg.PS.set(PSFlags::ZeroFlag, decrement == 0);
  cpu_reg.PS.set(PSFlags::NegativeFlag, static_cast<bool>(decrement & 0x80));
}

} // namespace cpu6502
