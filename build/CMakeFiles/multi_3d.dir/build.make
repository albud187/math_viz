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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/alfab/experiments/math_viz

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/alfab/experiments/math_viz/build

# Include any dependencies generated for this target.
include CMakeFiles/multi_3d.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/multi_3d.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/multi_3d.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/multi_3d.dir/flags.make

CMakeFiles/multi_3d.dir/src/multi_3d.cpp.o: CMakeFiles/multi_3d.dir/flags.make
CMakeFiles/multi_3d.dir/src/multi_3d.cpp.o: ../src/multi_3d.cpp
CMakeFiles/multi_3d.dir/src/multi_3d.cpp.o: CMakeFiles/multi_3d.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/alfab/experiments/math_viz/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/multi_3d.dir/src/multi_3d.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/multi_3d.dir/src/multi_3d.cpp.o -MF CMakeFiles/multi_3d.dir/src/multi_3d.cpp.o.d -o CMakeFiles/multi_3d.dir/src/multi_3d.cpp.o -c /home/alfab/experiments/math_viz/src/multi_3d.cpp

CMakeFiles/multi_3d.dir/src/multi_3d.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/multi_3d.dir/src/multi_3d.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/alfab/experiments/math_viz/src/multi_3d.cpp > CMakeFiles/multi_3d.dir/src/multi_3d.cpp.i

CMakeFiles/multi_3d.dir/src/multi_3d.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/multi_3d.dir/src/multi_3d.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/alfab/experiments/math_viz/src/multi_3d.cpp -o CMakeFiles/multi_3d.dir/src/multi_3d.cpp.s

CMakeFiles/multi_3d.dir/src/ogl_utils/ogldev_util.cpp.o: CMakeFiles/multi_3d.dir/flags.make
CMakeFiles/multi_3d.dir/src/ogl_utils/ogldev_util.cpp.o: ../src/ogl_utils/ogldev_util.cpp
CMakeFiles/multi_3d.dir/src/ogl_utils/ogldev_util.cpp.o: CMakeFiles/multi_3d.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/alfab/experiments/math_viz/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/multi_3d.dir/src/ogl_utils/ogldev_util.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/multi_3d.dir/src/ogl_utils/ogldev_util.cpp.o -MF CMakeFiles/multi_3d.dir/src/ogl_utils/ogldev_util.cpp.o.d -o CMakeFiles/multi_3d.dir/src/ogl_utils/ogldev_util.cpp.o -c /home/alfab/experiments/math_viz/src/ogl_utils/ogldev_util.cpp

CMakeFiles/multi_3d.dir/src/ogl_utils/ogldev_util.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/multi_3d.dir/src/ogl_utils/ogldev_util.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/alfab/experiments/math_viz/src/ogl_utils/ogldev_util.cpp > CMakeFiles/multi_3d.dir/src/ogl_utils/ogldev_util.cpp.i

CMakeFiles/multi_3d.dir/src/ogl_utils/ogldev_util.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/multi_3d.dir/src/ogl_utils/ogldev_util.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/alfab/experiments/math_viz/src/ogl_utils/ogldev_util.cpp -o CMakeFiles/multi_3d.dir/src/ogl_utils/ogldev_util.cpp.s

CMakeFiles/multi_3d.dir/src/ogl_utils/ogldev_math_3d.cpp.o: CMakeFiles/multi_3d.dir/flags.make
CMakeFiles/multi_3d.dir/src/ogl_utils/ogldev_math_3d.cpp.o: ../src/ogl_utils/ogldev_math_3d.cpp
CMakeFiles/multi_3d.dir/src/ogl_utils/ogldev_math_3d.cpp.o: CMakeFiles/multi_3d.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/alfab/experiments/math_viz/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/multi_3d.dir/src/ogl_utils/ogldev_math_3d.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/multi_3d.dir/src/ogl_utils/ogldev_math_3d.cpp.o -MF CMakeFiles/multi_3d.dir/src/ogl_utils/ogldev_math_3d.cpp.o.d -o CMakeFiles/multi_3d.dir/src/ogl_utils/ogldev_math_3d.cpp.o -c /home/alfab/experiments/math_viz/src/ogl_utils/ogldev_math_3d.cpp

CMakeFiles/multi_3d.dir/src/ogl_utils/ogldev_math_3d.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/multi_3d.dir/src/ogl_utils/ogldev_math_3d.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/alfab/experiments/math_viz/src/ogl_utils/ogldev_math_3d.cpp > CMakeFiles/multi_3d.dir/src/ogl_utils/ogldev_math_3d.cpp.i

