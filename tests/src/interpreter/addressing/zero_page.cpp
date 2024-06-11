#include "interpreter_test.hpp"

#include "cpu.hpp"
#include "interpreter.hpp"
#include "utility/test_utils.hpp"

#include <limits>
#include <string>

namespace CPU6502_TEST::interpreter_test::inner {

bool ADDRESSING_ZERO_PAGE_TEST() {
  bool all_good = true;
  cpu6502::Memory mem(64 * 1024);
  cpu6502::CPU cpu(mem);
  auto &all_reg = cpu.get_registers();

  utils::jump_to_2020(cpu);

  cpu6502::interpreter::Interpreter interp(cpu);
  const std::string label_name_good = "ProperAddress";
  const std::string label_name_bad = "BadAddress";

  constexpr std::uint8_t LSB_good = 0x06;
  constexpr std::uint8_t MSB_good = 0x00;
  constexpr std::uint32_t label_value_good = (MSB_good << 8) | LSB_good;

  interp.add_label(label_name_good, label_value_good);

  constexpr std::uint8_t LSB_bad = 0xFF;
  constexpr std::uint8_t MSB_bad = 0xFF;
  constexpr std::uint32_t label_value_bad = (MSB_bad << 8) | LSB_bad;

  interp.add_label(label_name_bad, label_value_bad);

  constexpr cpu6502::Byte zero_page_val = 0x05;

  auto run_test = [&](const std::string &command, std::uint8_t output,
                      auto &reg) {
    bool test_result = true;
    test_result &= reg.get() == 0;
    const auto addressing = interp.interprete(command);
    test_result &= addressing == cpu6502::interpreter::Addressing::ZeroPage;
    test_result &= reg.get() == output;
    reg.get() = 0;
    all_good &= test_result;
  };

  // Test correct command
  // Write '0x05' to zero page address '0x0006'
  mem[label_value_good] = zero_page_val;
  mem[0xAA] = zero_page_val;

  // Test ADC $AA
  run_test("adc $AA", zero_page_val, all_reg.ACU);

  // Test ADC $00AA
  run_test("adc $00AA", zero_page_val, all_reg.ACU);

  // Test ADC $6
  run_test("adc $6", zero_page_val, all_reg.ACU);

  // Test ADC $06
  run_test("adc $06", zero_page_val, all_reg.ACU);

  // Test ADC ProperAddress
  run_test("adc ProperAddress", zero_page_val, all_reg.ACU);

  // Test three command in row
  {
    cpu.reset();
    utils::jump_to_2020(cpu);
    mem[label_value_good] = zero_page_val;
    auto &reg = cpu.get_registers();
    const std::string cmd1 = "adc $6";
    const std::string cmd2 = "adc $06";
    const std::string cmd3 = "adc ProperAddress";
    interp.interprete(cmd1);
    interp.interprete(cmd2);
    interp.interprete(cmd3);
    all_good &= reg.ACU.get() == zero_page_val * 3;
    reg.ACU.get() = 0;
    cpu.reset();
    utils::jump_to_2020(cpu);
    mem[label_value_good] = zero_page_val;
  }

  // Test bad command

  auto run_bad_cmd = [&](const std::string &command) {
    try {
      const auto addressing = interp.interprete(command);
      all_good &= addressing != cpu6502::interpreter::Addressing::ZeroPage;
    } catch (const std::exception &) {
      all_good &= true;
    }
  };

  // add 6
  run_bad_cmd("add 6");

  // add 06
  run_bad_cmd("add 06");

  // add $256
  run_bad_cmd("add $256");

  // add label_name_bad
  run_bad_cmd("add label_name_bad");
  return all_good;
}

} // namespace CPU6502_TEST::interpreter_test::inner
