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
CMAKE_BINARY_DIR = F:\CPU6502\cpu-6502-emulator\cmake-build-debug

# Include any dependencies generated for this target.
include cpu6502/CMakeFiles/cpu6502_main.dir/depend.make

# Include the progress variables for this target.
include cpu6502/CMakeFiles/cpu6502_main.dir/progress.make

# Include the compile flags for this target's objects.
include cpu6502/CMakeFiles/cpu6502_main.dir/flags.make

cpu6502/CMakeFiles/cpu6502_main.dir/cpu/InstructionSet/LoadStoreOperations/LDA.cpp.obj: cpu6502/CMakeFiles/cpu6502_main.dir/flags.make
cpu6502/CMakeFiles/cpu6502_main.dir/cpu/InstructionSet/LoadStoreOperations/LDA.cpp.obj: cpu6502/CMakeFiles/cpu6502_main.dir/includes_CXX.rsp
cpu6502/CMakeFiles/cpu6502_main.dir/cpu/InstructionSet/LoadStoreOperations/LDA.cpp.obj: ../cpu6502/cpu/InstructionSet/LoadStoreOperations/LDA.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=F:\CPU6502\cpu-6502-emulator\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object cpu6502/CMakeFiles/cpu6502_main.dir/cpu/InstructionSet/LoadStoreOperations/LDA.cpp.obj"
	cd /d F:\CPU6502\cpu-6502-emulator\cmake-build-debug\cpu6502 && C:\msys64\mingw64\bin\clang++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\cpu6502_main.dir\cpu\InstructionSet\LoadStoreOperations\LDA.cpp.obj -c F:\CPU6502\cpu-6502-emulator\cpu6502\cpu\InstructionSet\LoadStoreOperations\LDA.cpp

cpu6502/CMakeFiles/cpu6502_main.dir/cpu/InstructionSet/LoadStoreOperations/LDA.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/cpu6502_main.dir/cpu/InstructionSet/LoadStoreOperations/LDA.cpp.i"
	cd /d F:\CPU6502\cpu-6502-emulator\cmake-build-debug\cpu6502 && C:\msys64\mingw64\bin\clang++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E F:\CPU6502\cpu-6502-emulator\cpu6502\cpu\InstructionSet\LoadStoreOperations\LDA.cpp > CMakeFiles\cpu6502_main.dir\cpu\InstructionSet\LoadStoreOperations\LDA.cpp.i

cpu6502/CMakeFiles/cpu6502_main.dir/cpu/InstructionSet/LoadStoreOperations/LDA.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/cpu6502_main.dir/cpu/InstructionSet/LoadStoreOperations/LDA.cpp.s"
	cd /d F:\CPU6502\cpu-6502-emulator\cmake-build-debug\cpu6502 && C:\msys64\mingw64\bin\clang++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S F:\CPU6502\cpu-6502-emulator\cpu6502\cpu\InstructionSet\LoadStoreOperations\LDA.cpp -o CMakeFiles\cpu6502_main.dir\cpu\InstructionSet\LoadStoreOperations\LDA.cpp.s

cpu6502/CMakeFiles/cpu6502_main.dir/cpu/InstructionSet/JumpsCalls/JSR.cpp.obj: cpu6502/CMakeFiles/cpu6502_main.dir/flags.make
cpu6502/CMakeFiles/cpu6502_main.dir/cpu/InstructionSet/JumpsCalls/JSR.cpp.obj: cpu6502/CMakeFiles/cpu6502_main.dir/includes_CXX.rsp
cpu6502/CMakeFiles/cpu6502_main.dir/cpu/InstructionSet/JumpsCalls/JSR.cpp.obj: ../cpu6502/cpu/InstructionSet/JumpsCalls/JSR.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=F:\CPU6502\cpu-6502-emulator\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object cpu6502/CMakeFiles/cpu6502_main.dir/cpu/InstructionSet/JumpsCalls/JSR.cpp.obj"
	cd /d F:\CPU6502\cpu-6502-emulator\cmake-build-debug\cpu6502 && C:\msys64\mingw64\bin\clang++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\cpu6502_main.dir\cpu\InstructionSet\JumpsCalls\JSR.cpp.obj -c F:\CPU6502\cpu-6502-emulator\cpu6502\cpu\InstructionSet\JumpsCalls\JSR.cpp