CMakeFiles/multi_3d.dir/src/ogl_utils/ogldev_math_3d.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/multi_3d.dir/src/ogl_utils/ogldev_math_3d.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/alfab/experiments/math_viz/src/ogl_utils/ogldev_math_3d.cpp -o CMakeFiles/multi_3d.dir/src/ogl_utils/ogldev_math_3d.cpp.s

CMakeFiles/multi_3d.dir/src/multi_utils/camera.cpp.o: CMakeFiles/multi_3d.dir/flags.make
CMakeFiles/multi_3d.dir/src/multi_utils/camera.cpp.o: ../src/multi_utils/camera.cpp
CMakeFiles/multi_3d.dir/src/multi_utils/camera.cpp.o: CMakeFiles/multi_3d.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/alfab/experiments/math_viz/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/multi_3d.dir/src/multi_utils/camera.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/multi_3d.dir/src/multi_utils/camera.cpp.o -MF CMakeFiles/multi_3d.dir/src/multi_utils/camera.cpp.o.d -o CMakeFiles/multi_3d.dir/src/multi_utils/camera.cpp.o -c /home/alfab/experiments/math_viz/src/multi_utils/camera.cpp

CMakeFiles/multi_3d.dir/src/multi_utils/camera.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/multi_3d.dir/src/multi_utils/camera.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/alfab/experiments/math_viz/src/multi_utils/camera.cpp > CMakeFiles/multi_3d.dir/src/multi_utils/camera.cpp.i

CMakeFiles/multi_3d.dir/src/multi_utils/camera.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/multi_3d.dir/src/multi_utils/camera.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/alfab/experiments/math_viz/src/multi_utils/camera.cpp -o CMakeFiles/multi_3d.dir/src/multi_utils/camera.cpp.s

CMakeFiles/multi_3d.dir/src/multi_utils/world_transform.cpp.o: CMakeFiles/multi_3d.dir/flags.make
CMakeFiles/multi_3d.dir/src/multi_utils/world_transform.cpp.o: ../src/multi_utils/world_transform.cpp
CMakeFiles/multi_3d.dir/src/multi_utils/world_transform.cpp.o: CMakeFiles/multi_3d.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/alfab/experiments/math_viz/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/multi_3d.dir/src/multi_utils/world_transform.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/multi_3d.dir/src/multi_utils/world_transform.cpp.o -MF CMakeFiles/multi_3d.dir/src/multi_utils/world_transform.cpp.o.d -o CMakeFiles/multi_3d.dir/src/multi_utils/world_transform.cpp.o -c /home/alfab/experiments/math_viz/src/multi_utils/world_transform.cpp

CMakeFiles/multi_3d.dir/src/multi_utils/world_transform.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/multi_3d.dir/src/multi_utils/world_transform.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/alfab/experiments/math_viz/src/multi_utils/world_transform.cpp > CMakeFiles/multi_3d.dir/src/multi_utils/world_transform.cpp.i

CMakeFiles/multi_3d.dir/src/multi_utils/world_transform.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/multi_3d.dir/src/multi_utils/world_transform.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/alfab/experiments/math_viz/src/multi_utils/world_transform.cpp -o CMakeFiles/multi_3d.dir/src/multi_utils/world_transform.cpp.s

CMakeFiles/multi_3d.dir/src/multi_utils/shaders.cpp.o: CMakeFiles/multi_3d.dir/flags.make
CMakeFiles/multi_3d.dir/src/multi_utils/shaders.cpp.o: ../src/multi_utils/shaders.cpp
CMakeFiles/multi_3d.dir/src/multi_utils/shaders.cpp.o: CMakeFiles/multi_3d.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/alfab/experiments/math_viz/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/multi_3d.dir/src/multi_utils/shaders.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/multi_3d.dir/src/multi_utils/shaders.cpp.o -MF CMakeFiles/multi_3d.dir/src/multi_utils/shaders.cpp.o.d -o CMakeFiles/multi_3d.dir/src/multi_utils/shaders.cpp.o -c /home/alfab/experiments/math_viz/src/multi_utils/shaders.cpp

CMakeFiles/multi_3d.dir/src/multi_utils/shaders.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/multi_3d.dir/src/multi_utils/shaders.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/alfab/experiments/math_viz/src/multi_utils/shaders.cpp > CMakeFiles/multi_3d.dir/src/multi_utils/shaders.cpp.i

CMakeFiles/multi_3d.dir/src/multi_utils/shaders.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/multi_3d.dir/src/multi_utils/shaders.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/alfab/experiments/math_viz/src/multi_utils/shaders.cpp -o CMakeFiles/multi_3d.dir/src/multi_utils/shaders.cpp.s

