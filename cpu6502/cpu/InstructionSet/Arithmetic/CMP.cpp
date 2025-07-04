#include "cpu.hpp"

namespace {
void cmp_operation(cpu6502::CPU &cpu, const cpu6502::Byte fetched) noexcept {
  auto &reg = cpu.get_registers();
  const auto acu = reg.ACU.get();
  const auto result = static_cast<cpu6502::Byte>(acu - fetched);

  reg.PS.set(cpu6502::CPU::PSFlags::CarryFlag, acu >= fetched);
  reg.PS.set(cpu6502::CPU::PSFlags::ZeroFlag, acu == fetched);
  reg.PS.set(cpu6502::CPU::PSFlags::NegativeFlag,
             static_cast<bool>(result & 0x80));
}
} // namespace

namespace cpu6502 {

void CPU::CMPimmediate(u32 &Cycles) noexcept {
  cmp_operation(*this, fetch<AddressingMode::Immediate>(Cycles));
}

void CPU::CMPzeropage(u32 &Cycles) noexcept {
  cmp_operation(*this, fetch<AddressingMode::ZeroPage>(Cycles));
}

void CPU::CMPzeropagex(u32 &Cycles) noexcept {
  cmp_operation(*this, fetch<AddressingMode::ZeroPageX>(Cycles));
}

void CPU::CMPabsolute(u32 &Cycles) noexcept {
  cmp_operation(*this, fetch<AddressingMode::Absolute>(Cycles));
}

void CPU::CMPabsolutex(u32 &Cycles) noexcept {
  cmp_operation(*this, fetch<AddressingMode::AbsoluteX>(Cycles));
}

void CPU::CMPabsolutey(u32 &Cycles) noexcept {
  cmp_operation(*this, fetch<AddressingMode::AbsoluteY>(Cycles));
}

void CPU::CMPindirectx(u32 &Cycles) noexcept {
  cmp_operation(*this, fetch<AddressingMode::IndirectX>(Cycles));
}

void CPU::CMPindirecty(u32 &Cycles) noexcept {
  cmp_operation(*this, fetch<AddressingMode::IndirectY>(Cycles));
}

} // namespace cpu6502
