#include "instruction_test.hpp"

#include "cpu.hpp"
#include "cpu/InstructionSet/opcode.hpp"
#include "utility/test_utils.hpp"

namespace CPU6502_TEST::inner {
bool CPX_TEST() {
  bool all_good = true;
  using PSFlags = cpu6502::registers::ProcessorStatus::Flags;

  cpu6502::Memory mem(64 * 1024);
  cpu6502::CPU cpu(mem);
  cpu6502::Byte opcode;

  utils::jump_to_2020(cpu);
  cpu6502::registers::ProgramCounter::RegisterStroedType PC;

  // ASSERT CPX - Immediate
  opcode = static_cast<decltype(opcode)>(
      cpu6502::opcode::CPX::Immediate); // 2 cycles

  for (std::int16_t i = -25; i <= 25; ++i) {
    for (std::int16_t j = -25; j <= 25; ++j) {
      // i -> acu
      // j -> memory
      const auto carry_flag =
          static_cast<cpu6502::Byte>(i) >= static_cast<cpu6502::Byte>(j);
      const auto zero_flag = i == j;
      const auto result = static_cast<cpu6502::Byte>(i - j);
      const auto negative_flag = static_cast<bool>(result & 0x80);
      // Load i to X register
      utils::load_to_xreg(cpu, static_cast<cpu6502::Byte>(i));
      PC = cpu.get_registers().PC.get();
      // Compare ACU with J (memory)
      mem[PC++] = opcode;
      mem[PC++] = static_cast<cpu6502::Byte>(j);
      cpu.execute(2);

      // Check Negative flag
      all_good &=
          cpu.get_registers().PS.get(PSFlags::NegativeFlag) == negative_flag;

      // Check Carry Flag
      all_good &= cpu.get_registers().PS.get(PSFlags::CarryFlag) == carry_flag;

      // Check Zero Flag
      all_good &= cpu.get_registers().PS.get(PSFlags::ZeroFlag) == zero_flag;

      utils::jump_to_2020(cpu);
    }
  }
  // END ASSERT CPX - Immediate

  utils::jump_to_2020(cpu);

  // ASSERT CPX - Zero Page
  opcode =
      static_cast<decltype(opcode)>(cpu6502::opcode::CPX::ZeroPage); // 3 Cycles

  utils::load_to_xreg(cpu, 37);
  PC = cpu.get_registers().PC.get();

  mem[PC++] = opcode;
  mem[PC++] = 0xFF;
  mem[0xFF] = 40;
  cpu.execute(3);

  all_good &= cpu.get_registers().PS.get(PSFlags::ZeroFlag) == false;
  all_good &= cpu.get_registers().PS.get(PSFlags::CarryFlag) == false;
  all_good &= cpu.get_registers().PS.get(PSFlags::NegativeFlag) == true;

  utils::load_to_xreg(cpu, 0x5);
  PC = cpu.get_registers().PC.get();

  mem[PC++] = opcode;
  mem[PC++] = 0xFF;
  mem[0xFF] = 0x5;
  cpu.execute(3);

  all_good &= cpu.get_registers().PS.get(PSFlags::ZeroFlag) == true;
  all_good &= cpu.get_registers().PS.get(PSFlags::CarryFlag) == true;
  all_good &= cpu.get_registers().PS.get(PSFlags::NegativeFlag) == false;

  utils::load_to_xreg(cpu, 0xFF);
  PC = cpu.get_registers().PC.get();

  mem[PC++] = opcode;
  mem[PC++] = 0xFF;
  mem[0xFF] = 0;
  cpu.execute(3);

  all_good &= cpu.get_registers().PS.get(PSFlags::ZeroFlag) == false;
  all_good &= cpu.get_registers().PS.get(PSFlags::CarryFlag) == true;
  all_good &= cpu.get_registers().PS.get(PSFlags::NegativeFlag) == true;

  // END ASSERT CPX - Zero Page

  utils::jump_to_2020(cpu);

  // ASSERT CPX - Absolute
  opcode = static_cast<decltype(opcode)>(cpu6502::opcode::CPX::Absolute);

  utils::load_to_xreg(cpu, 30);
  PC = cpu.get_registers().PC.get();

  mem[PC++] = opcode;
  mem[PC++] = 0x41;
  mem[PC++] = 0x47;
  mem[0x4741] = 40;
  cpu.execute(4);

  all_good &= cpu.get_registers().PS.get(PSFlags::ZeroFlag) == false;
  all_good &= cpu.get_registers().PS.get(PSFlags::CarryFlag) == false;
  all_good &= cpu.get_registers().PS.get(PSFlags::NegativeFlag) == true;

  utils::load_to_xreg(cpu, 0x5);
  PC = cpu.get_registers().PC.get();

  mem[PC++] = opcode;
  mem[PC++] = 0x41;
  mem[PC++] = 0x47;
  mem[0x4741] = 0x5;
  cpu.execute(4);

  all_good &= cpu.get_registers().PS.get(PSFlags::ZeroFlag) == true;
  all_good &= cpu.get_registers().PS.get(PSFlags::CarryFlag) == true;
  all_good &= cpu.get_registers().PS.get(PSFlags::NegativeFlag) == false;

  utils::load_to_xreg(cpu, 0xFF);
  PC = cpu.get_registers().PC.get();

  mem[PC++] = opcode;
  mem[PC++] = 0x41;
  mem[PC++] = 0x47;
  mem[0x4741] = 0;
  cpu.execute(4);

  all_good &= cpu.get_registers().PS.get(PSFlags::ZeroFlag) == false;
  all_good &= cpu.get_registers().PS.get(PSFlags::CarryFlag) == true;
  all_good &= cpu.get_registers().PS.get(PSFlags::NegativeFlag) == true;

  // END ASSERT CPX - Absolute

  return all_good;
}
} // namespace CPU6502_TEST::inner
