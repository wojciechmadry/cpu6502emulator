set(CMAKE_CXX_STANDARD 20)
add_library(
        cpu6502_tests STATIC
        src/time.cpp
        src/test_logger.cpp
        src/register_test.cpp
        src/cpu_test.cpp
        src/ALL_TEST.cpp
        src/instruction/AND.cpp
        src/instruction/BIT.cpp
        src/instruction/BRANCHES.cpp
        src/instruction/EOR.cpp
        src/instruction/JMP.cpp
        src/instruction/LDA.cpp
        src/instruction/LDX.cpp
        src/instruction/LDY.cpp
        src/instruction/ORA.cpp
        src/instruction/RegisterTransfer.cpp
        src/instruction/RTS_JSR.cpp
        src/instruction/STA.cpp
        src/instruction/StackOperations.cpp
        src/instruction/StatusFlagChanges.cpp
        src/instruction/STX.cpp
        src/instruction/STY.cpp
        src/instruction/ADC.cpp
)

target_include_directories(cpu6502_tests PRIVATE "../cpu6502")
set_target_properties(cpu6502_tests PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(cpu6502_tests PRIVATE cpu6502)
target_compile_options(cpu6502_tests PRIVATE -O3 -Wextra -Werror -W -Wshadow -Wdouble-promotion -Wformat=2 -Wundef -fno-common -Wconversion -pedantic -Wall)
target_include_directories(cpu6502_tests PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")