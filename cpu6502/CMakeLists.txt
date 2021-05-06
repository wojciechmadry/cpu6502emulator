set(CMAKE_CXX_STANDARD 20)

add_subdirectory(registers)
add_subdirectory(memory)

add_library(
        cpu6502_main STATIC
        cpu.hpp
        cpu/InstructionSet/LoadStoreOperations/LDA.cpp
        cpu/InstructionSet/LoadStoreOperations/LDX.cpp
        cpu/InstructionSet/JumpsCalls/JSR.cpp
        cpu/InstructionSet/JumpsCalls/JMP.cpp
        cpu/InstructionSet/JumpsCalls/RTS.cpp
        cpu/InstructionSet/opcode.hpp
        cpu/WriteRead/read.cpp
        cpu/WriteRead/write.cpp
        cpu/execute_instruction.cpp
        required.hpp
)

set_target_properties(cpu6502_main PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(cpu6502_main PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")

add_library(
        cpu6502 INTERFACE
)


target_link_libraries(cpu6502 INTERFACE
        cpu6502_memory
        cpu6502_registers
        cpu6502_main
        )

target_include_directories(cpu6502 INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}")
target_include_directories(cpu6502 INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/registers")