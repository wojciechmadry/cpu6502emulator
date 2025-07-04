#include "cpu.hpp"

namespace cpu6502 {

void CPU::TAXimplied(u32 &Cycles) noexcept {
  // 1 Cycles
  cpu_reg.IRX.set(cpu_reg.ACU.get());
  --Cycles;
  // 0 cycles
  cpu_reg.PS.set(PSFlags::ZeroFlag, cpu_reg.IRX.get() == 0U);
  cpu_reg.PS.set(PSFlags::NegativeFlag,
                 static_cast<bool>(cpu_reg.IRX.get() & 0x80));
}

} // namespace cpu6502
