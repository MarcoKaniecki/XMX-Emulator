# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/mk/Desktop/XMX-Emulator

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/mk/Desktop/XMX-Emulator/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/XMX_Emulator.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/XMX_Emulator.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/XMX_Emulator.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/XMX_Emulator.dir/flags.make

CMakeFiles/XMX_Emulator.dir/main.c.o: CMakeFiles/XMX_Emulator.dir/flags.make
CMakeFiles/XMX_Emulator.dir/main.c.o: ../main.c
CMakeFiles/XMX_Emulator.dir/main.c.o: CMakeFiles/XMX_Emulator.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/mk/Desktop/XMX-Emulator/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/XMX_Emulator.dir/main.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/XMX_Emulator.dir/main.c.o -MF CMakeFiles/XMX_Emulator.dir/main.c.o.d -o CMakeFiles/XMX_Emulator.dir/main.c.o -c /Users/mk/Desktop/XMX-Emulator/main.c

CMakeFiles/XMX_Emulator.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/XMX_Emulator.dir/main.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/mk/Desktop/XMX-Emulator/main.c > CMakeFiles/XMX_Emulator.dir/main.c.i

CMakeFiles/XMX_Emulator.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/XMX_Emulator.dir/main.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/mk/Desktop/XMX-Emulator/main.c -o CMakeFiles/XMX_Emulator.dir/main.c.s

CMakeFiles/XMX_Emulator.dir/loader.c.o: CMakeFiles/XMX_Emulator.dir/flags.make
CMakeFiles/XMX_Emulator.dir/loader.c.o: ../loader.c
CMakeFiles/XMX_Emulator.dir/loader.c.o: CMakeFiles/XMX_Emulator.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/mk/Desktop/XMX-Emulator/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/XMX_Emulator.dir/loader.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/XMX_Emulator.dir/loader.c.o -MF CMakeFiles/XMX_Emulator.dir/loader.c.o.d -o CMakeFiles/XMX_Emulator.dir/loader.c.o -c /Users/mk/Desktop/XMX-Emulator/loader.c

CMakeFiles/XMX_Emulator.dir/loader.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/XMX_Emulator.dir/loader.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/mk/Desktop/XMX-Emulator/loader.c > CMakeFiles/XMX_Emulator.dir/loader.c.i

CMakeFiles/XMX_Emulator.dir/loader.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/XMX_Emulator.dir/loader.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/mk/Desktop/XMX-Emulator/loader.c -o CMakeFiles/XMX_Emulator.dir/loader.c.s

CMakeFiles/XMX_Emulator.dir/bus.c.o: CMakeFiles/XMX_Emulator.dir/flags.make
CMakeFiles/XMX_Emulator.dir/bus.c.o: ../bus.c
CMakeFiles/XMX_Emulator.dir/bus.c.o: CMakeFiles/XMX_Emulator.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/mk/Desktop/XMX-Emulator/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/XMX_Emulator.dir/bus.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/XMX_Emulator.dir/bus.c.o -MF CMakeFiles/XMX_Emulator.dir/bus.c.o.d -o CMakeFiles/XMX_Emulator.dir/bus.c.o -c /Users/mk/Desktop/XMX-Emulator/bus.c

CMakeFiles/XMX_Emulator.dir/bus.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/XMX_Emulator.dir/bus.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/mk/Desktop/XMX-Emulator/bus.c > CMakeFiles/XMX_Emulator.dir/bus.c.i

CMakeFiles/XMX_Emulator.dir/bus.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/XMX_Emulator.dir/bus.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/mk/Desktop/XMX-Emulator/bus.c -o CMakeFiles/XMX_Emulator.dir/bus.c.s

CMakeFiles/XMX_Emulator.dir/fetch.c.o: CMakeFiles/XMX_Emulator.dir/flags.make
CMakeFiles/XMX_Emulator.dir/fetch.c.o: ../fetch.c
CMakeFiles/XMX_Emulator.dir/fetch.c.o: CMakeFiles/XMX_Emulator.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/mk/Desktop/XMX-Emulator/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/XMX_Emulator.dir/fetch.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/XMX_Emulator.dir/fetch.c.o -MF CMakeFiles/XMX_Emulator.dir/fetch.c.o.d -o CMakeFiles/XMX_Emulator.dir/fetch.c.o -c /Users/mk/Desktop/XMX-Emulator/fetch.c

CMakeFiles/XMX_Emulator.dir/fetch.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/XMX_Emulator.dir/fetch.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/mk/Desktop/XMX-Emulator/fetch.c > CMakeFiles/XMX_Emulator.dir/fetch.c.i

