set(CMAKE_CXX_STANDARD 20)
add_library(
        cpu6502_registers STATIC
        registers.hpp
        accumulator.hpp
        indexregisterx.hpp
        indexregistery.hpp
        processorstatus.hpp
        programcounter.hpp
        stackpointer.hpp
        ../required.hpp
)
set_target_properties(cpu6502_registers PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(cpu6502_registers PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")