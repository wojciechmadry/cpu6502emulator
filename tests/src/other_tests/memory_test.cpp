#include "cpu.hpp"
#include "cpu_test.hpp"

#include <type_traits>

namespace CPU6502_TEST::inner {

bool MEMORY_TEST() {
  bool all_good = true;
  constexpr std::size_t CAPACITY = 64;
  cpu6502::Memory mem(CAPACITY);

  auto each = [&]<typename LAMBDA>(LAMBDA lambda) {
    for (std::size_t i = 0u; i < CAPACITY; ++i) {
      lambda(mem[i]);
    }
  };

  all_good &= std::is_same_v<cpu6502::Byte, std::decay_t<decltype(mem[0])>>;

  each([&](auto val) { all_good &= val == 0; });

  mem.initialise();

  each([&](auto val) { all_good &= val == 0xFF; });

  // Read/Write byte
  for (std::size_t i = 0u; i < 64; ++i) {
    mem[i] = static_cast<cpu6502::Byte>(i);
  }
  for (std::size_t i = 0u; i < 64; ++i) {
    all_good &= mem[i] == static_cast<cpu6502::Byte>(i);
  }

  // Read/Write word
  constexpr cpu6502::Word word_value = 0x1234;
  for (std::size_t i = 0u; i < 64; i += 2) {
    mem.write_word(word_value, i);
  }
  for (std::size_t i = 0u; i < 64; i += 2) {
    all_good &= mem.read_word(i) == word_value;
  }

  mem[0] = 0;
  mem[1] = 0;

  mem.write_word(word_value, 0);
  all_good &= mem.read_word(0) == word_value;
  all_good &= mem[0] == static_cast<cpu6502::Byte>(word_value & 0xFF);
  all_good &= mem[1] == static_cast<cpu6502::Byte>((word_value >> 8) & 0xFF);

  return all_good;
}

} // namespace CPU6502_TEST::inner
