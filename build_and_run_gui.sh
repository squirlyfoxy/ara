echo "----------------------------------------"
echo "  ARA Game engine build and run script"
echo "----------------------------------------"
echo "1. Building the engine"
cd build
ninja

echo "2. Building the server for web build"
cd ../src/engine/jsbuild
sh build.sh

cd ../../../bin
echo ""
./gui