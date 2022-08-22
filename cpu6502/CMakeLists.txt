set(CMAKE_CXX_STANDARD 20)

add_subdirectory(exceptions)
add_subdirectory(registers)
add_subdirectory(memory)

add_library(
        cpu6502 STATIC
        cpu/cpu.cpp
        cpu/InstructionSet/LoadStoreOperations/LDA.cpp
        cpu/InstructionSet/LoadStoreOperations/LDX.cpp
        cpu/InstructionSet/LoadStoreOperations/LDY.cpp
        cpu/InstructionSet/LoadStoreOperations/STA.cpp
        cpu/InstructionSet/LoadStoreOperations/STX.cpp
        cpu/InstructionSet/LoadStoreOperations/STY.cpp
        cpu/InstructionSet/StatusFlagChanges/CLC.cpp
        cpu/InstructionSet/StatusFlagChanges/CLD.cpp
        cpu/InstructionSet/StatusFlagChanges/CLI.cpp
        cpu/InstructionSet/StatusFlagChanges/CLV.cpp
        cpu/InstructionSet/StatusFlagChanges/SEC.cpp
        cpu/InstructionSet/StatusFlagChanges/SED.cpp
        cpu/InstructionSet/StatusFlagChanges/SEI.cpp
        cpu/InstructionSet/RegisterTransfers/TAX.cpp
        cpu/InstructionSet/RegisterTransfers/TAY.cpp
        cpu/InstructionSet/RegisterTransfers/TXA.cpp
        cpu/InstructionSet/RegisterTransfers/TYA.cpp
        cpu/InstructionSet/JumpsCalls/JSR.cpp
        cpu/InstructionSet/JumpsCalls/JMP.cpp
        cpu/InstructionSet/JumpsCalls/RTS.cpp
        cpu/InstructionSet/StackOperations/PHA.cpp
        cpu/InstructionSet/StackOperations/PHP.cpp
        cpu/InstructionSet/StackOperations/PLA.cpp
        cpu/InstructionSet/StackOperations/PLP.cpp
        cpu/InstructionSet/StackOperations/TSX.cpp
        cpu/InstructionSet/StackOperations/TXS.cpp
        cpu/InstructionSet/Logical/AND.cpp
        cpu/InstructionSet/Logical/EOR.cpp
        cpu/InstructionSet/Logical/ORA.cpp
        cpu/InstructionSet/Logical/BIT.cpp
        cpu/InstructionSet/Branches/BRANCHES.cpp
        cpu/InstructionSet/Arithmetic/ADC.cpp
        cpu/InstructionSet/Arithmetic/MUL.cpp
        cpu/InstructionSet/Arithmetic/SBC.cpp
        cpu/InstructionSet/Arithmetic/CMP.cpp
        cpu/InstructionSet/Arithmetic/CPX.cpp
        cpu/InstructionSet/Arithmetic/CPY.cpp
        cpu/InstructionSet/SystemFunctions/BRK.cpp
        cpu/InstructionSet/SystemFunctions/NOP.cpp
        cpu/InstructionSet/SystemFunctions/RTI.cpp
        cpu/InstructionSet/Shifts/ASL.cpp
        cpu/InstructionSet/Shifts/LSR.cpp
        cpu/InstructionSet/Shifts/ROL.cpp
        cpu/InstructionSet/Shifts/ROR.cpp
        cpu/InstructionSet/IncrementsDecrements/DEC.cpp
        cpu/InstructionSet/IncrementsDecrements/DEX.cpp
        cpu/InstructionSet/IncrementsDecrements/DEY.cpp
        cpu/InstructionSet/IncrementsDecrements/INC.cpp
        cpu/InstructionSet/IncrementsDecrements/INX.cpp
        cpu/InstructionSet/IncrementsDecrements/INY.cpp
        cpu/WriteRead/read.cpp
        cpu/WriteRead/write.cpp
        cpu/InstructionSet/opcode.hpp
)

target_link_libraries(cpu6502
        cpu6502_memory
        cpu6502_registers
        cpu6502_exceptions)

set_target_properties(cpu6502 PROPERTIES LINKER_LANGUAGE CXX)
target_compile_options(cpu6502 PRIVATE ${CXX_COMPILER_FLAGS})

target_include_directories(cpu6502 PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
target_include_directories(cpu6502 PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/registers")
