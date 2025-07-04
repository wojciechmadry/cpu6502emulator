#include "cpu.hpp"

namespace cpu6502 {

void CPU::PHPimplied(u32 &Cycles) noexcept {
  // 2 Cycles
  push_byte_to_stack(cpu_reg.PS.pull_byte(), Cycles);
  // 0 Cycles
}

} // namespace cpu6502
