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

# Include any dependencies generated for this target.
include Source/CMakeFiles/BickRenderer.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include Source/CMakeFiles/BickRenderer.dir/compiler_depend.make

# Include the progress variables for this target.
include Source/CMakeFiles/BickRenderer.dir/progress.make

# Include the compile flags for this target's objects.
include Source/CMakeFiles/BickRenderer.dir/flags.make

Source/CMakeFiles/BickRenderer.dir/Src/Texture/Texture.cpp.obj: Source/CMakeFiles/BickRenderer.dir/flags.make
Source/CMakeFiles/BickRenderer.dir/Src/Texture/Texture.cpp.obj: Source/CMakeFiles/BickRenderer.dir/includes_CXX.rsp
Source/CMakeFiles/BickRenderer.dir/Src/Texture/Texture.cpp.obj: C:/Users/20131/Desktop/BickRenderer/Source/Src/Texture/Texture.cpp
Source/CMakeFiles/BickRenderer.dir/Src/Texture/Texture.cpp.obj: Source/CMakeFiles/BickRenderer.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:\Users\20131\Desktop\BickRenderer\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object Source/CMakeFiles/BickRenderer.dir/Src/Texture/Texture.cpp.obj"
	cd /d C:\Users\20131\Desktop\BickRenderer\build\Source && C:\msys64\ucrt64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT Source/CMakeFiles/BickRenderer.dir/Src/Texture/Texture.cpp.obj -MF CMakeFiles\BickRenderer.dir\Src\Texture\Texture.cpp.obj.d -o CMakeFiles\BickRenderer.dir\Src\Texture\Texture.cpp.obj -c C:\Users\20131\Desktop\BickRenderer\Source\Src\Texture\Texture.cpp

Source/CMakeFiles/BickRenderer.dir/Src/Texture/Texture.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/BickRenderer.dir/Src/Texture/Texture.cpp.i"
	cd /d C:\Users\20131\Desktop\BickRenderer\build\Source && C:\msys64\ucrt64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\20131\Desktop\BickRenderer\Source\Src\Texture\Texture.cpp > CMakeFiles\BickRenderer.dir\Src\Texture\Texture.cpp.i

Source/CMakeFiles/BickRenderer.dir/Src/Texture/Texture.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/BickRenderer.dir/Src/Texture/Texture.cpp.s"
	cd /d C:\Users\20131\Desktop\BickRenderer\build\Source && C:\msys64\ucrt64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\20131\Desktop\BickRenderer\Source\Src\Texture\Texture.cpp -o CMakeFiles\BickRenderer.dir\Src\Texture\Texture.cpp.s

Source/CMakeFiles/BickRenderer.dir/Src/glad/glad.c.obj: Source/CMakeFiles/BickRenderer.dir/flags.make
Source/CMakeFiles/BickRenderer.dir/Src/glad/glad.c.obj: Source/CMakeFiles/BickRenderer.dir/includes_C.rsp
Source/CMakeFiles/BickRenderer.dir/Src/glad/glad.c.obj: C:/Users/20131/Desktop/BickRenderer/Source/Src/glad/glad.c
Source/CMakeFiles/BickRenderer.dir/Src/glad/glad.c.obj: Source/CMakeFiles/BickRenderer.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:\Users\20131\Desktop\BickRenderer\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object Source/CMakeFiles/BickRenderer.dir/Src/glad/glad.c.obj"
	cd /d C:\Users\20131\Desktop\BickRenderer\build\Source && C:\msys64\ucrt64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT Source/CMakeFiles/BickRenderer.dir/Src/glad/glad.c.obj -MF CMakeFiles\BickRenderer.dir\Src\glad\glad.c.obj.d -o CMakeFiles\BickRenderer.dir\Src\glad\glad.c.obj -c C:\Users\20131\Desktop\BickRenderer\Source\Src\glad\glad.c

