set(CMAKE_CXX_STANDARD 20)

add_subdirectory(registers)

add_library(
        cpu6502_main STATIC
        cpu.hpp
        InstructionSet/LoadStoreOperations/LDA.cpp
        InstructionSet/JumpsCalls/JSR.cpp
        InstructionSet/JumpsCalls/JMP.cpp
        InstructionSet/JumpsCalls/RTS.cpp
        InstructionSet/opcode.hpp
        required.hpp
        memory.hpp
)

set_target_properties(cpu6502_main PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(cpu6502_main PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
target_include_directories(cpu6502_main PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/registers")

add_library(
        cpu6502 INTERFACE
)


target_link_libraries(cpu6502 INTERFACE
        cpu6502_registers
        cpu6502_main
        )

target_include_directories(cpu6502 INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}")
target_include_directories(cpu6502 INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/registers")