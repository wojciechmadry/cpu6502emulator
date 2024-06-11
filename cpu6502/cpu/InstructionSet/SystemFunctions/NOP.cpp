#include "cpu.hpp"

namespace cpu6502 {

void CPU::NOPimplied(u32 &Cycles) noexcept { --Cycles; }

} // namespace cpu6502
