cmake_minimum_required(VERSION 3.17)
project(cpu_6502_emulator)
set(CMAKE_CXX_STANDARD 20)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

if(NOT USE_CLANG_TIDY)
	set(USE_CLANG_TIDY False)
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
	message("-- Debug mode build")
    set(CXX_COMPILER_FLAGS -g -O3 -Wextra -Werror -W
    -Wno-unused-parameter
    -Wshadow -Wdouble-promotion -Wformat=2 
    -Wundef -fno-common -Wconversion -Wpedantic -Wall
    -Wno-unused-result -Wno-unused-variable 
    -Wno-unused-but-set-variable)
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
	message("-- Release mode build")
	set(CXX_COMPILER_FLAGS -O3)
endif()

add_subdirectory(fmt)

if(USE_CLANG_TIDY STREQUAL True)
	set(CMAKE_CXX_CLANG_TIDY "clang-tidy")
	message("-- Clang-tidy enabled")
endif()

add_subdirectory(cpu6502)
add_subdirectory(interpreter)
add_subdirectory(tests)
add_subdirectory(gui)

# Copy asm examples file to build folder
file(COPY examples/ DESTINATION examples)

