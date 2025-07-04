#include "cpu.hpp"

namespace {
void cpy_operation(cpu6502::CPU &cpu, const cpu6502::Byte fetched) noexcept {
  auto &reg = cpu.get_registers();
  const auto y_reg = reg.IRY.get();
  const auto result = static_cast<cpu6502::Byte>(y_reg - fetched);

  reg.PS.set(cpu6502::CPU::PSFlags::CarryFlag, y_reg >= fetched);
  reg.PS.set(cpu6502::CPU::PSFlags::ZeroFlag, y_reg == fetched);
  reg.PS.set(cpu6502::CPU::PSFlags::NegativeFlag,
             static_cast<bool>(result & 0x80));
}
} // namespace

namespace cpu6502 {

void CPU::CPYimmediate(u32 &Cycles) noexcept {
  cpy_operation(*this, fetch<AddressingMode::Immediate>(Cycles));
}

void CPU::CPYzeropage(u32 &Cycles) noexcept {
  cpy_operation(*this, fetch<AddressingMode::ZeroPage>(Cycles));
}

void CPU::CPYabsolute(u32 &Cycles) noexcept {
  cpy_operation(*this, fetch<AddressingMode::Absolute>(Cycles));
}

} // namespace cpu6502
