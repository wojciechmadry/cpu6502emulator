#include "cpu.hpp"
#include "interpreter/interpreter.hpp"
#include "ALL_TEST.HPP"

#include <fmt/core.h>

int main(){
  CPU6502_TEST::RUN_ALL_TEST();
  
  cpu6502::Memory memory(1024 * 64);
  cpu6502::CPU cpu(memory);
  cpu6502::interpreter::Interpreter interp(cpu);
  const std::string jump = {"jmp $AAAA"};
  interp.interprete(jump);
  fmt::print("Program Counter == {:x}\n", static_cast<int>(cpu.get_registers().PC.get()));

  return 0;
}
