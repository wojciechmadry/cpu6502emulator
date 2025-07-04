#include "cpu.hpp"

namespace {
void LDY(cpu6502::Registers &reg, const cpu6502::Byte fetched) {
  reg.IRY.set(fetched);
  reg.PS.set(cpu6502::CPU::PSFlags::ZeroFlag, fetched == 0U);
  reg.PS.set(cpu6502::CPU::PSFlags::NegativeFlag,
             static_cast<bool>(fetched & 0x80));
}
} // namespace

namespace cpu6502 {

void CPU::LDYimmediate(u32 &Cycles) noexcept {
  LDY(cpu_reg, fetch<AddressingMode::Immediate>(Cycles));
}

void CPU::LDYzeropage(u32 &Cycles) noexcept {
  LDY(cpu_reg, fetch<AddressingMode::ZeroPage>(Cycles));
}

void CPU::LDYzeropagex(u32 &Cycles) noexcept {
  LDY(cpu_reg, fetch<AddressingMode::ZeroPageX>(Cycles));
}

void CPU::LDYabsolute(u32 &Cycles) noexcept {
  LDY(cpu_reg, fetch<AddressingMode::Absolute>(Cycles));
}

void CPU::LDYabsolutex(u32 &Cycles) noexcept {
  LDY(cpu_reg, fetch<AddressingMode::AbsoluteX>(Cycles));
}

} // namespace cpu6502
