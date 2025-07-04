#include "cpu.hpp"

namespace cpu6502 {

void CPU::PLAimplied(u32 &Cycles) noexcept {
  // 3 cycles
  cpu_reg.ACU.set(pop_byte_from_stack(Cycles));
  --Cycles;
  // 0 Cycles
  cpu_reg.PS.set(PSFlags::ZeroFlag, cpu_reg.ACU.get() == 0U);
  cpu_reg.PS.set(PSFlags::NegativeFlag,
                 static_cast<bool>(cpu_reg.ACU.get() & 0x80));
}

} // namespace cpu6502
