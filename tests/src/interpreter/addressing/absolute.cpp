#include "interpreter_test.hpp"

#include "cpu.hpp"
#include "interpreter.hpp"
#include "utility/test_utils.hpp"

#include <limits>
#include <string>

namespace CPU6502_TEST::interpreter_test::inner {

bool ADDRESSING_ABSOLUTE_TEST() {
  bool all_good = true;
  cpu6502::Memory mem(64 * 1024);
  cpu6502::CPU cpu(mem);
  auto &all_reg = cpu.get_registers();

  utils::jump_to_2020(cpu);

  cpu6502::interpreter::Interpreter interp(cpu);
  const std::string label_name_good = "ProperAddress";

  // Label address: 0xFA06
  constexpr std::uint8_t LSB_good = 0x06;
  constexpr std::uint8_t MSB_good = 0xAA;
  constexpr std::uint32_t label_value_good = (MSB_good << 8) | LSB_good;

  interp.add_label(label_name_good, label_value_good);

  constexpr cpu6502::Byte absolute_val = 0xA5;

  auto run_test = [&](const std::string &command, std::uint8_t output,
                      auto &reg) {
    bool test_result = true;
    test_result &= reg.get() == 0;
    const auto addressing = interp.interprete(command);
    test_result &= addressing == cpu6502::interpreter::Addressing::Absolute;
    test_result &= reg.get() == output;
    reg.get() = 0;
    all_good &= test_result;
  };

  // Test correct command
  // Write '0x05' to zero page address '0x0006'
  mem[label_value_good] = absolute_val;

  // Test ADC $AA06
  run_test("adc $AA06", absolute_val, all_reg.ACU);

  // Test ADC $0AA06
  run_test("adc $0AA06", absolute_val, all_reg.ACU);

  // Test ADC ProperAddress
  run_test("adc ProperAddress", absolute_val, all_reg.ACU);

  // Test three command in row
  {
    cpu.reset();
    utils::jump_to_2020(cpu);
    auto &reg = cpu.get_registers();
    const std::string cmd1 = "adc $AA06";
    const std::string cmd2 = "adc $0AA06";
    const std::string cmd3 = "adc ProperAddress";
    interp.interprete(cmd1);
    interp.interprete(cmd2);
    interp.interprete(cmd3);
    all_good &= reg.ACU.get() == 254;
    reg.ACU.get() = 0;
    cpu.reset();
    utils::jump_to_2020(cpu);
  }

  {

    const auto addressing_0 = interp.interprete("jmp $1");
    all_good &= addressing_0 == cpu6502::interpreter::Addressing::Absolute;
    all_good &= 0x1 == all_reg.PC.get();

    const auto addressing_1 = interp.interprete("jmp $A04A");
    all_good &= addressing_1 == cpu6502::interpreter::Addressing::Absolute;
    all_good &= 0xA04A == all_reg.PC.get();
  }
  // Test bad command

  auto run_bad_cmd = [&](const std::string &command) {
    try {
      const auto addressing = interp.interprete(command);
      all_good &= addressing != cpu6502::interpreter::Addressing::Absolute;
    } catch (const std::exception &) {
      all_good &= true;
    }
  };

  // add AA06
  run_bad_cmd("add AA06");

  // add 0AA06
  run_bad_cmd("add 0AA06");

  // add $FFFF (out of range)
  run_bad_cmd("add $FFFF");

  // add label_name_bad
  run_bad_cmd("add label_name_bad");

  return all_good;
}

} // namespace CPU6502_TEST::interpreter_test::inner
