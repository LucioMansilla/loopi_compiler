#!/bin/bash
cd build

# Check if CMakeCache.txt already exists!.
if [ ! -f CMakeCache.txt ]; then
    cmake ..
    cmake -DCMAKE_BUILD_TYPE=Debug ..
fi
cmake --build .
