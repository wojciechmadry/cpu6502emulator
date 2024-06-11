#include "registers.hpp"
#include "accumulator.hpp"
#include "indexregistery.hpp"
#include "processorstatus.hpp"
#include "programcounter.hpp"
#include "stackpointer.hpp"

namespace cpu6502 {

bool Registers::operator==(const Registers &other) const noexcept {
  return this->ACU == other.ACU && this->IRX == other.IRX &&
         this->IRY == other.IRY && this->PC == other.PC &&
         this->SP == other.SP && this->PS == other.PS;
}

void Registers::setRegister(RegistersName regName,
                            std::uint32_t value) noexcept {
  switch (regName) {
  case cpu6502::RegistersName::ProcessorStatusBreakCommand: {
    PS.set(registers::ProcessorStatus::Flags::BreakCommand,
           static_cast<bool>(value));
    break;
  }
  case cpu6502::RegistersName::Accumulator: {
    ACU.set(static_cast<registers::Accumulator::RegisterStroedType>(value));
    break;
  }
  case cpu6502::RegistersName::IndexRegisterX: {
    IRX.set(static_cast<registers::IndexRegisterX::RegisterStroedType>(value));
    break;
  }
  case cpu6502::RegistersName::IndexRegisterY: {
    IRY.set(static_cast<registers::IndexRegisterY::RegisterStroedType>(value));
    break;
  }
  case cpu6502::RegistersName::ProcessorStatusCarryFlag: {
    PS.set(registers::ProcessorStatus::Flags::CarryFlag,
           static_cast<bool>(value));
    break;
  }
  case cpu6502::RegistersName::ProcessorStatusDecimalMode: {
    PS.set(registers::ProcessorStatus::Flags::DecimalMode,
           static_cast<bool>(value));
    break;
  }
  case cpu6502::RegistersName::ProcessorStatusInterruptDisable: {
    PS.set(registers::ProcessorStatus::Flags::InterruptDisable,
           static_cast<bool>(value));
    break;
  }
  case cpu6502::RegistersName::ProcessorStatusNegativeFlag: {
    PS.set(registers::ProcessorStatus::Flags::NegativeFlag,
           static_cast<bool>(value));
    break;
  }
  case cpu6502::RegistersName::ProcessorStatusOverflowFlag: {
    PS.set(registers::ProcessorStatus::Flags::OverflowFlag,
           static_cast<bool>(value));
    break;
  }
  case cpu6502::RegistersName::ProcessorStatusZeroFlag: {
    PS.set(registers::ProcessorStatus::Flags::ZeroFlag,
           static_cast<bool>(value));
    break;
  }
  case cpu6502::RegistersName::ProgramCounter: {
    PC.set(static_cast<registers::ProgramCounter::RegisterStroedType>(value));
    break;
  }
  case cpu6502::RegistersName::StackPointer: {
    SP.set(static_cast<registers::StackPointer::RegisterStroedType>(value));
    break;
  }
  }
}

} // namespace cpu6502
