set(CMAKE_CXX_STANDARD 20)
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
add_library(
        cpu6502_tests STATIC
        src/utility/time.cpp
        src/utility/test_logger.cpp
        src/utility/test_utils.cpp
        src/cpu_test.cpp
        src/all_test.cpp
        src/other_tests/register_test.cpp
        src/other_tests/stack_test.cpp
        src/other_tests/memory_test.cpp
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
        src/instruction/MUL.cpp
        src/instruction/SBC.cpp
        src/instruction/CMP.cpp
        src/instruction/CPX.cpp
        src/instruction/CPY.cpp
        src/instruction/NOP.cpp
        src/instruction/BRK.cpp
        src/instruction/RTI.cpp
        src/instruction/ASL.cpp
        src/instruction/LSR.cpp
        src/instruction/ROL.cpp
        src/instruction/ROR.cpp
        src/instruction/INC.cpp
        src/instruction/INX.cpp
        src/instruction/INY.cpp
        src/instruction/DEC.cpp
        src/instruction/DEX.cpp
        src/instruction/DEY.cpp
        src/interpreter/interpreter_test.cpp
        src/interpreter/addressing/immediate.cpp
        src/interpreter/addressing/zero_page.cpp
        src/interpreter/addressing/zero_page_x.cpp
        src/interpreter/addressing/zero_page_y.cpp
        src/interpreter/addressing/absolute.cpp
        src/interpreter/addressing/absolute_x.cpp
        src/interpreter/addressing/absolute_y.cpp
        src/interpreter/addressing/implicit.cpp
        src/interpreter/addressing/accumulator.cpp
        src/interpreter/addressing/relative.cpp
        src/interpreter/addressing/indirect.cpp
        src/interpreter/addressing/indirect_x.cpp
        src/interpreter/addressing/indirect_y.cpp
        src/interpreter/label_comment.cpp
        src/interpreter/fibonacci.cpp
        src/interpreter/factorial.cpp
        src/interpreter/debug_mode.cpp
)

target_compile_options(cpu6502_tests PRIVATE  ${CXX_COMPILER_FLAGS})

target_include_directories(cpu6502_tests PRIVATE "../cpu6502")
set_target_properties(cpu6502_tests PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(cpu6502_tests PRIVATE cpu6502 fmt cpu6502_interpreter)
target_include_directories(cpu6502_tests PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")

add_executable(cpu_6502_test test_main.cpp)

target_link_libraries(cpu_6502_test PUBLIC cpu6502 fmt cpu6502_tests cpu6502_interpreter )

target_compile_options(cpu_6502_test PRIVATE ${CXX_COMPILER_FLAGS})