Source/CMakeFiles/BickRenderer.dir/Src/glad/glad.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/BickRenderer.dir/Src/glad/glad.c.i"
	cd /d C:\Users\20131\Desktop\BickRenderer\build\Source && C:\msys64\ucrt64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\20131\Desktop\BickRenderer\Source\Src\glad\glad.c > CMakeFiles\BickRenderer.dir\Src\glad\glad.c.i

Source/CMakeFiles/BickRenderer.dir/Src/glad/glad.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/BickRenderer.dir/Src/glad/glad.c.s"
	cd /d C:\Users\20131\Desktop\BickRenderer\build\Source && C:\msys64\ucrt64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\20131\Desktop\BickRenderer\Source\Src\glad\glad.c -o CMakeFiles\BickRenderer.dir\Src\glad\glad.c.s

Source/CMakeFiles/BickRenderer.dir/Src/main.cpp.obj: Source/CMakeFiles/BickRenderer.dir/flags.make
Source/CMakeFiles/BickRenderer.dir/Src/main.cpp.obj: Source/CMakeFiles/BickRenderer.dir/includes_CXX.rsp
Source/CMakeFiles/BickRenderer.dir/Src/main.cpp.obj: C:/Users/20131/Desktop/BickRenderer/Source/Src/main.cpp
Source/CMakeFiles/BickRenderer.dir/Src/main.cpp.obj: Source/CMakeFiles/BickRenderer.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:\Users\20131\Desktop\BickRenderer\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object Source/CMakeFiles/BickRenderer.dir/Src/main.cpp.obj"
	cd /d C:\Users\20131\Desktop\BickRenderer\build\Source && C:\msys64\ucrt64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT Source/CMakeFiles/BickRenderer.dir/Src/main.cpp.obj -MF CMakeFiles\BickRenderer.dir\Src\main.cpp.obj.d -o CMakeFiles\BickRenderer.dir\Src\main.cpp.obj -c C:\Users\20131\Desktop\BickRenderer\Source\Src\main.cpp

Source/CMakeFiles/BickRenderer.dir/Src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/BickRenderer.dir/Src/main.cpp.i"
	cd /d C:\Users\20131\Desktop\BickRenderer\build\Source && C:\msys64\ucrt64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\20131\Desktop\BickRenderer\Source\Src\main.cpp > CMakeFiles\BickRenderer.dir\Src\main.cpp.i

Source/CMakeFiles/BickRenderer.dir/Src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/BickRenderer.dir/Src/main.cpp.s"
	cd /d C:\Users\20131\Desktop\BickRenderer\build\Source && C:\msys64\ucrt64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\20131\Desktop\BickRenderer\Source\Src\main.cpp -o CMakeFiles\BickRenderer.dir\Src\main.cpp.s

Source/CMakeFiles/BickRenderer.dir/Src/shader/Shader.cpp.obj: Source/CMakeFiles/BickRenderer.dir/flags.make
Source/CMakeFiles/BickRenderer.dir/Src/shader/Shader.cpp.obj: Source/CMakeFiles/BickRenderer.dir/includes_CXX.rsp
Source/CMakeFiles/BickRenderer.dir/Src/shader/Shader.cpp.obj: C:/Users/20131/Desktop/BickRenderer/Source/Src/shader/Shader.cpp
Source/CMakeFiles/BickRenderer.dir/Src/shader/Shader.cpp.obj: Source/CMakeFiles/BickRenderer.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:\Users\20131\Desktop\BickRenderer\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object Source/CMakeFiles/BickRenderer.dir/Src/shader/Shader.cpp.obj"
	cd /d C:\Users\20131\Desktop\BickRenderer\build\Source && C:\msys64\ucrt64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT Source/CMakeFiles/BickRenderer.dir/Src/shader/Shader.cpp.obj -MF CMakeFiles\BickRenderer.dir\Src\shader\Shader.cpp.obj.d -o CMakeFiles\BickRenderer.dir\Src\shader\Shader.cpp.obj -c C:\Users\20131\Desktop\BickRenderer\Source\Src\shader\Shader.cpp

