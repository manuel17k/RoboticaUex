# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/jorge/robocomp/components/supervisor

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/jorge/robocomp/components/supervisor

# Utility rule file for supervisor_autogen.

# Include the progress variables for this target.
include src/CMakeFiles/supervisor_autogen.dir/progress.make

src/CMakeFiles/supervisor_autogen:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/jorge/robocomp/components/supervisor/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Automatic MOC and UIC for target supervisor"
	cd /home/jorge/robocomp/components/supervisor/src && /usr/bin/cmake -E cmake_autogen /home/jorge/robocomp/components/supervisor/src/CMakeFiles/supervisor_autogen.dir ""

supervisor_autogen: src/CMakeFiles/supervisor_autogen
supervisor_autogen: src/CMakeFiles/supervisor_autogen.dir/build.make

.PHONY : supervisor_autogen

# Rule to build all files generated by this target.
src/CMakeFiles/supervisor_autogen.dir/build: supervisor_autogen

.PHONY : src/CMakeFiles/supervisor_autogen.dir/build

src/CMakeFiles/supervisor_autogen.dir/clean:
	cd /home/jorge/robocomp/components/supervisor/src && $(CMAKE_COMMAND) -P CMakeFiles/supervisor_autogen.dir/cmake_clean.cmake
.PHONY : src/CMakeFiles/supervisor_autogen.dir/clean

src/CMakeFiles/supervisor_autogen.dir/depend:
	cd /home/jorge/robocomp/components/supervisor && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/jorge/robocomp/components/supervisor /home/jorge/robocomp/components/supervisor/src /home/jorge/robocomp/components/supervisor /home/jorge/robocomp/components/supervisor/src /home/jorge/robocomp/components/supervisor/src/CMakeFiles/supervisor_autogen.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/CMakeFiles/supervisor_autogen.dir/depend

