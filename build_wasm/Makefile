# makefile that builds the wasm binary (engine)
EMCPP = em++
EMCC = emcc

EMFLAGS = -sWASM=1 --no-entry

SRC = ../src/engine/src
INCLUDE = -I../src/engine/include -I../src/include -I../src/lib/glm -I../src/lib/toml11 -I../src/lib/SQLiteCpp/include -I../src/lib/glfw/include -I../src/lib/glad/include -I../src/lib/freetype/include -I../src/gui/lib/imgui -I../src/gui/lib/imgui/misc/cpp
# obj files will be placed in obj/
OBJ = obj/

# all the .cpp files in the src directory and subdirectories
# take all cpp files also from ../src/gui/lib/imgui, ../src/gui/lib/imgui/misc/cpp, ../src/lib/glad/src (c files), ../src/lib/glfw/src (c files, except cocoa_time.c posix_module.c posix_thread.c)
SRCS = $(wildcard $(SRC)/*.cpp) $(wildcard $(SRC)/*/*.cpp) $(wildcard ../src/gui/lib/imgui/*.cpp) $(wildcard ../src/gui/lib/imgui/misc/cpp/*.cpp) $(wildcard ../src/lib/glad/src/*.c) $(wildcard ../src/lib/glfw/src/*.c) 

all: $(OBJ)/engine.wasm

clean:
	rm -rf $(OBJ)

$(OBJ)/engine.wasm: $(SRCS)
	$(EMCPP) $(EMFLAGS) $(INCLUDE) $(SRCS) -o $(OBJ)/engine.wasm
