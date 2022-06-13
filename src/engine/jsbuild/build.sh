# build into the bin directory
cd server
go build -o ../../../../bin/wbuild/server
cd ..

# copy web folder to bin directory
cp -r web ../bin/wbuild/
