# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.17

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

# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /Users/dpatrica/Desktop/CLion.app/Contents/bin/cmake/mac/bin/cmake

# The command to remove a file.
RM = /Users/dpatrica/Desktop/CLion.app/Contents/bin/cmake/mac/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/dpatrica/CLionProjects/MiniHell

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/dpatrica/CLionProjects/MiniHell/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/MiniHell.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/MiniHell.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/MiniHell.dir/flags.make

CMakeFiles/MiniHell.dir/main.c.o: CMakeFiles/MiniHell.dir/flags.make
CMakeFiles/MiniHell.dir/main.c.o: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/dpatrica/CLionProjects/MiniHell/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/MiniHell.dir/main.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/MiniHell.dir/main.c.o   -c /Users/dpatrica/CLionProjects/MiniHell/main.c

CMakeFiles/MiniHell.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/MiniHell.dir/main.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/dpatrica/CLionProjects/MiniHell/main.c > CMakeFiles/MiniHell.dir/main.c.i

CMakeFiles/MiniHell.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/MiniHell.dir/main.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/dpatrica/CLionProjects/MiniHell/main.c -o CMakeFiles/MiniHell.dir/main.c.s

# Object files for target MiniHell
MiniHell_OBJECTS = \
"CMakeFiles/MiniHell.dir/main.c.o"

# External object files for target MiniHell
MiniHell_EXTERNAL_OBJECTS =

MiniHell: CMakeFiles/MiniHell.dir/main.c.o
MiniHell: CMakeFiles/MiniHell.dir/build.make
MiniHell: ../libft/libft.a
MiniHell: CMakeFiles/MiniHell.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/dpatrica/CLionProjects/MiniHell/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable MiniHell"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/MiniHell.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/MiniHell.dir/build: MiniHell

.PHONY : CMakeFiles/MiniHell.dir/build

CMakeFiles/MiniHell.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/MiniHell.dir/cmake_clean.cmake
.PHONY : CMakeFiles/MiniHell.dir/clean

CMakeFiles/MiniHell.dir/depend:
	cd /Users/dpatrica/CLionProjects/MiniHell/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/dpatrica/CLionProjects/MiniHell /Users/dpatrica/CLionProjects/MiniHell /Users/dpatrica/CLionProjects/MiniHell/cmake-build-debug /Users/dpatrica/CLionProjects/MiniHell/cmake-build-debug /Users/dpatrica/CLionProjects/MiniHell/cmake-build-debug/CMakeFiles/MiniHell.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/MiniHell.dir/depend

