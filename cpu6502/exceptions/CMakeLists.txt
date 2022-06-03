set(CMAKE_CXX_STANDARD 20)
add_library(
        cpu6502_exceptions STATIC
        cpu_except.cpp
)
target_compile_options(cpu6502_exceptions PRIVATE ${CXX_COMPILER_FLAGS})
set_target_properties(cpu6502_exceptions PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(cpu6502_exceptions PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../")
target_include_directories(cpu6502_exceptions PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")