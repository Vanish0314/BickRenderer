# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.30

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
CMAKE_COMMAND = "C:\Program Files\CMake\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\CMake\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\20131\Desktop\BickRenderer

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\20131\Desktop\BickRenderer\build

# Utility rule file for uninstall.

# Include any custom commands dependencies for this target.
include 3rd/glfw/CMakeFiles/uninstall.dir/compiler_depend.make

# Include the progress variables for this target.
include 3rd/glfw/CMakeFiles/uninstall.dir/progress.make

3rd/glfw/CMakeFiles/uninstall:
	cd /d C:\Users\20131\Desktop\BickRenderer\build\3rd\glfw && "C:\Program Files\CMake\bin\cmake.exe" -P C:/Users/20131/Desktop/BickRenderer/build/3rd/glfw/cmake_uninstall.cmake

uninstall: 3rd/glfw/CMakeFiles/uninstall
uninstall: 3rd/glfw/CMakeFiles/uninstall.dir/build.make
.PHONY : uninstall

# Rule to build all files generated by this target.
3rd/glfw/CMakeFiles/uninstall.dir/build: uninstall
.PHONY : 3rd/glfw/CMakeFiles/uninstall.dir/build

3rd/glfw/CMakeFiles/uninstall.dir/clean:
	cd /d C:\Users\20131\Desktop\BickRenderer\build\3rd\glfw && $(CMAKE_COMMAND) -P CMakeFiles\uninstall.dir\cmake_clean.cmake
.PHONY : 3rd/glfw/CMakeFiles/uninstall.dir/clean

3rd/glfw/CMakeFiles/uninstall.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\20131\Desktop\BickRenderer C:\Users\20131\Desktop\BickRenderer\3rd\glfw C:\Users\20131\Desktop\BickRenderer\build C:\Users\20131\Desktop\BickRenderer\build\3rd\glfw C:\Users\20131\Desktop\BickRenderer\build\3rd\glfw\CMakeFiles\uninstall.dir\DependInfo.cmake "--color=$(COLOR)"
.PHONY : 3rd/glfw/CMakeFiles/uninstall.dir/depend

