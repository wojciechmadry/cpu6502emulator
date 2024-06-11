#include "cpu.hpp"

namespace cpu6502 {

void CPU::PHPimplied(u32 &Cycles) noexcept {
  // 2 Cycles
  const Byte StatusFlag = cpu_reg.PS.pull_byte();
  push_byte_to_stack(StatusFlag, Cycles);
  // 0 Cycles
}

} // namespace cpu6502
