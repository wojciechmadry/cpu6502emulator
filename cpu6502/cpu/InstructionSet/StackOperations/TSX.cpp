#include "cpu.hpp"

namespace cpu6502 {

void CPU::TSXimplied(u32 &Cycles) noexcept {
  // 1 Cycles
  cpu_reg.IRX.set(cpu_reg.SP.get());
  --Cycles;
  // 0 Cycles
  cpu_reg.PS.set(PSFlags::ZeroFlag, !static_cast<bool>(cpu_reg.IRX.get()));
  cpu_reg.PS.set(PSFlags::NegativeFlag, cpu_reg.IRX.get() & 0x80);
}

} // namespace cpu6502
