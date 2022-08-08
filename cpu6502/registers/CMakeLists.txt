set(CMAKE_CXX_STANDARD 20)
add_library(
        cpu6502_registers STATIC
        accumulator.cpp
        indexregisterx.cpp
        indexregistery.cpp
        processorstatus.cpp
        programcounter.cpp
        stackpointer.cpp
        registers.cpp
)
target_compile_options(cpu6502_registers PRIVATE ${CXX_COMPILER_FLAGS})
set_target_properties(cpu6502_registers PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(cpu6502_registers PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")