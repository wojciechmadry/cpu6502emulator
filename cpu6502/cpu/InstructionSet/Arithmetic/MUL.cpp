#include "cpu.hpp"

#include <limits>
#include <type_traits>

namespace cpu6502 {

void CPU::MUL(const Byte value) noexcept {
  auto &reg = cpu_reg;
  const auto ACU = reg.ACU.get();
  const auto word_data = static_cast<SByte>(value) * static_cast<SByte>(ACU);
  reg.ACU.set(static_cast<Byte>(word_data));

  reg.PS.set(CPU::PSFlags::ZeroFlag, reg.ACU.get() == 0);
  reg.PS.set(CPU::PSFlags::NegativeFlag, reg.ACU.get() & 0x80);

  const bool is_overflow = word_data < std::numeric_limits<SByte>::min() ||
                           word_data > std::numeric_limits<SByte>::max();
  reg.PS.set(CPU::PSFlags::OverflowFlag, is_overflow);
}

void CPU::MULimmediate(u32 &Cycles) noexcept {
  MUL(fetch<AddressingMode::Immediate>(Cycles));
}

void CPU::MULzeropage(u32 &Cycles) noexcept {
  MUL(fetch<AddressingMode::ZeroPage>(Cycles));
}

void CPU::MULzeropagex(u32 &Cycles) noexcept {
  MUL(fetch<AddressingMode::ZeroPageX>(Cycles));
}

void CPU::MULabsolute(u32 &Cycles) noexcept {
  MUL(fetch<AddressingMode::Absolute>(Cycles));
}

void CPU::MULabsolutex(u32 &Cycles) noexcept {
  MUL(fetch<AddressingMode::AbsoluteX>(Cycles));
}

void CPU::MULabsolutey(u32 &Cycles) noexcept {
  MUL(fetch<AddressingMode::AbsoluteY>(Cycles));
}

void CPU::MULindirectx(u32 &Cycles) noexcept {
  MUL(fetch<AddressingMode::IndirectX>(Cycles));
}

void CPU::MULindirecty(u32 &Cycles) noexcept {
  MUL(fetch<AddressingMode::IndirectY>(Cycles));
}
} // namespace cpu6502
