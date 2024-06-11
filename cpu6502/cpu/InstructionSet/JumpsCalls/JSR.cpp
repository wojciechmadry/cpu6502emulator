#include "cpu.hpp"
namespace cpu6502 {

void CPU::JSRabsolute(u32 &Cycles) noexcept {
  // 5 cycles
  const Word SubRoutineAddress = fetch_word(Cycles);
  // 3 cycles
  push_word_to_stack(cpu_reg.PC.get() - 1, Cycles);
  // 1 cycles
  cpu_reg.PC.set(SubRoutineAddress);
  --Cycles;
  // 0 cycles
}

} // namespace cpu6502
