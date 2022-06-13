cmake_minimum_required(VERSION 3.10)
project(Glad)

if (EMSCRIPTEN)
    add_library(glad STATIC include/glad/glad.h src/glad.c)
else()
    add_library(glad SHARED include/glad/glad.h src/glad.c)
endif()

target_include_directories(glad PUBLIC include/)