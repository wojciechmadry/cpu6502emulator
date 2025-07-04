#include "cpu.hpp"
#include "exceptions/cpu_except.hpp"

namespace cpu6502 {

Byte CPU::fetch_byte(u32 &Cycles) noexcept {
  --Cycles;
  return mem.get()[cpu_reg.PC.getAndIncrement()];
}

Byte CPU::read_byte(const u32 Address, u32 &Cycles) const noexcept {
  --Cycles;
  return mem.get()[Address];
}

Word CPU::fetch_word(u32 &Cycles) noexcept {
  // little endian
  const auto lsb = static_cast<Word>(fetch_byte(Cycles));
  return static_cast<Word>(lsb | (fetch_byte(Cycles) << 8));
}

Word CPU::read_word(const u32 Address, u32 &Cycles) noexcept {
  // little endian
  Cycles -= 2;
  return mem.get().read_word(Address);
}

Word CPU::pop_word_from_stack(u32 &Cycles) {
  if (cpu_reg.SP.get() > STACK_SIZE - sizeof(Word)) {
    throw std::out_of_range("Cant pop word from stack. (stack empty).");
  }
  cpu_reg.SP.increment(sizeof(Word));
  --Cycles;
  return read_word(static_cast<u32>(cpu_reg.SP.get()) + STACK_BEGIN, Cycles);
}

Byte CPU::pop_byte_from_stack(u32 &Cycles) {
  if (cpu_reg.SP.get() == STACK_SIZE) {
    throw std::out_of_range("Cant pop byte from stack. (stack empty).");
  }
  cpu_reg.SP.increment();
  --Cycles;
  return read_byte(static_cast<u32>(cpu_reg.SP.get()) + STACK_BEGIN, Cycles);
}
} // namespace cpu6502
