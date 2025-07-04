#ifndef CPU_6502_registers_programcounter
#define CPU_6502_registers_programcounter

#include "../required.hpp"

namespace cpu6502::registers {
class ProgramCounter {
  Word m_reg = 0;

public:
  using RegisterStoredType = decltype(m_reg);

  [[nodiscard]] RegisterStoredType get() const noexcept;

  [[nodiscard]] RegisterStoredType &get() noexcept;

  void set(RegisterStoredType NewRegValue) noexcept;

  void increment() noexcept;

  void decrement() noexcept;

  Word getAndIncrement() noexcept;

  bool operator==(const ProgramCounter &other) const noexcept;
};
} // namespace cpu6502::registers
#endif
