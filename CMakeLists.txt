cmake_minimum_required(VERSION 3.10)

project(blemderer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${CMAKE_SOURCE_DIR}/third_party/imgui/core)
include_directories(${CMAKE_SOURCE_DIR}/third_party/imgui/backends)
include_directories(third_party/imgui/core third_party/imgui/backends)


file(GLOB_RECURSE SOURCES
  "${CMAKE_SOURCE_DIR}/src/*.cpp"
  "${CMAKE_SOURCE_DIR}/third_party/imgui/core/*.cpp"
  "${CMAKE_SOURCE_DIR}/third_party/imgui/backends/imgui_impl_sdl2.cpp"
  "${CMAKE_SOURCE_DIR}/third_party/imgui/backends/imgui_impl_opengl3.cpp"
)

add_executable(blemderer ${SOURCES} include/settings.h)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})
target_link_libraries(blemderer ${SDL2_LIBRARIES})

# supress warning
set (OpenGL_GL_PREFERENCE "GLVND")
find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})
target_link_libraries(blemderer ${OPENGL_LIBRARIES})

find_package(GLEW REQUIRED)
include_directories(${GLEW_INCLUDE_DIRS})
target_link_libraries(blemderer ${GLEW_LIBRARIES})
