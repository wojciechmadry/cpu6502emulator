#include "cpu.hpp"

namespace {
void EOR(cpu6502::Registers &reg, const cpu6502::Byte fetched) {
  reg.ACU.set(fetched ^ reg.ACU.get());
  // 0 Cycles

  // Flag set
  reg.PS.set(cpu6502::CPU::PSFlags::ZeroFlag, reg.ACU.get() == 0U);
  reg.PS.set(cpu6502::CPU::PSFlags::NegativeFlag,
             static_cast<bool>(reg.ACU.get() & 0x80));
}
} // namespace

namespace cpu6502 {

void CPU::EORimmediate(u32 &Cycles) noexcept {
  EOR(cpu_reg, fetch<AddressingMode::Immediate>(Cycles));
}

void CPU::EORzeropage(u32 &Cycles) noexcept {
  EOR(cpu_reg, fetch<AddressingMode::ZeroPage>(Cycles));
}

void CPU::EORzeropagex(u32 &Cycles) noexcept {
  EOR(cpu_reg, fetch<AddressingMode::ZeroPageX>(Cycles));
}

void CPU::EORabsolute(u32 &Cycles) noexcept {
  EOR(cpu_reg, fetch<AddressingMode::Absolute>(Cycles));
}

void CPU::EORabsolutex(u32 &Cycles) noexcept {
  EOR(cpu_reg, fetch<AddressingMode::AbsoluteX>(Cycles));
}

void CPU::EORabsolutey(u32 &Cycles) noexcept {
  EOR(cpu_reg, fetch<AddressingMode::AbsoluteY>(Cycles));
}
void CPU::EORindirectx(u32 &Cycles) noexcept {
  EOR(cpu_reg, fetch<AddressingMode::IndirectX>(Cycles));
}

void CPU::EORindirecty(u32 &Cycles) noexcept {
  EOR(cpu_reg, fetch<AddressingMode::IndirectY>(Cycles));
}

} // namespace cpu6502