cpu6502/CMakeFiles/cpu6502_main.dir/cpu/InstructionSet/JumpsCalls/JSR.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/cpu6502_main.dir/cpu/InstructionSet/JumpsCalls/JSR.cpp.i"
	cd /d F:\CPU6502\cpu-6502-emulator\cmake-build-debug\cpu6502 && C:\msys64\mingw64\bin\clang++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E F:\CPU6502\cpu-6502-emulator\cpu6502\cpu\InstructionSet\JumpsCalls\JSR.cpp > CMakeFiles\cpu6502_main.dir\cpu\InstructionSet\JumpsCalls\JSR.cpp.i

cpu6502/CMakeFiles/cpu6502_main.dir/cpu/InstructionSet/JumpsCalls/JSR.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/cpu6502_main.dir/cpu/InstructionSet/JumpsCalls/JSR.cpp.s"
	cd /d F:\CPU6502\cpu-6502-emulator\cmake-build-debug\cpu6502 && C:\msys64\mingw64\bin\clang++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S F:\CPU6502\cpu-6502-emulator\cpu6502\cpu\InstructionSet\JumpsCalls\JSR.cpp -o CMakeFiles\cpu6502_main.dir\cpu\InstructionSet\JumpsCalls\JSR.cpp.s

cpu6502/CMakeFiles/cpu6502_main.dir/cpu/InstructionSet/JumpsCalls/JMP.cpp.obj: cpu6502/CMakeFiles/cpu6502_main.dir/flags.make
cpu6502/CMakeFiles/cpu6502_main.dir/cpu/InstructionSet/JumpsCalls/JMP.cpp.obj: cpu6502/CMakeFiles/cpu6502_main.dir/includes_CXX.rsp
cpu6502/CMakeFiles/cpu6502_main.dir/cpu/InstructionSet/JumpsCalls/JMP.cpp.obj: ../cpu6502/cpu/InstructionSet/JumpsCalls/JMP.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=F:\CPU6502\cpu-6502-emulator\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object cpu6502/CMakeFiles/cpu6502_main.dir/cpu/InstructionSet/JumpsCalls/JMP.cpp.obj"
	cd /d F:\CPU6502\cpu-6502-emulator\cmake-build-debug\cpu6502 && C:\msys64\mingw64\bin\clang++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\cpu6502_main.dir\cpu\InstructionSet\JumpsCalls\JMP.cpp.obj -c F:\CPU6502\cpu-6502-emulator\cpu6502\cpu\InstructionSet\JumpsCalls\JMP.cpp

cpu6502/CMakeFiles/cpu6502_main.dir/cpu/InstructionSet/JumpsCalls/JMP.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/cpu6502_main.dir/cpu/InstructionSet/JumpsCalls/JMP.cpp.i"
	cd /d F:\CPU6502\cpu-6502-emulator\cmake-build-debug\cpu6502 && C:\msys64\mingw64\bin\clang++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E F:\CPU6502\cpu-6502-emulator\cpu6502\cpu\InstructionSet\JumpsCalls\JMP.cpp > CMakeFiles\cpu6502_main.dir\cpu\InstructionSet\JumpsCalls\JMP.cpp.i

cpu6502/CMakeFiles/cpu6502_main.dir/cpu/InstructionSet/JumpsCalls/JMP.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/cpu6502_main.dir/cpu/InstructionSet/JumpsCalls/JMP.cpp.s"
	cd /d F:\CPU6502\cpu-6502-emulator\cmake-build-debug\cpu6502 && C:\msys64\mingw64\bin\clang++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S F:\CPU6502\cpu-6502-emulator\cpu6502\cpu\InstructionSet\JumpsCalls\JMP.cpp -o CMakeFiles\cpu6502_main.dir\cpu\InstructionSet\JumpsCalls\JMP.cpp.s

