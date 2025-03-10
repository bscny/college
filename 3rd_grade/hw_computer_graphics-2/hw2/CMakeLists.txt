cmake_minimum_required (VERSION 2.6)
project (hw-gl)

find_package(OpenGL REQUIRED)

find_package(PkgConfig REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)
pkg_search_module(GLEW REQUIRED glew)

include_directories(glad)


#find_package(glm)
include_directories( ${OPENGL_INCLUDE_DIRS}  ${GLFW_INCLUDE_DIRS} ${GLEW_INCLUDE_DIRS} )

#set(GLAD_GL "glad/gl.h"})

#if(CMAKE_COMPILER_IS_GNUCXX)
#    add_definitions(-std=gnu++11)
#endif()


# window
add_executable(window main.cpp)
target_link_libraries(window ${OPENGL_LIBRARIES} ${GLFW_LIBRARIES})

# start: triangle with shader
add_executable(start start.cpp)
target_link_libraries(start ${OPENGL_LIBRARIES} ${GLEW_LIBRARIES} ${GLFW_LIBRARIES}  )

# 1-line
add_executable(1-line 1-line.cpp)
target_link_libraries(1-line ${OPENGL_LIBRARIES} ${GLEW_LIBRARIES} ${GLFW_LIBRARIES}  )

# 2-ray
add_executable(2-ray 2-ray.cpp)
target_link_libraries(2-ray ${OPENGL_LIBRARIES} ${GLEW_LIBRARIES} ${GLFW_LIBRARIES}  )

# gasket1
add_executable(gasket1 gasket1.cpp)
target_link_libraries(gasket1 ${OPENGL_LIBRARIES} ${GLEW_LIBRARIES} ${GLFW_LIBRARIES}  )

# gasket2
add_executable(gasket2 gasket2.cpp)
target_link_libraries(gasket2 ${OPENGL_LIBRARIES} ${GLEW_LIBRARIES} ${GLFW_LIBRARIES}  )

# gasket3
add_executable(gasket3 gasket3.cpp)
target_link_libraries(gasket3 ${OPENGL_LIBRARIES} ${GLEW_LIBRARIES} ${GLFW_LIBRARIES}  )