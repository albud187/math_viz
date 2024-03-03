cmake_minimum_required(VERSION 3.10)  # Specify the minimum version of CMake
project(math_viz)  # Name your project

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(GLUT REQUIRED)
find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(GLEW REQUIRED)
# Include directories

include_directories(${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS})

add_executable(multi_3d src/multi_3d.cpp 
    src/ogl_utils/ogldev_util.cpp
    src/ogl_utils/ogldev_math_3d.cpp
    src/multi_utils/camera.cpp 
    src/multi_utils/world_transform.cpp
    src/multi_utils/shaders.cpp
    src/multi_utils/mesh.cpp
    )
    
target_link_libraries(multi_3d ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} ${GLEW_LIBRARIES} glfw)