CMakeFiles/XMX_Emulator.dir/fetch.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/XMX_Emulator.dir/fetch.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/mk/Desktop/XMX-Emulator/fetch.c -o CMakeFiles/XMX_Emulator.dir/fetch.c.s

CMakeFiles/XMX_Emulator.dir/decoder.c.o: CMakeFiles/XMX_Emulator.dir/flags.make
CMakeFiles/XMX_Emulator.dir/decoder.c.o: ../decoder.c
CMakeFiles/XMX_Emulator.dir/decoder.c.o: CMakeFiles/XMX_Emulator.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/mk/Desktop/XMX-Emulator/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object CMakeFiles/XMX_Emulator.dir/decoder.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/XMX_Emulator.dir/decoder.c.o -MF CMakeFiles/XMX_Emulator.dir/decoder.c.o.d -o CMakeFiles/XMX_Emulator.dir/decoder.c.o -c /Users/mk/Desktop/XMX-Emulator/decoder.c

CMakeFiles/XMX_Emulator.dir/decoder.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/XMX_Emulator.dir/decoder.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/mk/Desktop/XMX-Emulator/decoder.c > CMakeFiles/XMX_Emulator.dir/decoder.c.i

CMakeFiles/XMX_Emulator.dir/decoder.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/XMX_Emulator.dir/decoder.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/mk/Desktop/XMX-Emulator/decoder.c -o CMakeFiles/XMX_Emulator.dir/decoder.c.s

CMakeFiles/XMX_Emulator.dir/register_file.c.o: CMakeFiles/XMX_Emulator.dir/flags.make
CMakeFiles/XMX_Emulator.dir/register_file.c.o: ../register_file.c
CMakeFiles/XMX_Emulator.dir/register_file.c.o: CMakeFiles/XMX_Emulator.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/mk/Desktop/XMX-Emulator/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building C object CMakeFiles/XMX_Emulator.dir/register_file.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/XMX_Emulator.dir/register_file.c.o -MF CMakeFiles/XMX_Emulator.dir/register_file.c.o.d -o CMakeFiles/XMX_Emulator.dir/register_file.c.o -c /Users/mk/Desktop/XMX-Emulator/register_file.c

CMakeFiles/XMX_Emulator.dir/register_file.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/XMX_Emulator.dir/register_file.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/mk/Desktop/XMX-Emulator/register_file.c > CMakeFiles/XMX_Emulator.dir/register_file.c.i

CMakeFiles/XMX_Emulator.dir/register_file.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/XMX_Emulator.dir/register_file.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/mk/Desktop/XMX-Emulator/register_file.c -o CMakeFiles/XMX_Emulator.dir/register_file.c.s

CMakeFiles/XMX_Emulator.dir/execute.c.o: CMakeFiles/XMX_Emulator.dir/flags.make
CMakeFiles/XMX_Emulator.dir/execute.c.o: ../execute.c
CMakeFiles/XMX_Emulator.dir/execute.c.o: CMakeFiles/XMX_Emulator.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/mk/Desktop/XMX-Emulator/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building C object CMakeFiles/XMX_Emulator.dir/execute.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/XMX_Emulator.dir/execute.c.o -MF CMakeFiles/XMX_Emulator.dir/execute.c.o.d -o CMakeFiles/XMX_Emulator.dir/execute.c.o -c /Users/mk/Desktop/XMX-Emulator/execute.c

CMakeFiles/XMX_Emulator.dir/execute.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/XMX_Emulator.dir/execute.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/mk/Desktop/XMX-Emulator/execute.c > CMakeFiles/XMX_Emulator.dir/execute.c.i

CMakeFiles/XMX_Emulator.dir/execute.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/XMX_Emulator.dir/execute.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/mk/Desktop/XMX-Emulator/execute.c -o CMakeFiles/XMX_Emulator.dir/execute.c.s

CMakeFiles/XMX_Emulator.dir/psw.c.o: CMakeFiles/XMX_Emulator.dir/flags.make
CMakeFiles/XMX_Emulator.dir/psw.c.o: ../psw.c
CMakeFiles/XMX_Emulator.dir/psw.c.o: CMakeFiles/XMX_Emulator.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/mk/Desktop/XMX-Emulator/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building C object CMakeFiles/XMX_Emulator.dir/psw.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/XMX_Emulator.dir/psw.c.o -MF CMakeFiles/XMX_Emulator.dir/psw.c.o.d -o CMakeFiles/XMX_Emulator.dir/psw.c.o -c /Users/mk/Desktop/XMX-Emulator/psw.c

