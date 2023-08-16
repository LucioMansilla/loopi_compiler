#!/bin/bash

cd build

# Check if CMakeCache.txt already exists
if [ ! -f CMakeCache.txt ]; then
    cmake ..
fi

cmake --build .
