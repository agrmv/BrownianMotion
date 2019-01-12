cmake_minimum_required(VERSION 3.12)
project(oop)

set(CMAKE_CXX_STANDARD 17)
add_executable(${PROJECT_NAME} main.cpp tPoint.hpp tLocation.hpp tFigure.hpp tCircle.hpp Glut.hpp)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

include_directories(${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})