CMakeFiles/XMX_Emulator.dir/psw.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/XMX_Emulator.dir/psw.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/mk/Desktop/XMX-Emulator/psw.c > CMakeFiles/XMX_Emulator.dir/psw.c.i

CMakeFiles/XMX_Emulator.dir/psw.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/XMX_Emulator.dir/psw.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/mk/Desktop/XMX-Emulator/psw.c -o CMakeFiles/XMX_Emulator.dir/psw.c.s

CMakeFiles/XMX_Emulator.dir/others.c.o: CMakeFiles/XMX_Emulator.dir/flags.make
CMakeFiles/XMX_Emulator.dir/others.c.o: ../others.c
CMakeFiles/XMX_Emulator.dir/others.c.o: CMakeFiles/XMX_Emulator.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/mk/Desktop/XMX-Emulator/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building C object CMakeFiles/XMX_Emulator.dir/others.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/XMX_Emulator.dir/others.c.o -MF CMakeFiles/XMX_Emulator.dir/others.c.o.d -o CMakeFiles/XMX_Emulator.dir/others.c.o -c /Users/mk/Desktop/XMX-Emulator/others.c

CMakeFiles/XMX_Emulator.dir/others.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/XMX_Emulator.dir/others.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/mk/Desktop/XMX-Emulator/others.c > CMakeFiles/XMX_Emulator.dir/others.c.i

CMakeFiles/XMX_Emulator.dir/others.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/XMX_Emulator.dir/others.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/mk/Desktop/XMX-Emulator/others.c -o CMakeFiles/XMX_Emulator.dir/others.c.s

# Object files for target XMX_Emulator
XMX_Emulator_OBJECTS = \
"CMakeFiles/XMX_Emulator.dir/main.c.o" \
"CMakeFiles/XMX_Emulator.dir/loader.c.o" \
"CMakeFiles/XMX_Emulator.dir/bus.c.o" \
"CMakeFiles/XMX_Emulator.dir/fetch.c.o" \
"CMakeFiles/XMX_Emulator.dir/decoder.c.o" \
"CMakeFiles/XMX_Emulator.dir/register_file.c.o" \
"CMakeFiles/XMX_Emulator.dir/execute.c.o" \
"CMakeFiles/XMX_Emulator.dir/psw.c.o" \
"CMakeFiles/XMX_Emulator.dir/others.c.o"

# External object files for target XMX_Emulator
XMX_Emulator_EXTERNAL_OBJECTS =

XMX_Emulator: CMakeFiles/XMX_Emulator.dir/main.c.o
XMX_Emulator: CMakeFiles/XMX_Emulator.dir/loader.c.o
XMX_Emulator: CMakeFiles/XMX_Emulator.dir/bus.c.o
XMX_Emulator: CMakeFiles/XMX_Emulator.dir/fetch.c.o
XMX_Emulator: CMakeFiles/XMX_Emulator.dir/decoder.c.o
XMX_Emulator: CMakeFiles/XMX_Emulator.dir/register_file.c.o
XMX_Emulator: CMakeFiles/XMX_Emulator.dir/execute.c.o
XMX_Emulator: CMakeFiles/XMX_Emulator.dir/psw.c.o
XMX_Emulator: CMakeFiles/XMX_Emulator.dir/others.c.o
XMX_Emulator: CMakeFiles/XMX_Emulator.dir/build.make
XMX_Emulator: CMakeFiles/XMX_Emulator.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/mk/Desktop/XMX-Emulator/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Linking C executable XMX_Emulator"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/XMX_Emulator.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/XMX_Emulator.dir/build: XMX_Emulator
.PHONY : CMakeFiles/XMX_Emulator.dir/build

CMakeFiles/XMX_Emulator.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/XMX_Emulator.dir/cmake_clean.cmake
.PHONY : CMakeFiles/XMX_Emulator.dir/clean

CMakeFiles/XMX_Emulator.dir/depend:
	cd /Users/mk/Desktop/XMX-Emulator/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/mk/Desktop/XMX-Emulator /Users/mk/Desktop/XMX-Emulator /Users/mk/Desktop/XMX-Emulator/cmake-build-debug /Users/mk/Desktop/XMX-Emulator/cmake-build-debug /Users/mk/Desktop/XMX-Emulator/cmake-build-debug/CMakeFiles/XMX_Emulator.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/XMX_Emulator.dir/depend

