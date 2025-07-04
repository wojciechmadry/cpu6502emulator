#include "cpu.hpp"

#include <limits>

namespace cpu6502 {

void CPU::ADC(const Byte value) noexcept {
  // Overflow flag -> if ACU is treat as signed
  // Carry flag -> if ACU is treat as unsigned
  auto &reg = cpu_reg;
  const auto ACU = reg.ACU.get();
  const auto carry_flag = reg.PS.get(CPU::PSFlags::CarryFlag);
  const auto word_data = static_cast<Word>(value + ACU + carry_flag);
  reg.ACU.set(static_cast<Byte>(word_data));
  // 0 cycles

  reg.PS.set(CPU::PSFlags::ZeroFlag, reg.ACU.get() == 0);
  reg.PS.set(CPU::PSFlags::NegativeFlag, reg.ACU.get() & 0x80);

  const bool is_overflow =
      (!(ACU & 0x80) && !(value & 0x80) && word_data & 0x80) ||
      ((ACU & 0x80) && (value & 0x80) && !(word_data & 0x80));

  reg.PS.set(CPU::PSFlags::OverflowFlag, is_overflow);
  reg.PS.set(CPU::PSFlags::CarryFlag,
             word_data > std::numeric_limits<Byte>::max());
}

void CPU::ADCimmediate(u32 &Cycles) noexcept {
  ADC(fetch<AddressingMode::Immediate>(Cycles));
}

void CPU::ADCzeropage(u32 &Cycles) noexcept {
  ADC(fetch<AddressingMode::ZeroPage>(Cycles));
}

void CPU::ADCzeropagex(u32 &Cycles) noexcept {
  ADC(fetch<AddressingMode::ZeroPageX>(Cycles));
}

void CPU::ADCabsolute(u32 &Cycles) noexcept {
  ADC(fetch<AddressingMode::Absolute>(Cycles));
}

void CPU::ADCabsolutex(u32 &Cycles) noexcept {
  ADC(fetch<AddressingMode::AbsoluteX>(Cycles));
}

void CPU::ADCabsolutey(u32 &Cycles) noexcept {
  ADC(fetch<AddressingMode::AbsoluteY>(Cycles));
}

void CPU::ADCindirectx(u32 &Cycles) noexcept {
  ADC(fetch<AddressingMode::IndirectX>(Cycles));
}

void CPU::ADCindirecty(u32 &Cycles) noexcept {
  ADC(fetch<AddressingMode::IndirectY>(Cycles));
}
} // namespace cpu6502
