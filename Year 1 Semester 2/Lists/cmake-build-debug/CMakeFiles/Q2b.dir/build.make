# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.20

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
CMAKE_SOURCE_DIR = /Users/edenbar/CLionProjects/Y1S2Project3

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/edenbar/CLionProjects/Y1S2Project3/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/Q2b.dir/depend.make
# Include the progress variables for this target.
include CMakeFiles/Q2b.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Q2b.dir/flags.make

CMakeFiles/Q2b.dir/Q2b.c.o: CMakeFiles/Q2b.dir/flags.make
CMakeFiles/Q2b.dir/Q2b.c.o: ../Q2b.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/edenbar/CLionProjects/Y1S2Project3/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/Q2b.dir/Q2b.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/Q2b.dir/Q2b.c.o -c /Users/edenbar/CLionProjects/Y1S2Project3/Q2b.c

CMakeFiles/Q2b.dir/Q2b.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Q2b.dir/Q2b.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/edenbar/CLionProjects/Y1S2Project3/Q2b.c > CMakeFiles/Q2b.dir/Q2b.c.i

CMakeFiles/Q2b.dir/Q2b.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Q2b.dir/Q2b.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/edenbar/CLionProjects/Y1S2Project3/Q2b.c -o CMakeFiles/Q2b.dir/Q2b.c.s

# Object files for target Q2b
Q2b_OBJECTS = \
"CMakeFiles/Q2b.dir/Q2b.c.o"

# External object files for target Q2b
Q2b_EXTERNAL_OBJECTS =

Q2b: CMakeFiles/Q2b.dir/Q2b.c.o
Q2b: CMakeFiles/Q2b.dir/build.make
Q2b: CMakeFiles/Q2b.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/edenbar/CLionProjects/Y1S2Project3/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable Q2b"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Q2b.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Q2b.dir/build: Q2b
.PHONY : CMakeFiles/Q2b.dir/build

CMakeFiles/Q2b.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Q2b.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Q2b.dir/clean

CMakeFiles/Q2b.dir/depend:
	cd /Users/edenbar/CLionProjects/Y1S2Project3/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/edenbar/CLionProjects/Y1S2Project3 /Users/edenbar/CLionProjects/Y1S2Project3 /Users/edenbar/CLionProjects/Y1S2Project3/cmake-build-debug /Users/edenbar/CLionProjects/Y1S2Project3/cmake-build-debug /Users/edenbar/CLionProjects/Y1S2Project3/cmake-build-debug/CMakeFiles/Q2b.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Q2b.dir/depend

