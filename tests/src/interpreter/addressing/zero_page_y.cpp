#include "fmt/core.h"
#include "interpreter_test.hpp"

#include "cpu.hpp"
#include "interpreter.hpp"
#include "utility/test_utils.hpp"

#include <limits>
#include <string>

namespace CPU6502_TEST::interpreter_test::inner {

bool ADDRESSING_ZERO_PAGE_Y_TEST() {
  bool all_good = true;
  cpu6502::Memory mem(64 * 1024);
  cpu6502::CPU cpu(mem);
  auto &all_reg = cpu.get_registers();

  utils::jump_to_2020(cpu);

  constexpr cpu6502::Byte IRY_value = 0x0F;
  utils::load_to_yreg(cpu, IRY_value);

  cpu6502::interpreter::Interpreter interp(cpu);
  const std::string label_name_good = "ProperAddress";
  const std::string label_name_bad = "BadAddress";

  constexpr std::uint8_t LSB_good = 0x1A;
  constexpr std::uint8_t MSB_good = 0x00;
  constexpr std::uint32_t label_value_good = (MSB_good << 8) | LSB_good;

  interp.add_label(label_name_good, label_value_good);

  constexpr std::uint8_t LSB_bad = 0xFF;
  constexpr std::uint8_t MSB_bad = 0xFF;
  constexpr std::uint32_t label_value_bad = (MSB_bad << 8) | LSB_bad;

  interp.add_label(label_name_bad, label_value_bad);

  constexpr cpu6502::Byte zero_page_val = 0xF;

  auto run_test = [&](const std::string &command, std::uint8_t output,
                      auto &reg) {
    bool test_result = true;
    test_result &= reg.get() == 0;
    const auto addressing = interp.interprete(command);
    test_result &= addressing == cpu6502::interpreter::Addressing::ZeroPageY;
    test_result &= reg.get() == output;
    reg.get() = 0;
    all_good &= test_result;
  };

  // Test correct command
  // Write '0xF' to zero page address '0x001A' + IRY
  mem[label_value_good + IRY_value] = zero_page_val;
  mem[0xA + IRY_value] = zero_page_val;

  // Test LDX $A, Y
  run_test("LDX $A, Y", zero_page_val, all_reg.IRX);

  // Test LDX $0A, Y
  run_test("LDX $0A, Y", zero_page_val, all_reg.IRX);

  // Test LDX $001A, Y
  run_test("LDX $001A, Y", zero_page_val, all_reg.IRX);

  // Test LDX $1a, Y
  run_test("LDX $1a, Y", zero_page_val, all_reg.IRX);

  // Test LDX $1a, y
  run_test("LDX $1a, y", zero_page_val, all_reg.IRX);

  // Test ldx $00001A, y
  run_test("ldx $00001A, y", zero_page_val, all_reg.IRX);

  // Test ldx ProperAddress, y
  run_test("ldx ProperAddress, y", zero_page_val, all_reg.IRX);

  // Test LDX PROPERADDRESS, y
  run_test("LDX PROPERADDRESS, y", zero_page_val, all_reg.IRX);

  // Test ldx ProperAddress, y
  run_test("ldx ProperAddress, y", zero_page_val, all_reg.IRX);

  // Test ldx PROPERADDRESS, y
  run_test("ldx PROPERADDRESS, y", zero_page_val, all_reg.IRX);

  // Test three command in row
  {
    cpu.reset();
    utils::jump_to_2020(cpu);
    utils::load_to_yreg(cpu, IRY_value);
    mem[label_value_good + IRY_value] = zero_page_val;
    const std::string cmd1 = "ldx ProperAddress, y";
    const std::string cmd2 = "ldx $01A, y";
    const std::string cmd3 = "ldx $1a, y";
    interp.interprete(cmd1);
    interp.interprete(cmd2);
    interp.interprete(cmd3);
    all_good &= all_reg.IRX.get() == zero_page_val;
    all_reg.IRX.get() = 0;
    cpu.reset();
    utils::jump_to_2020(cpu);
    utils::load_to_yreg(cpu, IRY_value);
    mem[label_value_good + IRY_value] = zero_page_val;
  }

  // Test bad command

  auto run_bad_cmd = [&](const std::string &command) {
    try {
      const auto addressing = interp.interprete(command);
      all_good &= addressing != cpu6502::interpreter::Addressing::ZeroPageY;
    } catch (const std::exception &) {
      all_good &= true;
    }
  };

  // add 6, Y
  run_bad_cmd("add 6, Y");

  // add 06, y
  run_bad_cmd("add 06, y");

  // add $256, y
  run_bad_cmd("add $256, y");

  // add label_name_bad, y
  run_bad_cmd("add label_name_bad, y");

  run_bad_cmd("ldx 6, Y");

  run_bad_cmd("ldx 06, y");

  run_bad_cmd("ldx $256, y");

  run_bad_cmd("ldx label_name_bad, y");

  run_bad_cmd("adc ($00A2,X)");

  run_bad_cmd("adc ($00A2,x)");

  run_bad_cmd("adc ($00A2,Y)");

  run_bad_cmd("adc ($00A2,y)");

  return all_good;
}

} // namespace CPU6502_TEST::interpreter_test::inner
