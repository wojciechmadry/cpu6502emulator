#include <iostream>

#include "cpu.hpp"
#include "ALL_TEST.HPP"
int main(){
    CPU6502_TEST::RUN_ALL_TEST();

    cpu6502::Memory memory(1024 * 64);
    cpu6502::CPU cpu(memory);
    cpu.reset();
    //Program
    memory[0xFFFC] = 0xA9;
    memory[0xFFFD] = 39;
    //END program
    cpu.execute(2);
    std::cout << (int)cpu.get_registers().ACU.get() << std::endl;
    return 0;
}
