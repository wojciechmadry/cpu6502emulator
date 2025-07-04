#ifndef CPU_6502_registers_indexregisterx
#define CPU_6502_registers_indexregisterx

#include "../required.hpp"

namespace cpu6502::registers {
class IndexRegisterX {
  Byte m_reg = 0;

public:
  using RegisterStoredType = decltype(m_reg);

  [[nodiscard]] RegisterStoredType get() const noexcept;

  [[nodiscard]] RegisterStoredType &get() noexcept;

  void set(RegisterStoredType NewRegValue) noexcept;

  bool operator==(const IndexRegisterX &other) const noexcept;
};

} // namespace cpu6502::registers

#endif
