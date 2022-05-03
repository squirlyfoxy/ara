cmake_minimum_required(VERSION 3.23)
project(gui)

# include header files
include_directories(include)
include_directories(../include)

# source files (all .cpp files in the src directory)
file(GLOB_RECURSE SRCS 
    src/*.cpp
    src/*/*.cpp
    src/*/*/*.cpp
    src/*/*/*/*.cpp
)

add_executable(gui main.cpp ${SRCS})
target_link_libraries(gui engine)
