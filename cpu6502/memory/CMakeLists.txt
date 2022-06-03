set(CMAKE_CXX_STANDARD 20)
add_library(
        cpu6502_memory STATIC
        memory.cpp
)
target_compile_options(cpu6502_memory PRIVATE ${CXX_COMPILER_FLAGS})
target_link_libraries(cpu6502_memory PRIVATE cpu6502_exceptions)
set_target_properties(cpu6502_memory PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(cpu6502_memory PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../")
target_include_directories(cpu6502_memory PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")