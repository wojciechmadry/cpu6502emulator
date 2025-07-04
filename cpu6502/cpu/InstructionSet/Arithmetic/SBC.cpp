#include "cpu.hpp"
#include <limits>

namespace cpu6502 {
void CPU::SBCimmediate(u32 &Cycles) noexcept {
  ADC(static_cast<Byte>(~fetch<AddressingMode::Immediate>(Cycles)));
}

void CPU::SBCzeropage(u32 &Cycles) noexcept {
  ADC(static_cast<Byte>(~fetch<AddressingMode::ZeroPage>(Cycles)));
}

void CPU::SBCzeropagex(u32 &Cycles) noexcept {
  ADC(static_cast<Byte>(~fetch<AddressingMode::ZeroPageX>(Cycles)));
}

void CPU::SBCabsolute(u32 &Cycles) noexcept {
  ADC(static_cast<Byte>(~fetch<AddressingMode::Absolute>(Cycles)));
}

void CPU::SBCabsolutex(u32 &Cycles) noexcept {
  ADC(static_cast<Byte>(~fetch<AddressingMode::AbsoluteX>(Cycles)));
}

void CPU::SBCabsolutey(u32 &Cycles) noexcept {
  ADC(static_cast<Byte>(~fetch<AddressingMode::AbsoluteY>(Cycles)));
}

void CPU::SBCindirectx(u32 &Cycles) noexcept {
  ADC(static_cast<Byte>(~fetch<AddressingMode::IndirectX>(Cycles)));
}

void CPU::SBCindirecty(u32 &Cycles) noexcept {
  ADC(static_cast<Byte>(~fetch<AddressingMode::IndirectY>(Cycles)));
}

} // namespace cpu6502
