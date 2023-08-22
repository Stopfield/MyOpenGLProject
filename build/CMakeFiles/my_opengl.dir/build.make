# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.27

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/thiago-fedora/Documentos/Learning/OpenGL

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/thiago-fedora/Documentos/Learning/OpenGL/build

# Include any dependencies generated for this target.
include CMakeFiles/my_opengl.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/my_opengl.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/my_opengl.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/my_opengl.dir/flags.make

CMakeFiles/my_opengl.dir/src/main.cpp.o: CMakeFiles/my_opengl.dir/flags.make
CMakeFiles/my_opengl.dir/src/main.cpp.o: /home/thiago-fedora/Documentos/Learning/OpenGL/src/main.cpp
CMakeFiles/my_opengl.dir/src/main.cpp.o: CMakeFiles/my_opengl.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/thiago-fedora/Documentos/Learning/OpenGL/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/my_opengl.dir/src/main.cpp.o"
	/usr/lib64/ccache/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/my_opengl.dir/src/main.cpp.o -MF CMakeFiles/my_opengl.dir/src/main.cpp.o.d -o CMakeFiles/my_opengl.dir/src/main.cpp.o -c /home/thiago-fedora/Documentos/Learning/OpenGL/src/main.cpp

CMakeFiles/my_opengl.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/my_opengl.dir/src/main.cpp.i"
	/usr/lib64/ccache/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/thiago-fedora/Documentos/Learning/OpenGL/src/main.cpp > CMakeFiles/my_opengl.dir/src/main.cpp.i

CMakeFiles/my_opengl.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/my_opengl.dir/src/main.cpp.s"
	/usr/lib64/ccache/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/thiago-fedora/Documentos/Learning/OpenGL/src/main.cpp -o CMakeFiles/my_opengl.dir/src/main.cpp.s

CMakeFiles/my_opengl.dir/src/glad.c.o: CMakeFiles/my_opengl.dir/flags.make
CMakeFiles/my_opengl.dir/src/glad.c.o: /home/thiago-fedora/Documentos/Learning/OpenGL/src/glad.c
CMakeFiles/my_opengl.dir/src/glad.c.o: CMakeFiles/my_opengl.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/thiago-fedora/Documentos/Learning/OpenGL/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/my_opengl.dir/src/glad.c.o"
	/usr/lib64/ccache/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/my_opengl.dir/src/glad.c.o -MF CMakeFiles/my_opengl.dir/src/glad.c.o.d -o CMakeFiles/my_opengl.dir/src/glad.c.o -c /home/thiago-fedora/Documentos/Learning/OpenGL/src/glad.c

CMakeFiles/my_opengl.dir/src/glad.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/my_opengl.dir/src/glad.c.i"
	/usr/lib64/ccache/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/thiago-fedora/Documentos/Learning/OpenGL/src/glad.c > CMakeFiles/my_opengl.dir/src/glad.c.i

CMakeFiles/my_opengl.dir/src/glad.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/my_opengl.dir/src/glad.c.s"
	/usr/lib64/ccache/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/thiago-fedora/Documentos/Learning/OpenGL/src/glad.c -o CMakeFiles/my_opengl.dir/src/glad.c.s

# Object files for target my_opengl
my_opengl_OBJECTS = \
"CMakeFiles/my_opengl.dir/src/main.cpp.o" \
"CMakeFiles/my_opengl.dir/src/glad.c.o"

# External object files for target my_opengl
my_opengl_EXTERNAL_OBJECTS =

my_opengl: CMakeFiles/my_opengl.dir/src/main.cpp.o
my_opengl: CMakeFiles/my_opengl.dir/src/glad.c.o
my_opengl: CMakeFiles/my_opengl.dir/build.make
my_opengl: /usr/lib64/libGLX.so
my_opengl: /usr/lib64/libOpenGL.so
my_opengl: CMakeFiles/my_opengl.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/thiago-fedora/Documentos/Learning/OpenGL/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable my_opengl"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/my_opengl.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/my_opengl.dir/build: my_opengl
.PHONY : CMakeFiles/my_opengl.dir/build

CMakeFiles/my_opengl.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/my_opengl.dir/cmake_clean.cmake
.PHONY : CMakeFiles/my_opengl.dir/clean

CMakeFiles/my_opengl.dir/depend:
	cd /home/thiago-fedora/Documentos/Learning/OpenGL/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/thiago-fedora/Documentos/Learning/OpenGL /home/thiago-fedora/Documentos/Learning/OpenGL /home/thiago-fedora/Documentos/Learning/OpenGL/build /home/thiago-fedora/Documentos/Learning/OpenGL/build /home/thiago-fedora/Documentos/Learning/OpenGL/build/CMakeFiles/my_opengl.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/my_opengl.dir/depend
