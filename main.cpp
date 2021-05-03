#include <iostream>

#include "cpu.hpp"
#include "tests/ALL_TEST.hpp"

int main() {
    CPU6502_TEST::RUN_ALL_TEST();
    cpu6502::CPU cpu;
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
