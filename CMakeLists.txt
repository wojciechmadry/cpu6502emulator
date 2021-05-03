cmake_minimum_required(VERSION 3.19)
project(cpu_6502_emulator)

set(CMAKE_CXX_STANDARD 20)
add_subdirectory(cpu6502)

add_executable(cpu_6502_emulator main.cpp)

target_link_libraries(cpu_6502_emulator PUBLIC cpu6502)
target_compile_options(cpu_6502_emulator PRIVATE -O3 -Wextra -Werror -W -Wshadow -Wdouble-promotion -Wformat=2 -Wundef -fno-common -Wconversion -pedantic -Wall)
