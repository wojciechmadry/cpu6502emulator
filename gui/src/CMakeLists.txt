add_library(
    cpu6502_gui_lib STATIC
    gui_manager.cpp
)


target_compile_options(cpu6502_gui_lib PRIVATE  ${CXX_COMPILER_FLAGS})
target_include_directories(cpu6502_gui_lib PRIVATE "../cpu6502")
set_target_properties(cpu6502_gui_lib PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(cpu6502_gui_lib PRIVATE  ${GUI_LIBRARIES})
target_include_directories(cpu6502_gui_lib PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
