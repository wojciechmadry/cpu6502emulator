#include "cpu.hpp"

namespace {
void LDA(cpu6502::Registers &reg, const cpu6502::Byte fetched) {
  reg.ACU.set(fetched);
  reg.PS.set(cpu6502::CPU::PSFlags::ZeroFlag, fetched == 0U);
  reg.PS.set(cpu6502::CPU::PSFlags::NegativeFlag,
             static_cast<bool>(fetched & 0x80));
}
} // namespace

namespace cpu6502 {

void CPU::LDAimmediate(u32 &Cycles) noexcept {
  LDA(cpu_reg, fetch<AddressingMode::Immediate>(Cycles));
}

void CPU::LDAzeropage(u32 &Cycles) noexcept {
  LDA(cpu_reg, fetch<AddressingMode::ZeroPage>(Cycles));
}

void CPU::LDAzeropagex(u32 &Cycles) noexcept {
  LDA(cpu_reg, fetch<AddressingMode::ZeroPageX>(Cycles));
}

void CPU::LDAabsolute(u32 &Cycles) noexcept {
  LDA(cpu_reg, fetch<AddressingMode::Absolute>(Cycles));
}

void CPU::LDAabsolutex(u32 &Cycles) noexcept {
  LDA(cpu_reg, fetch<AddressingMode::AbsoluteX>(Cycles));
}

void CPU::LDAabsolutey(u32 &Cycles) noexcept {
  LDA(cpu_reg, fetch<AddressingMode::AbsoluteY>(Cycles));
}

void CPU::LDAindirectx(u32 &Cycles) noexcept {
  LDA(cpu_reg, fetch<AddressingMode::IndirectX>(Cycles));
}

void CPU::LDAindirecty(u32 &Cycles) noexcept {
  LDA(cpu_reg, fetch<AddressingMode::IndirectY>(Cycles));
}

} // namespace cpu6502
