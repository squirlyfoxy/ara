# engine -> Library to use for the backend (compiles for the targets specified in readme.txt)
# gui    -> Executable for the GUI.

# libs:
#     - imgui
#     - glfw
#     - glm
#     - SQLiteCpp
#     - stb_image

cmake_minimum_required(VERSION 3.23)
project(ara VERSION 1.0)

# header file for version
configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/include/version.hpp.in"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/version.hpp"
)

# add subdirectories (engine, gui)

# binary output directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/../bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/../bin")

set(BUILD_SHARED_LIBS ON)

add_subdirectory(engine)
add_subdirectory(gui)

# libraries
add_subdirectory(lib/glfw)

add_subdirectory(lib/glad)

add_subdirectory(lib/SQLiteCpp)

add_subdirectory(lib/freetype)

# include global libraries
include_directories(
    "${CMAKE_CURRENT_SOURCE_DIR}/lib/glfw/include"
    "${CMAKE_CURRENT_SOURCE_DIR}/lib/glad/include"
    "${CMAKE_CURRENT_SOURCE_DIR}/lib/glm"
)
