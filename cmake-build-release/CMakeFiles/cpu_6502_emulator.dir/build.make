# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.19

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Disable VCS-based implicit rules.
% : %,v


# Disable VCS-based implicit rules.
% : RCS/%


# Disable VCS-based implicit rules.
% : RCS/%,v


# Disable VCS-based implicit rules.
% : SCCS/s.%


# Disable VCS-based implicit rules.
% : s.%


.SUFFIXES: .hpux_make_needs_suffix_list


# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "F:\CLion\CLion 2020.2.4\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "F:\CLion\CLion 2020.2.4\bin\cmake\win\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = F:\CPU6502\cpu-6502-emulator

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = F:\CPU6502\cpu-6502-emulator\cmake-build-release

# Include any dependencies generated for this target.
include CMakeFiles/cpu_6502_emulator.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/cpu_6502_emulator.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/cpu_6502_emulator.dir/flags.make

CMakeFiles/cpu_6502_emulator.dir/main.cpp.obj: CMakeFiles/cpu_6502_emulator.dir/flags.make
CMakeFiles/cpu_6502_emulator.dir/main.cpp.obj: CMakeFiles/cpu_6502_emulator.dir/includes_CXX.rsp
CMakeFiles/cpu_6502_emulator.dir/main.cpp.obj: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=F:\CPU6502\cpu-6502-emulator\cmake-build-release\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/cpu_6502_emulator.dir/main.cpp.obj"
	C:\msys64\mingw64\bin\clang++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\cpu_6502_emulator.dir\main.cpp.obj -c F:\CPU6502\cpu-6502-emulator\main.cpp

CMakeFiles/cpu_6502_emulator.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/cpu_6502_emulator.dir/main.cpp.i"
	C:\msys64\mingw64\bin\clang++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E F:\CPU6502\cpu-6502-emulator\main.cpp > CMakeFiles\cpu_6502_emulator.dir\main.cpp.i

CMakeFiles/cpu_6502_emulator.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/cpu_6502_emulator.dir/main.cpp.s"
	C:\msys64\mingw64\bin\clang++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S F:\CPU6502\cpu-6502-emulator\main.cpp -o CMakeFiles\cpu_6502_emulator.dir\main.cpp.s

# Object files for target cpu_6502_emulator
cpu_6502_emulator_OBJECTS = \
"CMakeFiles/cpu_6502_emulator.dir/main.cpp.obj"

# External object files for target cpu_6502_emulator
cpu_6502_emulator_EXTERNAL_OBJECTS =

cpu_6502_emulator.exe: CMakeFiles/cpu_6502_emulator.dir/main.cpp.obj
cpu_6502_emulator.exe: CMakeFiles/cpu_6502_emulator.dir/build.make
cpu_6502_emulator.exe: cpu6502/libcpu6502.a
cpu_6502_emulator.exe: tests/libcpu6502_tests.a
cpu_6502_emulator.exe: cpu6502/memory/libcpu6502_memory.a
cpu_6502_emulator.exe: cpu6502/registers/libcpu6502_registers.a
cpu_6502_emulator.exe: CMakeFiles/cpu_6502_emulator.dir/linklibs.rsp
cpu_6502_emulator.exe: CMakeFiles/cpu_6502_emulator.dir/objects1.rsp
cpu_6502_emulator.exe: CMakeFiles/cpu_6502_emulator.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=F:\CPU6502\cpu-6502-emulator\cmake-build-release\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable cpu_6502_emulator.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\cpu_6502_emulator.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/cpu_6502_emulator.dir/build: cpu_6502_emulator.exe

.PHONY : CMakeFiles/cpu_6502_emulator.dir/build

CMakeFiles/cpu_6502_emulator.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\cpu_6502_emulator.dir\cmake_clean.cmake
.PHONY : CMakeFiles/cpu_6502_emulator.dir/clean

CMakeFiles/cpu_6502_emulator.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" F:\CPU6502\cpu-6502-emulator F:\CPU6502\cpu-6502-emulator F:\CPU6502\cpu-6502-emulator\cmake-build-release F:\CPU6502\cpu-6502-emulator\cmake-build-release F:\CPU6502\cpu-6502-emulator\cmake-build-release\CMakeFiles\cpu_6502_emulator.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/cpu_6502_emulator.dir/depend

