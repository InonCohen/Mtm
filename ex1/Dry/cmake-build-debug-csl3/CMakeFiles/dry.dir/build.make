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


# Produce verbose output by default.
VERBOSE = 1

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
CMAKE_COMMAND = /home/mtm/cmake-3.17.0-Linux-x86_64/bin/cmake

# The command to remove a file.
RM = /home/mtm/cmake-3.17.0-Linux-x86_64/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /tmp/tmp.YVaeKa3iS7/tmp/tmp.YVaeKa3iS7/dry

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /tmp/tmp.YVaeKa3iS7/tmp/tmp.YVaeKa3iS7/dry/cmake-build-debug-csl3

# Include any dependencies generated for this target.
include CMakeFiles/dry.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/dry.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/dry.dir/flags.make

CMakeFiles/dry.dir/dry.c.o: CMakeFiles/dry.dir/flags.make
CMakeFiles/dry.dir/dry.c.o: ../dry.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/tmp/tmp.YVaeKa3iS7/tmp/tmp.YVaeKa3iS7/dry/cmake-build-debug-csl3/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/dry.dir/dry.c.o"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/dry.dir/dry.c.o   -c /tmp/tmp.YVaeKa3iS7/tmp/tmp.YVaeKa3iS7/dry/dry.c

CMakeFiles/dry.dir/dry.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/dry.dir/dry.c.i"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /tmp/tmp.YVaeKa3iS7/tmp/tmp.YVaeKa3iS7/dry/dry.c > CMakeFiles/dry.dir/dry.c.i

CMakeFiles/dry.dir/dry.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/dry.dir/dry.c.s"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /tmp/tmp.YVaeKa3iS7/tmp/tmp.YVaeKa3iS7/dry/dry.c -o CMakeFiles/dry.dir/dry.c.s

# Object files for target dry
dry_OBJECTS = \
"CMakeFiles/dry.dir/dry.c.o"

# External object files for target dry
dry_EXTERNAL_OBJECTS =

dry: CMakeFiles/dry.dir/dry.c.o
dry: CMakeFiles/dry.dir/build.make
dry: CMakeFiles/dry.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/tmp/tmp.YVaeKa3iS7/tmp/tmp.YVaeKa3iS7/dry/cmake-build-debug-csl3/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable dry"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/dry.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/dry.dir/build: dry

.PHONY : CMakeFiles/dry.dir/build

CMakeFiles/dry.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/dry.dir/cmake_clean.cmake
.PHONY : CMakeFiles/dry.dir/clean

CMakeFiles/dry.dir/depend:
	cd /tmp/tmp.YVaeKa3iS7/tmp/tmp.YVaeKa3iS7/dry/cmake-build-debug-csl3 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /tmp/tmp.YVaeKa3iS7/tmp/tmp.YVaeKa3iS7/dry /tmp/tmp.YVaeKa3iS7/tmp/tmp.YVaeKa3iS7/dry /tmp/tmp.YVaeKa3iS7/tmp/tmp.YVaeKa3iS7/dry/cmake-build-debug-csl3 /tmp/tmp.YVaeKa3iS7/tmp/tmp.YVaeKa3iS7/dry/cmake-build-debug-csl3 /tmp/tmp.YVaeKa3iS7/tmp/tmp.YVaeKa3iS7/dry/cmake-build-debug-csl3/CMakeFiles/dry.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/dry.dir/depend
