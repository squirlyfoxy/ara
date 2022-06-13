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

# binary output directory
if(EMSCRIPTEN)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/../bin/wbuild")
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/../bin/wbuild")

    set(CMAKE_TOOLCHAIN_FILE "${CMAKE_CURRENT_SOURCE_DIR}../tools/emscripten/upstream/emscripten/cmake/Modules/Platform/Emscripten.cmake")
else()
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/../bin")
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/../bin")
    set(BUILD_SHARED_LIBS ON)
endif()

# add subdirectories (engine, gui)
add_subdirectory(engine)
if(EMSCRIPTEN)
else()
    add_subdirectory(gui)
endif()

# libraries
if(EMSCRIPTEN)
else()
    add_subdirectory(lib/glfw)
endif()

add_subdirectory(lib/glad)

set(SQLITECPP_RUN_CPPLINT OFF)
add_subdirectory(lib/SQLiteCpp)

add_subdirectory(lib/freetype)

# include global libraries
include_directories(
    "${CMAKE_CURRENT_SOURCE_DIR}/lib/glfw/include"
    "${CMAKE_CURRENT_SOURCE_DIR}/lib/glad/include"
    "${CMAKE_CURRENT_SOURCE_DIR}/lib/glm"
)
