#include "cpu.hpp"

namespace cpu6502 {

void CPU::DEXimplied(u32 &Cycles) noexcept {
  const auto x_reg = cpu_reg.IRX.get();
  const auto decrement = static_cast<Byte>(x_reg - 1);
  cpu_reg.IRX.set(decrement);
  --Cycles;
  // 0 cycles

  cpu_reg.PS.set(PSFlags::ZeroFlag, decrement == 0);
  cpu_reg.PS.set(PSFlags::NegativeFlag, static_cast<bool>(decrement & 0x80));
}

} // namespace cpu6502
