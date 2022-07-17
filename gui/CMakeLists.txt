set(CMAKE_CXX_STANDARD 20)
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
#add_library(
#        cpu6502_gui STATIC
#)

#target_compile_options(cpu6502_gui PRIVATE  ${CXX_COMPILER_FLAGS})

#target_include_directories(cpu6502_gui PRIVATE "../cpu6502")
#set_target_properties(cpu6502_gui PROPERTIES LINKER_LANGUAGE CXX)
#target_link_libraries(cpu6502_gui PRIVATE cpu6502 fmt)
#target_include_directories(cpu6502_gui PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")

find_package(Qt6 CONFIG REQUIRED COMPONENTS Widgets)

add_executable(cpu_6502_emulator 
    src/gui_main.cpp)

target_include_directories(cpu_6502_emulator PRIVATE "../cpu6502")
target_include_directories(cpu_6502_emulator PRIVATE "../interpreter")

target_link_libraries(cpu_6502_emulator PUBLIC cpu6502 fmt cpu6502_tests cpu6502_interpreter Qt6::Widgets)#cpu6502_gui

target_compile_options(cpu_6502_emulator PRIVATE ${CXX_COMPILER_FLAGS})

file(COPY images DESTINATION ${CMAKE_BINARY_DIR})