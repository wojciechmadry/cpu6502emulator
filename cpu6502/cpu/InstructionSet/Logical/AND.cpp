#include "cpu.hpp"

namespace cpu6502 {

void CPU::ANDimmediate(u32 &Cycles) noexcept {
  const auto fetched = fetch<AddressingMode::Immediate>(Cycles);
  cpu_reg.ACU.set(fetched & cpu_reg.ACU.get());
  // 0 Cycles

  cpu_reg.PS.set(PSFlags::ZeroFlag, !static_cast<bool>(cpu_reg.ACU.get()));
  cpu_reg.PS.set(PSFlags::NegativeFlag, cpu_reg.ACU.get() & 0x80);
}

void CPU::ANDzeropage(u32 &Cycles) noexcept {
  const auto fetched = fetch<AddressingMode::ZeroPage>(Cycles);
  cpu_reg.ACU.set(cpu_reg.ACU.get() & fetched);
  // 0 cycles

  cpu_reg.PS.set(PSFlags::ZeroFlag, !static_cast<bool>(cpu_reg.ACU.get()));
  cpu_reg.PS.set(PSFlags::NegativeFlag, cpu_reg.ACU.get() & 0x80);
}

void CPU::ANDzeropagex(u32 &Cycles) noexcept {
  const auto fetched = fetch<AddressingMode::ZeroPageX>(Cycles);
  cpu_reg.ACU.set(cpu_reg.ACU.get() & fetched);
  // 0 cycles

  // Flag set
  cpu_reg.PS.set(PSFlags::ZeroFlag, !static_cast<bool>(cpu_reg.ACU.get()));
  cpu_reg.PS.set(PSFlags::NegativeFlag, cpu_reg.ACU.get() & 0x80);
}

void CPU::ANDabsolute(u32 &Cycles) noexcept {
  const auto fetched = fetch<AddressingMode::Absolute>(Cycles);
  cpu_reg.ACU.set(cpu_reg.ACU.get() & fetched);
  // 0 Cycles

  // Flag set
  cpu_reg.PS.set(PSFlags::ZeroFlag, !static_cast<bool>(cpu_reg.ACU.get()));
  cpu_reg.PS.set(PSFlags::NegativeFlag, cpu_reg.ACU.get() & 0x80);
}

void CPU::ANDabsolutex(u32 &Cycles) noexcept {
  const auto fetched = fetch<AddressingMode::AbsoluteX>(Cycles);
  cpu_reg.ACU.set(cpu_reg.ACU.get() & fetched);
  // 0 cycles

  // Flag set
  cpu_reg.PS.set(PSFlags::ZeroFlag, !static_cast<bool>(cpu_reg.ACU.get()));
  cpu_reg.PS.set(PSFlags::NegativeFlag, cpu_reg.ACU.get() & 0x80);
}

void CPU::ANDabsolutey(u32 &Cycles) noexcept {
  const auto fetched = fetch<AddressingMode::AbsoluteY>(Cycles);
  cpu_reg.ACU.set(cpu_reg.ACU.get() & fetched);
  // 0 cycles

  // Flag set
  cpu_reg.PS.set(PSFlags::ZeroFlag, !static_cast<bool>(cpu_reg.ACU.get()));
  cpu_reg.PS.set(PSFlags::NegativeFlag, cpu_reg.ACU.get() & 0x80);
}

void CPU::ANDindirectx(u32 &Cycles) noexcept {
  const auto fetched = fetch<AddressingMode::IndirectX>(Cycles);
  cpu_reg.ACU.set(cpu_reg.ACU.get() & fetched);
  // 0 cycles

  // Flag set
  cpu_reg.PS.set(PSFlags::ZeroFlag, !static_cast<bool>(cpu_reg.ACU.get()));
  cpu_reg.PS.set(PSFlags::NegativeFlag, cpu_reg.ACU.get() & 0x80);
}

void CPU::ANDindirecty(u32 &Cycles) noexcept {
  const auto fetched = fetch<AddressingMode::IndirectY>(Cycles);
  cpu_reg.ACU.set(cpu_reg.ACU.get() & fetched);
  // 0 cycles

  // Flag set
  cpu_reg.PS.set(PSFlags::ZeroFlag, !static_cast<bool>(cpu_reg.ACU.get()));
  cpu_reg.PS.set(PSFlags::NegativeFlag, cpu_reg.ACU.get() & 0x80);
}

} // namespace cpu6502
