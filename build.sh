echo "----------------------------------------"
echo "      ARA Game engine build script"
echo "----------------------------------------"
echo "1. Building the engine"
echo "   -> Building the engine"
sh ./prepare.sh
cd build
ninja

cd ..
echo "   -> Preparing the WASM build"
cd tools/emscripten
source ./emsdk_env.sh
cd ../..

#cd build_wasm
#echo "   -> Building.."
#make

#cd ..

echo "2. Building the server for web build"
cd ./src/engine/jsbuild
sh build.sh

echo "OK"
