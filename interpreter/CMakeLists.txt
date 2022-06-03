set(CMAKE_CXX_STANDARD 20)


add_library(
        cpu6502_interpreter STATIC
        src/interpreter.cpp
        src/interpreter_load_ins.cpp
        src/utility/utility.cpp
        src/utility/opcode_map.cpp
        src/utility/is_accumulator.cpp
        src/utility/is_implicit.cpp
        src/utility/is_relative.cpp
        src/utility/is_indirect.cpp
        src/utility/is_indirect_x.cpp
        src/utility/is_indirect_y.cpp
        src/utility/is_immediate.cpp
        src/utility/is_zero_page_or_absolute.cpp
        src/utility/is_zero_page_x_or_absolute_x.cpp
        src/utility/is_zero_page_y_or_absolute_y.cpp
        src/instruction.cpp
        src/interp_except.cpp
)

target_compile_options(cpu6502_interpreter PRIVATE  ${CXX_COMPILER_FLAGS})

target_include_directories(cpu6502_interpreter PRIVATE "../cpu6502")
set_target_properties(cpu6502_interpreter PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(cpu6502_interpreter PRIVATE cpu6502 fmt)
target_include_directories(cpu6502_interpreter PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
