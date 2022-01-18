#!/bin/sh
[ ! -e build ] && mkdir build

(
    export \
        CC=/usr/lib/llvm/13/bin/clang \
        CXX=/usr/lib/llvm/13/bin/clang++ \
    &&
    cd build &&
    cmake .. \
        -G Ninja \
        -DCMAKE_C_FLAGS=-m32 \
        -DCMAKE_CXX_FLAGS=-m32 \
        -DCMAKE_BUILD_TYPE=Debug \
    &&
    cmake --build . --config Debug
)
