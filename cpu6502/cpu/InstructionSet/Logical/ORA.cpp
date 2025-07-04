#include "cpu.hpp"

namespace {
void ORA(cpu6502::Registers &reg, const cpu6502::Byte fetched) {
  reg.ACU.set(fetched | reg.ACU.get());
  // 0 Cycles

  // Flag set
  reg.PS.set(cpu6502::CPU::PSFlags::ZeroFlag, reg.ACU.get() == 0U);
  reg.PS.set(cpu6502::CPU::PSFlags::NegativeFlag,
             static_cast<bool>(reg.ACU.get() & 0x80));
}
} // namespace

namespace cpu6502 {

void CPU::ORAimmediate(u32 &Cycles) noexcept {
  ORA(cpu_reg, fetch<AddressingMode::Immediate>(Cycles));
}

void CPU::ORAzeropage(u32 &Cycles) noexcept {
  ORA(cpu_reg, fetch<AddressingMode::ZeroPage>(Cycles));
}

void CPU::ORAzeropagex(u32 &Cycles) noexcept {
  ORA(cpu_reg, fetch<AddressingMode::ZeroPageX>(Cycles));
}

void CPU::ORAabsolute(u32 &Cycles) noexcept {
  ORA(cpu_reg, fetch<AddressingMode::Absolute>(Cycles));
}

void CPU::ORAabsolutex(u32 &Cycles) noexcept {
  ORA(cpu_reg, fetch<AddressingMode::AbsoluteX>(Cycles));
}

void CPU::ORAabsolutey(u32 &Cycles) noexcept {
  ORA(cpu_reg, fetch<AddressingMode::AbsoluteY>(Cycles));
}

void CPU::ORAindirectx(u32 &Cycles) noexcept {
  ORA(cpu_reg, fetch<AddressingMode::IndirectX>(Cycles));
}

void CPU::ORAindirecty(u32 &Cycles) noexcept {
  ORA(cpu_reg, fetch<AddressingMode::IndirectY>(Cycles));
}

} // namespace cpu6502
