# Prepare CMake build environment

# enter the build directory and use CMakeLists.txt located in src/ to generate a ninja build file
mkdir build
cd build
cmake ../src -G Ninja -DWEB_B=0
