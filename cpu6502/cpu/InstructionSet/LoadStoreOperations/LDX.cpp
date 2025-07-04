#include "cpu.hpp"

namespace {
void LDX(cpu6502::Registers &reg, const cpu6502::Byte fetched) {
  reg.IRX.set(fetched);
  reg.PS.set(cpu6502::CPU::PSFlags::ZeroFlag, fetched == 0U);
  reg.PS.set(cpu6502::CPU::PSFlags::NegativeFlag,
             static_cast<bool>(fetched & 0x80));
}
} // namespace

namespace cpu6502 {

void CPU::LDXimmediate(u32 &Cycles) noexcept {
  LDX(cpu_reg, fetch<AddressingMode::Immediate>(Cycles));
}

void CPU::LDXzeropage(u32 &Cycles) noexcept {
  LDX(cpu_reg, fetch<AddressingMode::ZeroPage>(Cycles));
}

void CPU::LDXzeropagey(u32 &Cycles) noexcept {
  LDX(cpu_reg, fetch<AddressingMode::ZeroPageY>(Cycles));
}

void CPU::LDXabsolute(u32 &Cycles) noexcept {
  LDX(cpu_reg, fetch<AddressingMode::Absolute>(Cycles));
}

void CPU::LDXabsolutey(u32 &Cycles) noexcept {
  LDX(cpu_reg, fetch<AddressingMode::AbsoluteY>(Cycles));
}

} // namespace cpu6502
