cmake_minimum_required(VERSION 3.23)
project(engine)

# include header files
include_directories(include)
include_directories(../include)

# glm
include_directories(../lib/glm)

# toml11
include_directories(../lib/toml11)

# freetype
include_directories(../lib/freetype/include)

# include imgui
include_directories(../gui/lib/imgui)
include_directories(../gui/lib/imgui/misc/cpp)

# source files (all .cpp files in the src directory)
file(GLOB_RECURSE SRCS 
    src/*.cpp
    src/*/*.cpp
    src/*/*/*.cpp
    src/*/*/*/*.cpp

    ../gui/lib/imgui/imgui/*.cpp
    ../gui/lib/imgui/imgui/backends/*.cpp

    ../gui/lib/imgui/imgui/misc/cpp/*.cpp
)

# c++ 20
set(CMAKE_CXX_STANDARD 20)

# will build as a dynamic library
# if not emscripten, then it will build as a static library
if(EMSCRIPTEN)
    add_library(engine STATIC ${SRCS})
    set_target_properties(engine PROPERTIES LINK_FLAGS "s WASM=1")

    # link against:
    target_link_libraries(engine glad freetype)
else()
    add_library(engine SHARED ${SRCS})

    # link against:
    target_link_libraries(engine glad glfw freetype)
endif()
