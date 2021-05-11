set(CMAKE_CXX_STANDARD 20)
add_library(
        cpu6502_memory STATIC
        memory.cpp
        memory.hpp
        ../required.hpp
)
set_target_properties(cpu6502_memory PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(cpu6502_memory PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../")
target_include_directories(cpu6502_memory PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
target_compile_options(cpu6502_memory PRIVATE -O3 -Wextra -Werror -W -Wshadow -Wdouble-promotion -Wformat=2 -Wundef -fno-common -Wconversion -pedantic -Wall)