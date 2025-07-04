#include "cpu.hpp"

namespace cpu6502 {

void CPU::RTIimplied(u32 &Cycles) noexcept {
  // 5 cycles
  cpu_reg.PS.put_byte(pop_byte_from_stack(Cycles)); // 2 cycle
  cpu_reg.PC.set(pop_word_from_stack(Cycles));      // 3 cycle
  // 0 cycles
}

} // namespace cpu6502
