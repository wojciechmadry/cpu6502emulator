#include "cpu.hpp"
#include "exceptions/cpu_except.hpp"

namespace cpu6502 {

Byte CPU::fetch_byte(u32 &Cycles) noexcept {
  const Byte Data = mem.get()[cpu_reg.PC.get()];
  cpu_reg.PC.increment();
  --Cycles;
  return Data;
}

Byte CPU::read_byte(const u32 Address, u32 &Cycles) const noexcept {
  --Cycles;
  return mem.get()[Address];
}

Word CPU::fetch_word(u32 &Cycles) noexcept {
  // little endian
  auto Data = static_cast<Word>(fetch_byte(Cycles));
  Data = static_cast<Word>(Data | (fetch_byte(Cycles) << 8));
  return Data;
}

Word CPU::read_word(const u32 Address, u32 &Cycles) noexcept {
  // little endian
  Cycles -= 2;
  return mem.get().read_word(Address);
}

Word CPU::pop_word_from_stack(u32 &Cycles) {
  if (cpu_reg.SP.get() >= 254) {
    throw std::out_of_range("Cant pop word from stack. (stack empty).");
  }
  const Word Data =
      read_word(static_cast<u32>(cpu_reg.SP.get()) + 2 + STACK_BEGIN, Cycles);
  cpu_reg.SP.increment(2);
  --Cycles;
  return Data;
}

Byte CPU::pop_byte_from_stack(u32 &Cycles) {
  if (cpu_reg.SP.get() == 255) {
    throw std::out_of_range("Cant pop byte from stack. (stack empty).");
  }
  const Byte Data =
      read_byte(static_cast<u32>(cpu_reg.SP.get()) + 1 + STACK_BEGIN, Cycles);
  cpu_reg.SP.increment();
  --Cycles;
  return Data;
}
} // namespace cpu6502
