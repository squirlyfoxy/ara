# engine -> Library to use for the backend (compiles for the targets specified in readme.txt)
# gui    -> Executable for the GUI.

# libs:
#     - imgui
#     - glfw
#     - glm
#     - stb_image

cmake_minimum_required(VERSION 3.23)
project(ara VERSION 1.0)

# header file for version
configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/include/version.hpp.in"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/version.hpp"
)

# binary output directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/../bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/../bin")

# add subdirectories (engine, gui)
add_subdirectory(engine)
add_subdirectory(gui)