Source/CMakeFiles/BickRenderer.dir/Src/shader/Shader.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/BickRenderer.dir/Src/shader/Shader.cpp.i"
	cd /d C:\Users\20131\Desktop\BickRenderer\build\Source && C:\msys64\ucrt64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\20131\Desktop\BickRenderer\Source\Src\shader\Shader.cpp > CMakeFiles\BickRenderer.dir\Src\shader\Shader.cpp.i

Source/CMakeFiles/BickRenderer.dir/Src/shader/Shader.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/BickRenderer.dir/Src/shader/Shader.cpp.s"
	cd /d C:\Users\20131\Desktop\BickRenderer\build\Source && C:\msys64\ucrt64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\20131\Desktop\BickRenderer\Source\Src\shader\Shader.cpp -o CMakeFiles\BickRenderer.dir\Src\shader\Shader.cpp.s

# Object files for target BickRenderer
BickRenderer_OBJECTS = \
"CMakeFiles/BickRenderer.dir/Src/Texture/Texture.cpp.obj" \
"CMakeFiles/BickRenderer.dir/Src/glad/glad.c.obj" \
"CMakeFiles/BickRenderer.dir/Src/main.cpp.obj" \
"CMakeFiles/BickRenderer.dir/Src/shader/Shader.cpp.obj"

# External object files for target BickRenderer
BickRenderer_EXTERNAL_OBJECTS =

C:/Users/20131/Desktop/BickRenderer/BickRenderer.exe: Source/CMakeFiles/BickRenderer.dir/Src/Texture/Texture.cpp.obj
C:/Users/20131/Desktop/BickRenderer/BickRenderer.exe: Source/CMakeFiles/BickRenderer.dir/Src/glad/glad.c.obj
C:/Users/20131/Desktop/BickRenderer/BickRenderer.exe: Source/CMakeFiles/BickRenderer.dir/Src/main.cpp.obj
C:/Users/20131/Desktop/BickRenderer/BickRenderer.exe: Source/CMakeFiles/BickRenderer.dir/Src/shader/Shader.cpp.obj
C:/Users/20131/Desktop/BickRenderer/BickRenderer.exe: Source/CMakeFiles/BickRenderer.dir/build.make
C:/Users/20131/Desktop/BickRenderer/BickRenderer.exe: 3rd/glfw/src/libglfw3.a
C:/Users/20131/Desktop/BickRenderer/BickRenderer.exe: 3rd/glm/glm/libglm.a
C:/Users/20131/Desktop/BickRenderer/BickRenderer.exe: Source/CMakeFiles/BickRenderer.dir/linkLibs.rsp
C:/Users/20131/Desktop/BickRenderer/BickRenderer.exe: Source/CMakeFiles/BickRenderer.dir/objects1.rsp
C:/Users/20131/Desktop/BickRenderer/BickRenderer.exe: Source/CMakeFiles/BickRenderer.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=C:\Users\20131\Desktop\BickRenderer\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking CXX executable C:\Users\20131\Desktop\BickRenderer\BickRenderer.exe"
	cd /d C:\Users\20131\Desktop\BickRenderer\build\Source && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\BickRenderer.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
Source/CMakeFiles/BickRenderer.dir/build: C:/Users/20131/Desktop/BickRenderer/BickRenderer.exe
.PHONY : Source/CMakeFiles/BickRenderer.dir/build

Source/CMakeFiles/BickRenderer.dir/clean:
	cd /d C:\Users\20131\Desktop\BickRenderer\build\Source && $(CMAKE_COMMAND) -P CMakeFiles\BickRenderer.dir\cmake_clean.cmake
.PHONY : Source/CMakeFiles/BickRenderer.dir/clean

Source/CMakeFiles/BickRenderer.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\20131\Desktop\BickRenderer C:\Users\20131\Desktop\BickRenderer\Source C:\Users\20131\Desktop\BickRenderer\build C:\Users\20131\Desktop\BickRenderer\build\Source C:\Users\20131\Desktop\BickRenderer\build\Source\CMakeFiles\BickRenderer.dir\DependInfo.cmake "--color=$(COLOR)"
.PHONY : Source/CMakeFiles/BickRenderer.dir/depend
