set(CMAKE_CXX_STANDARD 20)
add_library(
        cpu6502_tests STATIC
        ALL_TEST.HPP
        register_test.hpp
        cpu_test.hpp
)
set_target_properties(cpu6502_tests PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(cpu6502_tests PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")