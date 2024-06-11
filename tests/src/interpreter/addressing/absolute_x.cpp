#include "interpreter_test.hpp"

#include "cpu.hpp"
#include "interpreter.hpp"
#include "utility/test_utils.hpp"

#include <limits>
#include <string>

namespace CPU6502_TEST::interpreter_test::inner {

bool ADDRESSING_ABSOLUTE_X_TEST() {
  bool all_good = true;
  cpu6502::Memory mem(64 * 1024);
  cpu6502::CPU cpu(mem);
  auto &all_reg = cpu.get_registers();

  utils::jump_to_2020(cpu);

  constexpr cpu6502::Byte IRX_value = 0x15;
  utils::load_to_xreg(cpu, IRX_value);

  cpu6502::interpreter::Interpreter interp(cpu);
  const std::string label_name_good = "ProperAddress";

  constexpr std::uint8_t LSB_good = 0x06;
  constexpr std::uint8_t MSB_good = 0xAA;
  constexpr std::uint32_t label_value_good = (MSB_good << 8) | LSB_good;

  interp.add_label(label_name_good, label_value_good);

  constexpr cpu6502::Byte absolute_val = 0xA0;

  auto run_test = [&](const std::string &command, std::uint8_t output,
                      auto &reg) {
    bool test_result = true;
    test_result &= reg.get() == 0;
    const auto addressing = interp.interprete(command);
    test_result &= addressing == cpu6502::interpreter::Addressing::AbsoluteX;
    test_result &= reg.get() == output;
    reg.get() = 0;
    all_good &= test_result;
  };

  // Test correct command
  // Write '0x05' to zero page address '0x0006' + IRX
  mem[label_value_good + IRX_value] = absolute_val;
  mem[0xAAAA + IRX_value] = absolute_val;

  // Test ADC $A, X
  run_test("adc $AAAA, X", absolute_val, all_reg.ACU);

  // Test ADC $0A, X
  run_test("adc $0AAAA, X", absolute_val, all_reg.ACU);

  // Test ADC $AA06, X
  run_test("adc $AA06, X", absolute_val, all_reg.ACU);

  // Test ADC $0AA06, X
  run_test("adc $0AA06, X", absolute_val, all_reg.ACU);

  // Test ADC $AA06, x
  run_test("adc $AA06, x", absolute_val, all_reg.ACU);

  // Test ADC $AA06, x
  run_test("adc $0AA06, x", absolute_val, all_reg.ACU);

  // Test ADC ProperAddress, x
  run_test("adc ProperAddress, x", absolute_val, all_reg.ACU);

  // Test ADC PROPERADDRESS, x
  run_test("adc PROPERADDRESS, x", absolute_val, all_reg.ACU);

  // Test ADC ProperAddress, x
  run_test("adc ProperAddress, x", absolute_val, all_reg.ACU);

  // Test ADC PROPERADDRESS, x
  run_test("adc PROPERADDRESS, x", absolute_val, all_reg.ACU);

  // Test three command in row
  {
    cpu.reset();
    utils::jump_to_2020(cpu);
    auto &reg = cpu.get_registers();
    const std::string cmd1 = "adc ProperAddress, x";
    const std::string cmd2 = "adc $0AA06, x";
    const std::string cmd3 = "adc $AA06, X";
    interp.interprete(cmd1);
    interp.interprete(cmd2);
    interp.interprete(cmd3);
    all_good &= reg.ACU.get() == 254;
    reg.ACU.get() = 0;
    cpu.reset();
    utils::jump_to_2020(cpu);
  }

  // Test bad command

  auto run_bad_cmd = [&](const std::string &command) {
    try {
      const auto addressing = interp.interprete(command);
      all_good &= addressing != cpu6502::interpreter::Addressing::ZeroPageX;
    } catch (const std::exception &) {
      all_good &= true;
    }
  };

  run_bad_cmd("add 6, X");

  run_bad_cmd("add 06, x");

  run_bad_cmd("add $256, x");

  run_bad_cmd("add label_name_bad, x");

  run_bad_cmd("adc ($00A2,X)");

  run_bad_cmd("adc ($00A2,Y)");

  return all_good;
}

} // namespace CPU6502_TEST::interpreter_test::inner
