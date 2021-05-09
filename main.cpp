#include <iostream>

#include "cpu.hpp"
#include "ALL_TEST.HPP"

int main(){

    CPU6502_TEST::RUN_ALL_TEST(1);
    // 100 DEBUG - 3.19775
    // 100 DEBUG NEW - 3.30985
    // 100 RELEASE - 0.0110093
    // 100 RELEASE NEW - 0.010509
    cpu6502::Memory memory(1024 * 64);
    cpu6502::CPU cpu(memory);
    cpu6502::CPU cpu2(memory);
    //Program
    memory[cpu.get_registers().PC.get()] = 0xA9;
    memory[cpu.get_registers().PC.get() + 1] = 39;
    //END program
    cpu.execute(2);
    cpu2.execute(2);
    // size - 8208
    // after - 2064
    std::cout << sizeof(cpu) << std::endl;
    return 0;
}