cpu6502/CMakeFiles/cpu6502_main.dir/cpu/InstructionSet/JumpsCalls/RTS.cpp.obj: cpu6502/CMakeFiles/cpu6502_main.dir/flags.make
cpu6502/CMakeFiles/cpu6502_main.dir/cpu/InstructionSet/JumpsCalls/RTS.cpp.obj: cpu6502/CMakeFiles/cpu6502_main.dir/includes_CXX.rsp
cpu6502/CMakeFiles/cpu6502_main.dir/cpu/InstructionSet/JumpsCalls/RTS.cpp.obj: ../cpu6502/cpu/InstructionSet/JumpsCalls/RTS.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=F:\CPU6502\cpu-6502-emulator\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object cpu6502/CMakeFiles/cpu6502_main.dir/cpu/InstructionSet/JumpsCalls/RTS.cpp.obj"
	cd /d F:\CPU6502\cpu-6502-emulator\cmake-build-debug\cpu6502 && C:\msys64\mingw64\bin\clang++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\cpu6502_main.dir\cpu\InstructionSet\JumpsCalls\RTS.cpp.obj -c F:\CPU6502\cpu-6502-emulator\cpu6502\cpu\InstructionSet\JumpsCalls\RTS.cpp

cpu6502/CMakeFiles/cpu6502_main.dir/cpu/InstructionSet/JumpsCalls/RTS.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/cpu6502_main.dir/cpu/InstructionSet/JumpsCalls/RTS.cpp.i"
	cd /d F:\CPU6502\cpu-6502-emulator\cmake-build-debug\cpu6502 && C:\msys64\mingw64\bin\clang++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E F:\CPU6502\cpu-6502-emulator\cpu6502\cpu\InstructionSet\JumpsCalls\RTS.cpp > CMakeFiles\cpu6502_main.dir\cpu\InstructionSet\JumpsCalls\RTS.cpp.i

cpu6502/CMakeFiles/cpu6502_main.dir/cpu/InstructionSet/JumpsCalls/RTS.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/cpu6502_main.dir/cpu/InstructionSet/JumpsCalls/RTS.cpp.s"
	cd /d F:\CPU6502\cpu-6502-emulator\cmake-build-debug\cpu6502 && C:\msys64\mingw64\bin\clang++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S F:\CPU6502\cpu-6502-emulator\cpu6502\cpu\InstructionSet\JumpsCalls\RTS.cpp -o CMakeFiles\cpu6502_main.dir\cpu\InstructionSet\JumpsCalls\RTS.cpp.s

cpu6502/CMakeFiles/cpu6502_main.dir/cpu/WriteRead/read.cpp.obj: cpu6502/CMakeFiles/cpu6502_main.dir/flags.make
cpu6502/CMakeFiles/cpu6502_main.dir/cpu/WriteRead/read.cpp.obj: cpu6502/CMakeFiles/cpu6502_main.dir/includes_CXX.rsp
cpu6502/CMakeFiles/cpu6502_main.dir/cpu/WriteRead/read.cpp.obj: ../cpu6502/cpu/WriteRead/read.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=F:\CPU6502\cpu-6502-emulator\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object cpu6502/CMakeFiles/cpu6502_main.dir/cpu/WriteRead/read.cpp.obj"
	cd /d F:\CPU6502\cpu-6502-emulator\cmake-build-debug\cpu6502 && C:\msys64\mingw64\bin\clang++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\cpu6502_main.dir\cpu\WriteRead\read.cpp.obj -c F:\CPU6502\cpu-6502-emulator\cpu6502\cpu\WriteRead\read.cpp

cpu6502/CMakeFiles/cpu6502_main.dir/cpu/WriteRead/read.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/cpu6502_main.dir/cpu/WriteRead/read.cpp.i"
	cd /d F:\CPU6502\cpu-6502-emulator\cmake-build-debug\cpu6502 && C:\msys64\mingw64\bin\clang++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E F:\CPU6502\cpu-6502-emulator\cpu6502\cpu\WriteRead\read.cpp > CMakeFiles\cpu6502_main.dir\cpu\WriteRead\read.cpp.i

cpu6502/CMakeFiles/cpu6502_main.dir/cpu/WriteRead/read.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/cpu6502_main.dir/cpu/WriteRead/read.cpp.s"
	cd /d F:\CPU6502\cpu-6502-emulator\cmake-build-debug\cpu6502 && C:\msys64\mingw64\bin\clang++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S F:\CPU6502\cpu-6502-emulator\cpu6502\cpu\WriteRead\read.cpp -o CMakeFiles\cpu6502_main.dir\cpu\WriteRead\read.cpp.s

