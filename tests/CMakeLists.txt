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
)

target_compile_options(cpu6502_tests PRIVATE  ${CXX_COMPILER_FLAGS})

target_include_directories(cpu6502_tests PRIVATE "../cpu6502")
set_target_properties(cpu6502_tests PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(cpu6502_tests PRIVATE cpu6502)
target_include_directories(cpu6502_tests PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")