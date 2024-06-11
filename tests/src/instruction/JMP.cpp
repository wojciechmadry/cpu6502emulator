#include "instruction_test.hpp"

#include "cpu.hpp"
#include "cpu/InstructionSet/opcode.hpp"

namespace CPU6502_TEST::inner {
bool JMP_TEST() {
  bool all_good = true;
  // using PSFlags = cpu6502::registers::ProcessorStatus::Flags;
  cpu6502::Memory mem(64 * 1024);
  cpu6502::CPU cpu(mem);
  cpu6502::Byte opcode;

  opcode = static_cast<decltype(opcode)>(cpu6502::opcode::JMP::Absolute);

  auto PC = cpu.get_registers().PC.get();

  mem[PC++] = opcode;
  mem[PC++] = 0x20;
  mem[PC++] = 0x20;
  cpu.execute(3);
  PC = 0x2020;
  // ASSERT JMP - Absolute
  mem[PC++] = opcode;
  mem[PC++] = 0x25;
  mem[PC++] = 0x25;
  cpu.execute(3);
  all_good &= (cpu.get_registers().PC.get() == 0x2525);
  PC = cpu.get_registers().PC.get();
  // END ASSERT JMP - Absolute

  // ASSERT JMP - Indirect
  opcode = static_cast<decltype(opcode)>(cpu6502::opcode::JMP::Indirect);
  mem[PC++] = opcode;
  mem[PC++] = 0x42;
  mem[PC++] = 0x42;
  mem[0x4242] = 0x20;
  mem[0x4242 + 1] = 0x20;
  cpu.execute(5);
  all_good &= (cpu.get_registers().PC.get() == 0x2020);
  // END ASSERT JMP - Indirect

  return all_good;
}
} // namespace CPU6502_TEST::inner
