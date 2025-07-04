#include "cpu.hpp"

namespace cpu6502 {

void CPU::PLPimplied(u32 &Cycles) noexcept {
  // 3 Cycles;
  cpu_reg.PS.put_byte(pop_byte_from_stack(Cycles));
  --Cycles;
  // 0 Cycles
}

} // namespace cpu6502