cpu6502/CMakeFiles/cpu6502_main.dir/cpu/WriteRead/write.cpp.obj: cpu6502/CMakeFiles/cpu6502_main.dir/flags.make
cpu6502/CMakeFiles/cpu6502_main.dir/cpu/WriteRead/write.cpp.obj: cpu6502/CMakeFiles/cpu6502_main.dir/includes_CXX.rsp
cpu6502/CMakeFiles/cpu6502_main.dir/cpu/WriteRead/write.cpp.obj: ../cpu6502/cpu/WriteRead/write.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=F:\CPU6502\cpu-6502-emulator\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object cpu6502/CMakeFiles/cpu6502_main.dir/cpu/WriteRead/write.cpp.obj"
	cd /d F:\CPU6502\cpu-6502-emulator\cmake-build-debug\cpu6502 && C:\msys64\mingw64\bin\clang++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\cpu6502_main.dir\cpu\WriteRead\write.cpp.obj -c F:\CPU6502\cpu-6502-emulator\cpu6502\cpu\WriteRead\write.cpp

cpu6502/CMakeFiles/cpu6502_main.dir/cpu/WriteRead/write.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/cpu6502_main.dir/cpu/WriteRead/write.cpp.i"
	cd /d F:\CPU6502\cpu-6502-emulator\cmake-build-debug\cpu6502 && C:\msys64\mingw64\bin\clang++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E F:\CPU6502\cpu-6502-emulator\cpu6502\cpu\WriteRead\write.cpp > CMakeFiles\cpu6502_main.dir\cpu\WriteRead\write.cpp.i

cpu6502/CMakeFiles/cpu6502_main.dir/cpu/WriteRead/write.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/cpu6502_main.dir/cpu/WriteRead/write.cpp.s"
	cd /d F:\CPU6502\cpu-6502-emulator\cmake-build-debug\cpu6502 && C:\msys64\mingw64\bin\clang++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S F:\CPU6502\cpu-6502-emulator\cpu6502\cpu\WriteRead\write.cpp -o CMakeFiles\cpu6502_main.dir\cpu\WriteRead\write.cpp.s

cpu6502/CMakeFiles/cpu6502_main.dir/cpu/execute_instruction.cpp.obj: cpu6502/CMakeFiles/cpu6502_main.dir/flags.make
cpu6502/CMakeFiles/cpu6502_main.dir/cpu/execute_instruction.cpp.obj: cpu6502/CMakeFiles/cpu6502_main.dir/includes_CXX.rsp
cpu6502/CMakeFiles/cpu6502_main.dir/cpu/execute_instruction.cpp.obj: ../cpu6502/cpu/execute_instruction.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=F:\CPU6502\cpu-6502-emulator\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object cpu6502/CMakeFiles/cpu6502_main.dir/cpu/execute_instruction.cpp.obj"
	cd /d F:\CPU6502\cpu-6502-emulator\cmake-build-debug\cpu6502 && C:\msys64\mingw64\bin\clang++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\cpu6502_main.dir\cpu\execute_instruction.cpp.obj -c F:\CPU6502\cpu-6502-emulator\cpu6502\cpu\execute_instruction.cpp

cpu6502/CMakeFiles/cpu6502_main.dir/cpu/execute_instruction.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/cpu6502_main.dir/cpu/execute_instruction.cpp.i"
	cd /d F:\CPU6502\cpu-6502-emulator\cmake-build-debug\cpu6502 && C:\msys64\mingw64\bin\clang++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E F:\CPU6502\cpu-6502-emulator\cpu6502\cpu\execute_instruction.cpp > CMakeFiles\cpu6502_main.dir\cpu\execute_instruction.cpp.i

cpu6502/CMakeFiles/cpu6502_main.dir/cpu/execute_instruction.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/cpu6502_main.dir/cpu/execute_instruction.cpp.s"
	cd /d F:\CPU6502\cpu-6502-emulator\cmake-build-debug\cpu6502 && C:\msys64\mingw64\bin\clang++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S F:\CPU6502\cpu-6502-emulator\cpu6502\cpu\execute_instruction.cpp -o CMakeFiles\cpu6502_main.dir\cpu\execute_instruction.cpp.s

