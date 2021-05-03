set(CMAKE_CXX_STANDARD 20)

add_subdirectory(registers)

add_library(
        cpu6502 STATIC
        cpu.hpp
        required.hpp
        memory.hpp
)

set_target_properties(cpu6502 PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(cpu6502 PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
target_include_directories(cpu6502 PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/registers")