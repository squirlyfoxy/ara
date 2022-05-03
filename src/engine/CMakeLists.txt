cmake_minimum_required(VERSION 3.23)
project(engine)

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

# will build as a dynamic library

add_library(engine SHARED ${SRCS})
