#include "cpu.hpp"

namespace cpu6502 {

void CPU::LDAimmediate(u32 &Cycles) noexcept {
  const auto fetched = fetch<AddressingMode::Immediate>(Cycles);
  // 1 cycles
  cpu_reg.ACU.set(fetched);
  // 0 cycles
  cpu_reg.PS.set(PSFlags::ZeroFlag, !static_cast<bool>(fetched));
  cpu_reg.PS.set(PSFlags::NegativeFlag, fetched & 0x80);
}

void CPU::LDAzeropage(u32 &Cycles) noexcept {
  const auto fetched = fetch<AddressingMode::ZeroPage>(Cycles);
  cpu_reg.ACU.set(fetched);
  // 0 cycles
  cpu_reg.PS.set(PSFlags::ZeroFlag, !static_cast<bool>(fetched));
  cpu_reg.PS.set(PSFlags::NegativeFlag, fetched & 0x80);
}

void CPU::LDAzeropagex(u32 &Cycles) noexcept {
  const auto fetched = fetch<AddressingMode::ZeroPageX>(Cycles);
  cpu_reg.ACU.set(fetched);
  // 0 cycles
  cpu_reg.PS.set(PSFlags::ZeroFlag, !static_cast<bool>(fetched));
  cpu_reg.PS.set(PSFlags::NegativeFlag, fetched & 0x80);
}

void CPU::LDAabsolute(u32 &Cycles) noexcept {
  const auto fetched = fetch<AddressingMode::Absolute>(Cycles);
  cpu_reg.ACU.set(fetched);
  // 0 cycles
  cpu_reg.PS.set(PSFlags::ZeroFlag, !static_cast<bool>(fetched));
  cpu_reg.PS.set(PSFlags::NegativeFlag, fetched & 0x80);
}

void CPU::LDAabsolutex(u32 &Cycles) noexcept {
  const auto fetched = fetch<AddressingMode::AbsoluteX>(Cycles);
  cpu_reg.ACU.set(fetched);
  // 0 cycles
  cpu_reg.PS.set(PSFlags::ZeroFlag, !static_cast<bool>(fetched));
  cpu_reg.PS.set(PSFlags::NegativeFlag, fetched & 0x80);
}

void CPU::LDAabsolutey(u32 &Cycles) noexcept {
  const auto fetched = fetch<AddressingMode::AbsoluteY>(Cycles);

  cpu_reg.ACU.set(fetched);
  // 0 cycles
  cpu_reg.PS.set(PSFlags::ZeroFlag, !static_cast<bool>(fetched));
  cpu_reg.PS.set(PSFlags::NegativeFlag, fetched & 0x80);
}

void CPU::LDAindirectx(u32 &Cycles) noexcept {
  const auto fetched = fetch<AddressingMode::IndirectX>(Cycles);
  cpu_reg.ACU.set(fetched);
  // 0 cycles

  cpu_reg.PS.set(PSFlags::ZeroFlag, !static_cast<bool>(fetched));
  cpu_reg.PS.set(PSFlags::NegativeFlag, fetched & 0x80);
}

void CPU::LDAindirecty(u32 &Cycles) noexcept {
  const auto fetched = fetch<AddressingMode::IndirectY>(Cycles);
  cpu_reg.ACU.set(fetched);
  // 0 cycles

  cpu_reg.PS.set(PSFlags::ZeroFlag, !static_cast<bool>(fetched));
  cpu_reg.PS.set(PSFlags::NegativeFlag, fetched & 0x80);
}

} // namespace cpu6502
