set(CMAKE_CXX_STANDARD 20)
add_library(
        cpu6502_tests STATIC
        ALL_TEST.HPP
        register_test.hpp
        cpu_test.hpp
        InstructionSetTest/JMP_TEST.HPP
        InstructionSetTest/LDA_TEST.HPP
        InstructionSetTest/LDX_TEST.HPP
        InstructionSetTest/LDY_TEST.HPP
        InstructionSetTest/STA_TEST.HPP
        InstructionSetTest/STX_TEST.HPP
        InstructionSetTest/STY_TEST.HPP
        InstructionSetTest/RTS_JSR_TEST.HPP
        InstructionSetTest/StatusFlagChanges.HPP
        InstructionSetTest/REGISTER_TRANSFER.HPP
        time.hpp
)
set_target_properties(cpu6502_tests PROPERTIES LINKER_LANGUAGE CXX)
target_compile_options(cpu6502_tests PRIVATE -O3 -Wextra -Werror -W -Wshadow -Wdouble-promotion -Wformat=2 -Wundef -fno-common -Wconversion -pedantic -Wall)
target_include_directories(cpu6502_tests PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")