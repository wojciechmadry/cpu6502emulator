#include "cpu.hpp"

namespace {
void AND(cpu6502::Registers &reg, const cpu6502::Byte fetched) {
  reg.ACU.set(fetched & reg.ACU.get());
  reg.PS.set(cpu6502::CPU::PSFlags::ZeroFlag, reg.ACU.get() == 0U);
  reg.PS.set(cpu6502::CPU::PSFlags::NegativeFlag,
             static_cast<bool>(reg.ACU.get() & 0x80));
}
} // namespace

namespace cpu6502 {

void CPU::ANDimmediate(u32 &Cycles) noexcept {
  AND(cpu_reg, fetch<AddressingMode::Immediate>(Cycles));
}

void CPU::ANDzeropage(u32 &Cycles) noexcept {
  AND(cpu_reg, fetch<AddressingMode::ZeroPage>(Cycles));
}

void CPU::ANDzeropagex(u32 &Cycles) noexcept {
  AND(cpu_reg, fetch<AddressingMode::ZeroPageX>(Cycles));
}

void CPU::ANDabsolute(u32 &Cycles) noexcept {
  AND(cpu_reg, fetch<AddressingMode::Absolute>(Cycles));
}

void CPU::ANDabsolutex(u32 &Cycles) noexcept {
  AND(cpu_reg, fetch<AddressingMode::AbsoluteX>(Cycles));
}

void CPU::ANDabsolutey(u32 &Cycles) noexcept {
  AND(cpu_reg, fetch<AddressingMode::AbsoluteY>(Cycles));
}

void CPU::ANDindirectx(u32 &Cycles) noexcept {
  AND(cpu_reg, fetch<AddressingMode::IndirectX>(Cycles));
}

void CPU::ANDindirecty(u32 &Cycles) noexcept {
  AND(cpu_reg, fetch<AddressingMode::IndirectY>(Cycles));
}

} // namespace cpu6502
