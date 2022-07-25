set(CMAKE_CXX_STANDARD 20)
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

find_package(Qt6 CONFIG REQUIRED COMPONENTS Widgets)
set(GUI_LIBRARIES cpu6502 fmt cpu6502_tests cpu6502_interpreter Qt6::Widgets)

include_directories(include)
include_directories(cpu_6502_gui PRIVATE "../cpu6502")
include_directories(cpu_6502_gui PRIVATE "../interpreter")
add_subdirectory(src)

add_executable(cpu_6502_gui 
    src/gui_main.cpp)


target_link_libraries(cpu_6502_gui PUBLIC ${GUI_LIBRARIES} cpu6502_gui_lib)
target_compile_options(cpu_6502_gui PRIVATE ${CXX_COMPILER_FLAGS})

file(COPY images DESTINATION ${CMAKE_BINARY_DIR})