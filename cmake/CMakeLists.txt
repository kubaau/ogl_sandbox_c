cmake_minimum_required(VERSION 3.1)

project(ogl_sandbox_c)

include(../tools_c/tools/CMakeCommon.cmake)

verifyCCompiler(8 6)

find_package(GLEW REQUIRED)
find_package(GLUT REQUIRED)
find_package(KAZMATH REQUIRED)
find_package(OpenGL REQUIRED)

include_directories(.. ${GLEW_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS} ${KAZMATH_INCLUDE_DIRS} ${OPENGL_INCLUDE_DIRS})

target_link_libraries(${PROJECT_NAME} ${GLEW_LIBRARIES} ${GLUT_LIBRARIES} ${KAZMATH_LIBRARIES} ${OPENGL_LIBRARIES} m)

dumpParameters()

