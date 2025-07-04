#include "cpu.hpp"

namespace cpu6502 {

void CPU::BRKimplied(u32 &Cycles) noexcept {
  // 6 cycles
  push_word_to_stack(cpu_reg.PC.get(), Cycles);
  // 4 cycles
  push_byte_to_stack(cpu_reg.PS.pull_byte(), Cycles);
  // 2 cycles
  cpu_reg.PC.set(read_word(IRQ, Cycles));
  cpu_reg.PS.set(PSFlags::BreakCommand, true);
  // 0 cycles
}

} // namespace cpu6502
