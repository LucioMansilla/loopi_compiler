#!/bin/bash

cd build

BUILD_TYPE="Debug"

# Check if an argument was provided
if [ "$1" != "" ]; then
    if [ "$1" == "False" ]; then
        BUILD_TYPE="Release"
    fi
fi

# Check if CMakeCache.txt already exists.
if [ ! -f CMakeCache.txt ]; then
    cmake ..
    cmake -DCMAKE_BUILD_TYPE=$BUILD_TYPE ..
fi

cmake --build .
