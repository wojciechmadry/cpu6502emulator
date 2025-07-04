#include "cpu.hpp"

namespace cpu6502 {

void CPU::PHAimplied(u32 &Cycles) noexcept {
  push_byte_to_stack(cpu_reg.ACU.get(), Cycles);
}

} // namespace cpu6502
