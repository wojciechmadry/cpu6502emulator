#ifndef CPU_6502_registers_stackpointer
#define CPU_6502_registers_stackpointer

#include "../required.hpp"

namespace cpu6502::registers {
class StackPointer {
  Byte m_reg = 0;

public:
  using RegisterStoredType = decltype(m_reg);

  [[nodiscard]] RegisterStoredType get() const noexcept;

  [[nodiscard]] RegisterStoredType &get() noexcept;

  void set(RegisterStoredType NewRegValue) noexcept;

  void increment(Byte i = 1) noexcept;

  void decrement(Byte i = 1) noexcept;

  bool operator==(const StackPointer &other) const noexcept;
};
} // namespace cpu6502::registers

#endif