CMakeFiles/multi_3d.dir/src/multi_utils/mesh.cpp.o: CMakeFiles/multi_3d.dir/flags.make
CMakeFiles/multi_3d.dir/src/multi_utils/mesh.cpp.o: ../src/multi_utils/mesh.cpp
CMakeFiles/multi_3d.dir/src/multi_utils/mesh.cpp.o: CMakeFiles/multi_3d.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/alfab/experiments/math_viz/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/multi_3d.dir/src/multi_utils/mesh.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/multi_3d.dir/src/multi_utils/mesh.cpp.o -MF CMakeFiles/multi_3d.dir/src/multi_utils/mesh.cpp.o.d -o CMakeFiles/multi_3d.dir/src/multi_utils/mesh.cpp.o -c /home/alfab/experiments/math_viz/src/multi_utils/mesh.cpp

CMakeFiles/multi_3d.dir/src/multi_utils/mesh.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/multi_3d.dir/src/multi_utils/mesh.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/alfab/experiments/math_viz/src/multi_utils/mesh.cpp > CMakeFiles/multi_3d.dir/src/multi_utils/mesh.cpp.i

CMakeFiles/multi_3d.dir/src/multi_utils/mesh.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/multi_3d.dir/src/multi_utils/mesh.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/alfab/experiments/math_viz/src/multi_utils/mesh.cpp -o CMakeFiles/multi_3d.dir/src/multi_utils/mesh.cpp.s

# Object files for target multi_3d
multi_3d_OBJECTS = \
"CMakeFiles/multi_3d.dir/src/multi_3d.cpp.o" \
"CMakeFiles/multi_3d.dir/src/ogl_utils/ogldev_util.cpp.o" \
"CMakeFiles/multi_3d.dir/src/ogl_utils/ogldev_math_3d.cpp.o" \
"CMakeFiles/multi_3d.dir/src/multi_utils/camera.cpp.o" \
"CMakeFiles/multi_3d.dir/src/multi_utils/world_transform.cpp.o" \
"CMakeFiles/multi_3d.dir/src/multi_utils/shaders.cpp.o" \
"CMakeFiles/multi_3d.dir/src/multi_utils/mesh.cpp.o"

# External object files for target multi_3d
multi_3d_EXTERNAL_OBJECTS =

multi_3d: CMakeFiles/multi_3d.dir/src/multi_3d.cpp.o
multi_3d: CMakeFiles/multi_3d.dir/src/ogl_utils/ogldev_util.cpp.o
multi_3d: CMakeFiles/multi_3d.dir/src/ogl_utils/ogldev_math_3d.cpp.o
multi_3d: CMakeFiles/multi_3d.dir/src/multi_utils/camera.cpp.o
multi_3d: CMakeFiles/multi_3d.dir/src/multi_utils/world_transform.cpp.o
multi_3d: CMakeFiles/multi_3d.dir/src/multi_utils/shaders.cpp.o
multi_3d: CMakeFiles/multi_3d.dir/src/multi_utils/mesh.cpp.o
multi_3d: CMakeFiles/multi_3d.dir/build.make
multi_3d: /usr/lib/x86_64-linux-gnu/libGL.so
multi_3d: /usr/lib/x86_64-linux-gnu/libGLU.so
multi_3d: /usr/lib/x86_64-linux-gnu/libglut.so
multi_3d: /usr/lib/x86_64-linux-gnu/libXmu.so
multi_3d: /usr/lib/x86_64-linux-gnu/libXi.so
multi_3d: /usr/lib/x86_64-linux-gnu/libGLEW.so
multi_3d: /usr/lib/x86_64-linux-gnu/libglfw.so.3.3
multi_3d: CMakeFiles/multi_3d.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/alfab/experiments/math_viz/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Linking CXX executable multi_3d"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/multi_3d.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/multi_3d.dir/build: multi_3d
.PHONY : CMakeFiles/multi_3d.dir/build

CMakeFiles/multi_3d.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/multi_3d.dir/cmake_clean.cmake
.PHONY : CMakeFiles/multi_3d.dir/clean

CMakeFiles/multi_3d.dir/depend:
	cd /home/alfab/experiments/math_viz/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/alfab/experiments/math_viz /home/alfab/experiments/math_viz /home/alfab/experiments/math_viz/build /home/alfab/experiments/math_viz/build /home/alfab/experiments/math_viz/build/CMakeFiles/multi_3d.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/multi_3d.dir/depend

