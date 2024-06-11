#include "cpu.hpp"

namespace cpu6502 {

void CPU::INCzeropage(u32 &Cycles) noexcept {
  // 4 cycles;
  const auto ZeroPageAddress = fetch_byte(Cycles);
  // 3 cycles
  const auto fetched = read_byte(ZeroPageAddress, Cycles);
  const auto increment = static_cast<Byte>(fetched + 1);
  --Cycles;
  // 1 cycles
  write_byte(increment, ZeroPageAddress, Cycles);
  // 0 cycles

  cpu_reg.PS.set(PSFlags::ZeroFlag, increment == 0);
  cpu_reg.PS.set(PSFlags::NegativeFlag, static_cast<bool>(increment & 0x80));
}

void CPU::INCzeropagex(u32 &Cycles) noexcept {
  // 5 cycles
  auto ZeroPageAddress = fetch_byte(Cycles);
  // 4 cycles
  ZeroPageAddress += cpu_reg.IRX.get();
  --Cycles;
  // 3 cycles
  const auto fetched = read_byte(ZeroPageAddress, Cycles);
  const auto increment = static_cast<Byte>(fetched + 1);
  --Cycles;
  // 1 cycles
  write_byte(increment, ZeroPageAddress, Cycles);
  // 0 cycles

  cpu_reg.PS.set(PSFlags::ZeroFlag, increment == 0);
  cpu_reg.PS.set(PSFlags::NegativeFlag, static_cast<bool>(increment & 0x80));
}

void CPU::INCabsolute(u32 &Cycles) noexcept {
  // 5 cycles
  const Word address = fetch_word(Cycles);
  // 3 cycles
  const auto fetched = read_byte(address, Cycles);
  // 2 cycles
  const auto increment = static_cast<Byte>(fetched + 1);
  --Cycles;
  // 1 cycles
  write_byte(increment, address, Cycles);

  cpu_reg.PS.set(PSFlags::ZeroFlag, increment == 0);
  cpu_reg.PS.set(PSFlags::NegativeFlag, static_cast<bool>(increment & 0x80));
}

void CPU::INCabsolutex(u32 &Cycles) noexcept {
  // 6 cycles
  Word address = fetch_word(Cycles);
  // 4 cycles
  address += cpu_reg.IRX.get();
  --Cycles;
  // 3 cycles
  const auto fetched = read_byte(address, Cycles);
  // 2 cycles
  const auto increment = static_cast<Byte>(fetched + 1);
  --Cycles;
  // 1 cycles
  write_byte(increment, address, Cycles);
  // 0 cycles

  cpu_reg.PS.set(PSFlags::ZeroFlag, increment == 0);
  cpu_reg.PS.set(PSFlags::NegativeFlag, static_cast<bool>(increment & 0x80));
}

} // namespace cpu6502
