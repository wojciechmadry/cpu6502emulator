#include "cpu.hpp"
#include "interpreter/interpreter.hpp"
#include "ALL_TEST.HPP"

#include <fmt/core.h>

int main(){
  CPU6502_TEST::RUN_ALL_TEST();
  
  cpu6502::Memory memory(1024 * 64);
  cpu6502::CPU cpu(memory);
  //Program
  auto pc = cpu.get_registers().PC.get();

  memory[pc] = 0x20; // JMP to half of memory (6 cycles);
  memory[pc + 1] = 0x00; // Second 8 bits;
  memory[pc + 2] = 0x80; // First 8 bits;


  cpu.execute(6); // Execute jump
  cpu.get_registers().PS.put_byte(0x00);

  pc = cpu.get_registers().PC.get();
  
  memory[pc] = 0xA9; // Load to accumulator register  value 222 (2 cycles)
  memory[pc + 1] = 222; // value in accumulator
  memory[pc + 2] = 0x48; // Push accumulator on stack (3 cycles)
  memory[pc + 3] = 0xA9; // Load to accumulator register  value 5 (2 cycles)
  memory[pc + 4] = 5; // First value in accumulator
  memory[pc + 5] = 0x48; // Push accumulator on stack (3 cycles)
  memory[pc + 6] = 0xA9; // Load to accumulator register  value 0 (2 cycles)
  memory[pc + 7] = 0; // Second value in accumulator
  memory[pc + 8] = 0x09; // ORA (2 cycles)
  memory[pc + 9] = 17; // ACU | 17 (10001)
  // After thath ACU should be equal 0 | 17 --> 17
  memory[pc + 10] = 0x8D; // Store ACU in memory ( 4 cycles)
  memory[pc + 11] = static_cast<unsigned char>(pc + 14); // Write ACU value to memory on position pc + 14 // Second eigth bits
  memory[pc + 12] = static_cast<unsigned char>((pc + 14) >> 8); // Write ACU value to memory on position pc + 14 // First eitghs bits
  memory[pc + 13] = 0xA2; // Load 17 (ACU) to LDX register (2 cycles)
  memory[pc + 15] = 0x68; // Pull accumulator from stack (4 cycles) (ACU == 5)
  memory[pc + 16] = 0x09; // ORA (2 cycles)
  memory[pc + 17] = 17; // ACU | 17 (10001)
  // After thath ACU should be equal 5 | 17 --> (10101 == 21)
  memory[pc + 18] = 0x8D; // Store ACU in memory ( 4 cycles)
  memory[pc + 19] = static_cast<unsigned char>(pc + 22); // Write ACU value to memory on position pc + 22 // Second eigth bits
  memory[pc + 20] = static_cast<unsigned char>((pc + 22) >> 8); // Write ACU value to memory on position pc + 22 // First eitghs bits
  memory[pc + 21] = 0xA0; // Load 22 (ACU) to LDY register (2 cycles)
  memory[pc + 23] = 0x68; // Pull accumulator from stack (4 cycles) (ACU == 222)



  //END program
  cpu.execute(36); // 36
  fmt::print("ACU : {}\n", static_cast<int>(cpu.get_registers().ACU.get()));
  fmt::print("LDX : {}\n", static_cast<int>(cpu.get_registers().IRX.get()));
  fmt::print("LDY : {}\n", static_cast<int>(cpu.get_registers().IRY.get()));

  fmt::print("--- Interpreter ---\n");
  cpu6502::interpreter::Interpreter interp(cpu);
  fmt::print("Number of addresing type: {}\n", static_cast<int>(cpu6502::interpreter::Addressing::NUM_OF_ADDRESSING));

  // Immediate adc
  const std::string ins_im_adc = {"adc #10"}; // can be ADC etc...
  const std::string ins_im_hi_adc = {"adc #HI TEST"}; // can be hi test
  const std::string ins_im_lo_adc = {"adc #LO TEST"}; // can be lo test
  // Zero page adc
  
  const std::string ins_zp_adc = {"adc $55"};
  const std::string ins_zp_adc_label = {"adc ZP_LABEL"};
  
  // Zero Page X adc

  const std::string ins_zpx_adc = {"adc $55, X"};
  const std::string ins_zpx_adc_label = {"adc ZP_LABEL, X"};

  // Absolute adc

  // Absolute X adc

  // Absolute Y adc

  // Indirect X adc

  // Indirect Y adc

  /*
  interp.add_label("test", 1234);
  interp.add_label("zp_label", 12);
  fmt::print("-----------------\n");
  interp.interprete(ins_im_adc);
  fmt::print("-----------------\n");
  interp.interprete(ins_im_hi_adc);
  fmt::print("-----------------\n");
  interp.interprete(ins_im_lo_adc);
  fmt::print("-----------------\n");
  interp.interprete(ins_zp_adc);
  fmt::print("-----------------\n");
  interp.interprete(ins_zp_adc_label);
  fmt::print("-----------------\n");
  interp.interprete(ins_zpx_adc);
  fmt::print("-----------------\n");
  interp.interprete(ins_zpx_adc_label);
  fmt::print("-----------------\n");
  */
  return 0;
}
