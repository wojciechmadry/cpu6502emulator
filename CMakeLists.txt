cmake_minimum_required(VERSION 3.17)
project(cpu_6502_emulator)

set(CXX_COMPILER_FLAGS -g -O3 -Wextra -Werror -W
-Wno-unused-parameter
-Wshadow -Wdouble-promotion -Wformat=2 
-Wundef -fno-common -Wconversion -Wpedantic -Wall
-Wno-unused-result -Wno-unused-variable 
-Wno-unused-but-set-variabl)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(fmt)

add_subdirectory(cpu6502)
add_subdirectory(interpreter)
add_subdirectory(tests)

add_executable(cpu_6502_emulator main.cpp)

target_link_libraries(cpu_6502_emulator PUBLIC cpu6502 fmt cpu6502_tests cpu6502_interpreter)

target_compile_options(cpu_6502_emulator PRIVATE ${CXX_COMPILER_FLAGS})
