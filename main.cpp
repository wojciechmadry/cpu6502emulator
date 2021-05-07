#include <iostream>

#include "cpu.hpp"
#include "ALL_TEST.HPP"

int main(){

    CPU6502_TEST::RUN_ALL_TEST(1);

    cpu6502::Memory memory(1024 * 64);
    cpu6502::CPU cpu(memory);
    cpu.reset();
    //Program
    memory[cpu.get_registers().PC.get()] = 0xA9;
    memory[cpu.get_registers().PC.get() + 1] = 39;
    //END program
    cpu.execute(2);
    std::cout << sizeof(cpu) << std::endl;
    return 0;
}
