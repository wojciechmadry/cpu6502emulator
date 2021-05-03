#include <iostream>

#include "cpu.hpp"
#include "ALL_TEST.hpp"
#include "test.hpp"

int main() {
    show();
    CPU6502_TEST::RUN_ALL_TEST();
    cpu6502::Memory memory(1024 * 64);
    cpu6502::CPU cpu(memory);
    cpu.reset();
    cpu.execute(2);
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
