cmake_minimum_required(VERSION 3.10)  # Specify the minimum version of CMake
project(math_viz)  # Name your project

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED) 

# Include directories
include_directories(${CMAKE_SOURCE_DIR}/src/glad)
include_directories(${CMAKE_SOURCE_DIR}/src/rendering)

# Add the executable
add_executable(main src/main.cpp src/glad/glad.c)

# Link libraries
target_link_libraries(main ${OPENGL_gl_LIBRARY} glfw)
