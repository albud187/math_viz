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
include CMakeFiles/T6.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/T6.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/T6.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/T6.dir/flags.make

CMakeFiles/T6.dir/src/T6_translation.cpp.o: CMakeFiles/T6.dir/flags.make
CMakeFiles/T6.dir/src/T6_translation.cpp.o: ../src/T6_translation.cpp
CMakeFiles/T6.dir/src/T6_translation.cpp.o: CMakeFiles/T6.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/alfab/experiments/math_viz/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/T6.dir/src/T6_translation.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/T6.dir/src/T6_translation.cpp.o -MF CMakeFiles/T6.dir/src/T6_translation.cpp.o.d -o CMakeFiles/T6.dir/src/T6_translation.cpp.o -c /home/alfab/experiments/math_viz/src/T6_translation.cpp

CMakeFiles/T6.dir/src/T6_translation.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/T6.dir/src/T6_translation.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/alfab/experiments/math_viz/src/T6_translation.cpp > CMakeFiles/T6.dir/src/T6_translation.cpp.i

CMakeFiles/T6.dir/src/T6_translation.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/T6.dir/src/T6_translation.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/alfab/experiments/math_viz/src/T6_translation.cpp -o CMakeFiles/T6.dir/src/T6_translation.cpp.s

CMakeFiles/T6.dir/src/ogl_utils/ogldev_util.cpp.o: CMakeFiles/T6.dir/flags.make
CMakeFiles/T6.dir/src/ogl_utils/ogldev_util.cpp.o: ../src/ogl_utils/ogldev_util.cpp
CMakeFiles/T6.dir/src/ogl_utils/ogldev_util.cpp.o: CMakeFiles/T6.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/alfab/experiments/math_viz/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/T6.dir/src/ogl_utils/ogldev_util.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/T6.dir/src/ogl_utils/ogldev_util.cpp.o -MF CMakeFiles/T6.dir/src/ogl_utils/ogldev_util.cpp.o.d -o CMakeFiles/T6.dir/src/ogl_utils/ogldev_util.cpp.o -c /home/alfab/experiments/math_viz/src/ogl_utils/ogldev_util.cpp

CMakeFiles/T6.dir/src/ogl_utils/ogldev_util.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/T6.dir/src/ogl_utils/ogldev_util.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/alfab/experiments/math_viz/src/ogl_utils/ogldev_util.cpp > CMakeFiles/T6.dir/src/ogl_utils/ogldev_util.cpp.i

CMakeFiles/T6.dir/src/ogl_utils/ogldev_util.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/T6.dir/src/ogl_utils/ogldev_util.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/alfab/experiments/math_viz/src/ogl_utils/ogldev_util.cpp -o CMakeFiles/T6.dir/src/ogl_utils/ogldev_util.cpp.s

# Object files for target T6
T6_OBJECTS = \
"CMakeFiles/T6.dir/src/T6_translation.cpp.o" \
"CMakeFiles/T6.dir/src/ogl_utils/ogldev_util.cpp.o"

# External object files for target T6
T6_EXTERNAL_OBJECTS =

T6: CMakeFiles/T6.dir/src/T6_translation.cpp.o
T6: CMakeFiles/T6.dir/src/ogl_utils/ogldev_util.cpp.o
T6: CMakeFiles/T6.dir/build.make
T6: /usr/lib/x86_64-linux-gnu/libGL.so
T6: /usr/lib/x86_64-linux-gnu/libGLU.so
T6: /usr/lib/x86_64-linux-gnu/libglut.so
T6: /usr/lib/x86_64-linux-gnu/libXmu.so
T6: /usr/lib/x86_64-linux-gnu/libXi.so
T6: /usr/lib/x86_64-linux-gnu/libGLEW.so
T6: /usr/lib/x86_64-linux-gnu/libglfw.so.3.3
T6: CMakeFiles/T6.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/alfab/experiments/math_viz/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable T6"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/T6.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/T6.dir/build: T6
.PHONY : CMakeFiles/T6.dir/build

CMakeFiles/T6.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/T6.dir/cmake_clean.cmake
.PHONY : CMakeFiles/T6.dir/clean

CMakeFiles/T6.dir/depend:
	cd /home/alfab/experiments/math_viz/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/alfab/experiments/math_viz /home/alfab/experiments/math_viz /home/alfab/experiments/math_viz/build /home/alfab/experiments/math_viz/build /home/alfab/experiments/math_viz/build/CMakeFiles/T6.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/T6.dir/depend

