#include "interpreter_test.hpp"

#include "cpu.hpp"
#include "interpreter.hpp"
#include "processorstatus.hpp"
#include "required.hpp"
#include "utility/test_utils.hpp"

#include <limits>
#include <string>

namespace CPU6502_TEST::interpreter_test::inner {

bool ADDRESSING_INDIRECT_Y_TEST() {
  bool all_good = true;
  cpu6502::Memory mem(64 * 1024);
  cpu6502::CPU cpu(mem);
  auto &all_reg = cpu.get_registers();

  utils::jump_to_2020(cpu);

  cpu6502::interpreter::Interpreter interp(cpu);

  const std::string label = "memory";
  constexpr std::uint8_t LSB = 0xA2;
  constexpr std::uint8_t MSB = 0x00;
  constexpr std::uint32_t label_value = (MSB << 8) | LSB; // 0x00A2
  constexpr cpu6502::Byte IRY_value = 0x12;
  constexpr cpu6502::Word memory_addr = 0x2713;
  constexpr cpu6502::Byte memory_val = 0x16;
  mem[label_value] = memory_addr & 0xFF;
  mem[label_value + 1] = (memory_addr >> 8) & 0xFF;
  mem[memory_addr + IRY_value] = memory_val;

  utils::load_to_yreg(cpu, IRY_value);
  interp.add_label(label, label_value);

  auto run_test = [&](const std::string &command, cpu6502::Byte ACU_value) {
    all_good &= all_reg.ACU.get() == 0;
    const auto addressing = interp.interprete(command);
    all_good &= addressing == cpu6502::interpreter::Addressing::IndirectY;
    all_good &= all_reg.ACU.get() == ACU_value;
    all_reg.ACU.set(0);
    all_reg.PS.put_byte(0);
  };

  // Test correct command
  run_test("adc ($00A2),Y", memory_val);
  run_test("adc  ($00A2),Y", memory_val);
  run_test("adc ($00A2),Y ", memory_val);
  run_test("adc  ($00A2),Y  ", memory_val);
  run_test("adc  ($00A2), Y  ", memory_val);
  run_test("adc (  $00A2  ), Y  ", memory_val);
  run_test("adc ( $0 0A2  ),  y  ", memory_val);

  run_test("ADC ($00A2), Y", memory_val);
  run_test("aDc  ($00A2), Y", memory_val);
  run_test("adc ($00a2),Y ", memory_val);
  run_test("adc  ($00A2), Y  ", memory_val);
  run_test("adc ( $00a2  ),  y   ", memory_val);
  run_test("adC ( $0 0 a 2   ),y  ", memory_val);

  run_test("adc (memory),Y", memory_val);
  run_test("adc  (memory),Y ", memory_val);
  run_test("adc (memory), Y ", memory_val);
  run_test("adc  (memory), y  ", memory_val);
  run_test("adc ( memory ) , Y ", memory_val);
  run_test("adc ( m e m o r y    ),y  ", memory_val);

  // Test bad command
  auto run_bad_cmd = [&](const std::string &command) {
    try {
      const auto addressing = interp.interprete(command);
      all_good &= addressing != cpu6502::interpreter::Addressing::IndirectY;
    } catch (const std::exception &) {
      all_good &= true;
    }
  };

  run_bad_cmd("adc ($00A2,X)");
  run_bad_cmd("adc ($00A2) Y");
  run_bad_cmd("adc ($00A2), X");
  run_bad_cmd("adc ($00A2,Y");
  run_bad_cmd("adc $00A2,X), Y");
  run_bad_cmd("adc $00A2,X, Y");
  run_bad_cmd("adv ($00A2),y X");
  run_bad_cmd("adv ($%00A2),Y");
  run_bad_cmd("adv ($#00A2),Y");
  run_bad_cmd("adv (#00A2,Y)");
  run_bad_cmd("adv (00A2,Y)");
  run_bad_cmd("adv (mems,y)");

  return all_good;
}

} // namespace CPU6502_TEST::interpreter_test::inner
