cmake_minimum_required(VERSION 3.23)
project(gui)

# include header files
include_directories(include)
include_directories(../include)
include_directories(../engine/include)

# glm
include_directories(../lib/glm)

# source files (all .cpp files in the src and lib directories)
file(GLOB_RECURSE SRCS 
    src/*.cpp
    src/*/*.cpp
    src/*/*/*.cpp
    src/*/*/*/*.cpp
    lib/imgui/*.cpp
    lib/imgui/backends/*.cpp

    lib/imgui/misc/cpp/*.cpp
)

# imgui library include
include_directories(lib/imgui)
include_directories(lib/imgui/misc/cpp)

# c++ 20
set(CMAKE_CXX_STANDARD 20)

add_executable(gui main.cpp ${SRCS})
target_link_libraries(gui engine glad SQLiteCpp)
