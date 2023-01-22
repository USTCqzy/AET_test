# cd AETLib
# make clean
# make
# make install
# cd ..

[[ -d build ]] && rm -rf build
mkdir build && cd build
cmake ..
make
