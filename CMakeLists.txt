cmake_minimum_required(VERSION 3.13)
project(Hubble)

file(GLOB hubble_src "*.h" "*.cpp")

option(PLATFORM PLATFORMM_RPI)
# option(OPENGL_VERSION OPENGL_VERSION_OFF)

find_package(raylib 2.5.0 REQUIRED)
find_package(Threads REQUIRED)
find_package(X11 REQUIRED)

find_package(PythonLibs REQUIRED)
include_directories(${PYTHON_INCLUDE_DIRS})

set(CMAKE_C_STANDARD 11)

add_executable(Hubble ${hubble_src})

target_link_libraries(Hubble raylib Threads::Threads X11 ${PYTHON_LIBRARIES})