# Object files for target cpu6502_main
cpu6502_main_OBJECTS = \
"CMakeFiles/cpu6502_main.dir/cpu/InstructionSet/LoadStoreOperations/LDA.cpp.obj" \
"CMakeFiles/cpu6502_main.dir/cpu/InstructionSet/JumpsCalls/JSR.cpp.obj" \
"CMakeFiles/cpu6502_main.dir/cpu/InstructionSet/JumpsCalls/JMP.cpp.obj" \
"CMakeFiles/cpu6502_main.dir/cpu/InstructionSet/JumpsCalls/RTS.cpp.obj" \
"CMakeFiles/cpu6502_main.dir/cpu/WriteRead/read.cpp.obj" \
"CMakeFiles/cpu6502_main.dir/cpu/WriteRead/write.cpp.obj" \
"CMakeFiles/cpu6502_main.dir/cpu/execute_instruction.cpp.obj"

# External object files for target cpu6502_main
cpu6502_main_EXTERNAL_OBJECTS =

cpu6502/libcpu6502_main.a: cpu6502/CMakeFiles/cpu6502_main.dir/cpu/InstructionSet/LoadStoreOperations/LDA.cpp.obj
cpu6502/libcpu6502_main.a: cpu6502/CMakeFiles/cpu6502_main.dir/cpu/InstructionSet/JumpsCalls/JSR.cpp.obj
cpu6502/libcpu6502_main.a: cpu6502/CMakeFiles/cpu6502_main.dir/cpu/InstructionSet/JumpsCalls/JMP.cpp.obj
cpu6502/libcpu6502_main.a: cpu6502/CMakeFiles/cpu6502_main.dir/cpu/InstructionSet/JumpsCalls/RTS.cpp.obj
cpu6502/libcpu6502_main.a: cpu6502/CMakeFiles/cpu6502_main.dir/cpu/WriteRead/read.cpp.obj
cpu6502/libcpu6502_main.a: cpu6502/CMakeFiles/cpu6502_main.dir/cpu/WriteRead/write.cpp.obj
cpu6502/libcpu6502_main.a: cpu6502/CMakeFiles/cpu6502_main.dir/cpu/execute_instruction.cpp.obj
cpu6502/libcpu6502_main.a: cpu6502/CMakeFiles/cpu6502_main.dir/build.make
cpu6502/libcpu6502_main.a: cpu6502/CMakeFiles/cpu6502_main.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=F:\CPU6502\cpu-6502-emulator\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Linking CXX static library libcpu6502_main.a"
	cd /d F:\CPU6502\cpu-6502-emulator\cmake-build-debug\cpu6502 && $(CMAKE_COMMAND) -P CMakeFiles\cpu6502_main.dir\cmake_clean_target.cmake
	cd /d F:\CPU6502\cpu-6502-emulator\cmake-build-debug\cpu6502 && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\cpu6502_main.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
cpu6502/CMakeFiles/cpu6502_main.dir/build: cpu6502/libcpu6502_main.a

.PHONY : cpu6502/CMakeFiles/cpu6502_main.dir/build

cpu6502/CMakeFiles/cpu6502_main.dir/clean:
	cd /d F:\CPU6502\cpu-6502-emulator\cmake-build-debug\cpu6502 && $(CMAKE_COMMAND) -P CMakeFiles\cpu6502_main.dir\cmake_clean.cmake
.PHONY : cpu6502/CMakeFiles/cpu6502_main.dir/clean

cpu6502/CMakeFiles/cpu6502_main.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" F:\CPU6502\cpu-6502-emulator F:\CPU6502\cpu-6502-emulator\cpu6502 F:\CPU6502\cpu-6502-emulator\cmake-build-debug F:\CPU6502\cpu-6502-emulator\cmake-build-debug\cpu6502 F:\CPU6502\cpu-6502-emulator\cmake-build-debug\cpu6502\CMakeFiles\cpu6502_main.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : cpu6502/CMakeFiles/cpu6502_main.dir/depend

