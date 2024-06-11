#include "instruction_test.hpp"

#include "cpu.hpp"
#include "cpu/InstructionSet/opcode.hpp"
#include "utility/test_utils.hpp"

namespace CPU6502_TEST::inner {
bool STA_TEST() {
  bool all_good = true;

  cpu6502::Memory mem(64 * 1024);
  cpu6502::CPU cpu(mem);
  cpu6502::Byte opcode;

  utils::jump_to_2020(cpu);
  auto PC = cpu.get_registers().PC.get();
  // STA - Zero Page
  opcode = static_cast<decltype(opcode)>(
      cpu6502::opcode::LDA::Immediate); // 2 cycles

  mem[PC++] = static_cast<decltype(opcode)>(
      cpu6502::opcode::JMP::Absolute); // 3 cycles Jump to 0x4242
  mem[PC++] = 0x42;
  mem[PC++] = 0x42;
  mem[0x4242] = opcode;
  mem[0x4242 + 1] = 40; // ACU = 40
  mem[0x4242 + 2] =
      static_cast<decltype(opcode)>(cpu6502::opcode::STA::ZeroPage); // 3 cycles
  mem[0x4242 + 3] = 0x42;
  cpu.execute(8);
  all_good &= (mem[0x42] == 40);
  // END STA - Zero Page

  // STA - Zero Page X
  utils::jump_to_2020(cpu);
  PC = cpu.get_registers().PC.get();
  opcode = static_cast<decltype(opcode)>(
      cpu6502::opcode::LDA::Immediate); // 2 cycles
  mem[PC++] = static_cast<decltype(opcode)>(
      cpu6502::opcode::JMP::Absolute); // 3 cycles Jump to 0x4242
  mem[PC++] = 0x42;
  mem[PC++] = 0x42;
  mem[0x4242] = opcode;
  mem[0x4242 + 1] = 40; // ACU = 40
  mem[0x4242 + 2] = static_cast<decltype(opcode)>(
      cpu6502::opcode::LDX::Immediate); // 2 cycles
  mem[0x4242 + 3] = 0x18;               // X register = 0x18
  mem[0x4242 + 4] = static_cast<decltype(opcode)>(
      cpu6502::opcode::STA::ZeroPageX); // 4 cycles
  mem[0x4242 + 5] = 0x42;
  cpu.execute(11);
  all_good &= (mem[0x42 + 0x18] == 40);
  // END STA - Zero Page X

  // STA - Absolute
  utils::jump_to_2020(cpu);
  PC = cpu.get_registers().PC.get();
  opcode = static_cast<decltype(opcode)>(
      cpu6502::opcode::LDA::Immediate); // 2 cycles
  mem[PC++] = static_cast<decltype(opcode)>(
      cpu6502::opcode::JMP::Absolute); // 3 cycles Jump to 0x4242
  mem[PC++] = 0x42;
  mem[PC++] = 0x42;
  mem[0x4242] = opcode;
  mem[0x4242 + 1] = 40; // ACU = 40
  mem[0x4242 + 2] =
      static_cast<decltype(opcode)>(cpu6502::opcode::STA::Absolute); // 4 cycles
  mem[0x4242 + 3] = 0x30;
  mem[0x4242 + 4] = 0x30;
  cpu.execute(9);
  all_good &= (mem[0x3030] == 40);
  // END STA - Absolute

  // STA - Absolute X
  utils::jump_to_2020(cpu);
  PC = cpu.get_registers().PC.get();
  opcode = static_cast<decltype(opcode)>(
      cpu6502::opcode::LDA::Immediate); // 2 cycles
  mem[PC++] = static_cast<decltype(opcode)>(
      cpu6502::opcode::JMP::Absolute); // 3 cycles Jump to 0x4242
  mem[PC++] = 0x42;
  mem[PC++] = 0x42;
  mem[0x4242] = opcode;
  mem[0x4242 + 1] = 40; // ACU = 40
  mem[0x4242 + 2] = static_cast<decltype(opcode)>(
      cpu6502::opcode::LDX::Immediate); // 2 cycles
  mem[0x4242 + 3] = 0x18;               // X register = 0x18
  mem[0x4242 + 4] = static_cast<decltype(opcode)>(
      cpu6502::opcode::STA::AbsoluteX); // 5 cycles
  mem[0x4242 + 5] = 0x31;
  mem[0x4242 + 6] = 0x31;
  cpu.execute(12);
  all_good &= (mem[0x3131 + 0x18] == 40);
  // END STA - Absolute X

  // STA - Absolute Y
  utils::jump_to_2020(cpu);
  PC = cpu.get_registers().PC.get();
  opcode = static_cast<decltype(opcode)>(
      cpu6502::opcode::LDA::Immediate); // 2 cycles
  mem[PC++] = static_cast<decltype(opcode)>(
      cpu6502::opcode::JMP::Absolute); // 3 cycles Jump to 0x4242
  mem[PC++] = 0x42;
  mem[PC++] = 0x42;
  mem[0x4242] = opcode;
  mem[0x4242 + 1] = 15; // ACU = 15
  mem[0x4242 + 2] = static_cast<decltype(opcode)>(
      cpu6502::opcode::LDY::Immediate); // 2 cycles
  mem[0x4242 + 3] = 0x11;               // Y register = 0x11
  mem[0x4242 + 4] = static_cast<decltype(opcode)>(
      cpu6502::opcode::STA::AbsoluteY); // 5 cycles
  mem[0x4242 + 5] = 0x31;
  mem[0x4242 + 6] = 0x31;
  cpu.execute(12);
  all_good &= (mem[0x3131 + 0x11] == 15);
  // END STA - Absolute Y

  // STA - Indirect X
  utils::jump_to_2020(cpu);
  PC = cpu.get_registers().PC.get();
  opcode = static_cast<decltype(opcode)>(
      cpu6502::opcode::LDA::Immediate); // 2 cycles
  mem[PC++] = static_cast<decltype(opcode)>(
      cpu6502::opcode::JMP::Absolute); // 3 cycles Jump to 0x4242
  mem[PC++] = 0x42;
  mem[PC++] = 0x42;
  mem[0x4242] = opcode;
  mem[0x4242 + 1] = 40; // ACU = 40
  mem[0x4242 + 2] = static_cast<decltype(opcode)>(
      cpu6502::opcode::LDX::Immediate); // 2 cycles
  mem[0x4242 + 3] = 0x18;               // X register = 0x18
  mem[0x4242 + 4] = static_cast<decltype(opcode)>(
      cpu6502::opcode::STA::IndircetX); // 6 cycles
  mem[0x4242 + 5] = 0x30;
  mem[0x30 + 0x18] = 0x15;
  mem[0x30 + 0x18 + 1] = 0x15;
  cpu.execute(13);
  all_good &= (mem[0x1515] == 40);
  // END STA - Indirect X

  // STA - Indirect Y
  utils::jump_to_2020(cpu);
  PC = cpu.get_registers().PC.get();
  opcode = static_cast<decltype(opcode)>(
      cpu6502::opcode::LDA::Immediate); // 2 cycles
  mem[PC++] = static_cast<decltype(opcode)>(
      cpu6502::opcode::JMP::Absolute); // 3 cycles Jump to 0x4242
  mem[PC++] = 0x42;
  mem[PC++] = 0x42;
  mem[0x4242] = opcode;
  mem[0x4242 + 1] = 40; // ACU = 40
  mem[0x4242 + 2] = static_cast<decltype(opcode)>(
      cpu6502::opcode::LDY::Immediate); // 2 cycles
  mem[0x4242 + 3] = 0x18;               // X register = 0x18
  mem[0x4242 + 4] = static_cast<decltype(opcode)>(
      cpu6502::opcode::STA::IndircetY); // 6 cycles
  mem[0x4242 + 5] = 0x30;
  mem[0x30 + 0x18] = 0x15;
  mem[0x30 + 0x18 + 1] = 0x15;
  cpu.execute(13);
  all_good &= (mem[0x1515] == 40);
  // END STA - Indirect Y

  return all_good;
}
} // namespace CPU6502_TEST::inner
