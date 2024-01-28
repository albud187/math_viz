cmake_minimum_required(VERSION 3.10)  # Specify the minimum version of CMake
project(math_viz)  # Name your project

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_package(glfw3 REQUIRED)
find_package(GLEW REQUIRED)
# Include directories
include_directories(${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS})

# add_executable(T3 src/T3_triangle.cpp )
# target_link_libraries(T3 ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} ${GLEW_LIBRARIES} glfw)

add_executable(T4 src/T4_shaders.cpp src/ogl_utils/ogldev_util.cpp)
target_link_libraries(T4 ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} ${GLEW_LIBRARIES} glfw)

add_executable(T4_multi src/T4_shaders_multi.cpp src/ogl_utils/ogldev_util.cpp)
target_link_libraries(T4_multi ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} ${GLEW_LIBRARIES} glfw)

# add_executable(T5 src/T5_uniforms.cpp src/ogl_utils/ogldev_util.cpp)
# target_link_libraries(T5 ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} ${GLEW_LIBRARIES} glfw)

# add_executable(T6 src/T6_translation.cpp src/ogl_utils/ogldev_util.cpp)
# target_link_libraries(T6 ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} ${GLEW_LIBRARIES} glfw)

# add_executable(T7 src/T7_rotation.cpp src/ogl_utils/ogldev_util.cpp)
# target_link_libraries(T7 ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} ${GLEW_LIBRARIES} glfw)