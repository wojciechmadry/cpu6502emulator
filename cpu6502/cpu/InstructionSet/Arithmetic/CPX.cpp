#include "cpu.hpp"

namespace {

void cpx_operation(cpu6502::CPU &cpu, const cpu6502::Byte fetched) noexcept {
  auto &reg = cpu.get_registers();
  const auto x_reg = reg.IRX.get();
  const auto result = static_cast<cpu6502::Byte>(x_reg - fetched);

  reg.PS.set(cpu6502::CPU::PSFlags::CarryFlag, x_reg >= fetched);
  reg.PS.set(cpu6502::CPU::PSFlags::ZeroFlag, x_reg == fetched);
  reg.PS.set(cpu6502::CPU::PSFlags::NegativeFlag,
             static_cast<bool>(result & 0x80));
}
} // namespace

namespace cpu6502 {

void CPU::CPXimmediate(u32 &Cycles) noexcept {
  cpx_operation(*this, fetch<AddressingMode::Immediate>(Cycles));
}

void CPU::CPXzeropage(u32 &Cycles) noexcept {
  cpx_operation(*this, fetch<AddressingMode::ZeroPage>(Cycles));
}

void CPU::CPXabsolute(u32 &Cycles) noexcept {
  cpx_operation(*this, fetch<AddressingMode::Absolute>(Cycles));
}

} // namespace cpu6502
