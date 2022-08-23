cmake_minimum_required(VERSION 3.17)
project(cpu_6502_emulator)

set(DEBUG_MODE 1)

if(${DEBUG_MODE} EQUAL 1)
    set(CXX_COMPILER_FLAGS -g -O3 -Wextra -Werror -W
    -Wno-unused-parameter
    -Wshadow -Wdouble-promotion -Wformat=2 
    -Wundef -fno-common -Wconversion -Wpedantic -Wall
    -Wno-unused-result -Wno-unused-variable 
    -Wno-unused-but-set-variable)
else()
    set(CXX_COMPILER_FLAGS -O3)
endif()

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(fmt)

add_subdirectory(cpu6502)
add_subdirectory(interpreter)
add_subdirectory(tests)
add_subdirectory(gui)

# Copy asm examples file to build folder
file(COPY examples/ DESTINATION examples)
