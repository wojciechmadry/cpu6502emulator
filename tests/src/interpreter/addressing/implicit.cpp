#include "instruction.hpp"
#include "interpreter_test.hpp"

#include "cpu.hpp"
#include "interpreter.hpp"
#include "processorstatus.hpp"
#include "required.hpp"
#include "utility/test_utils.hpp"

#include <limits>
#include <string>

namespace CPU6502_TEST::interpreter_test::inner {

bool ADDRESSING_IMPLICIT_TEST() {
  bool all_good = true;
  cpu6502::Memory mem(64 * 1024);
  cpu6502::CPU cpu(mem);
  auto &all_reg = cpu.get_registers();

  utils::jump_to_2020(cpu);

  cpu6502::interpreter::Interpreter interp(cpu);

  auto run_test = [&](const std::string &command, bool output, auto flag) {
    const auto &reg = all_reg.PS;
    bool test_result = true;
    auto addressing = interp.interprete(command);
    test_result &= addressing == cpu6502::interpreter::Addressing::Implicit;
    test_result &= reg.get(flag) == output;
    all_good &= test_result;
  };
  // Test correct command

  mem[cpu6502::CPU::IRQ] = 0x10;
  mem[cpu6502::CPU::IRQ + 1] = 0x10;

  {
    const auto PC_before = all_reg.PC.get();
    // BRK (Force interrupt)
    auto addressing_brk = interp.interprete("brk");
    all_good &= addressing_brk == cpu6502::interpreter::Addressing::Implicit;
    all_good &= PC_before != all_reg.PC.get() && all_reg.PC.get() == 0x1010;
    // RTI (Return from interrupt)
    auto addressing_rti = interp.interprete("rti");
    all_good &= addressing_rti == cpu6502::interpreter::Addressing::Implicit;
    all_good &=
        PC_before != all_reg.PC.get() && all_reg.PC.get() == PC_before + 1;
  }

  // Test SEC (set carry flag)
  run_test("SEC", true, cpu6502::registers::ProcessorStatus::Flags::CarryFlag);
  run_test("SEC", true, cpu6502::registers::ProcessorStatus::Flags::CarryFlag);

  // Test CLC (clear carry flag)
  run_test("CLC", false, cpu6502::registers::ProcessorStatus::Flags::CarryFlag);
  run_test("CLC", false, cpu6502::registers::ProcessorStatus::Flags::CarryFlag);

  utils::load_to_xreg(cpu, 0xF);

  // TXA (Transfer X reg to ACU)
  {
    auto addressing = interp.interprete("txa");
    all_good &= addressing == cpu6502::interpreter::Addressing::Implicit;
    all_good &= all_reg.ACU.get() == 0xF;
  }

  // NOP (No operations)
  {
    const auto pc = cpu.get_registers().PC.get();
    auto addressing = interp.interprete("NoP");
    all_good &= addressing == cpu6502::interpreter::Addressing::Implicit;
    all_good &= cpu.get_registers().PC.get() == pc + 1;
  }

  // Test bad command

  auto run_bad_cmd = [&](const std::string &command) {
    try {
      const auto addressing = interp.interprete(command);
      all_good &= addressing != cpu6502::interpreter::Addressing::Implicit;
    } catch (const std::exception &) {
      all_good &= true;
    }
  };

  // ad
  run_bad_cmd("ad");

  // adc
  run_bad_cmd("adc");

  return all_good;
}

} // namespace CPU6502_TEST::interpreter_test::inner
