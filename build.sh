#!/bin/bash

# Remove old build directory if it exists
if [ -d "build/" ]; then
    rm -r build/
fi

# Create a new build directory and navigate into it
mkdir build
cd build

BUILD_TYPE="Debug"

# Check if an argument was provided
if [ "$1" != "" ]; then
    if [ "$1" == "False" ]; then
        BUILD_TYPE="Release"
    fi
fi

# Run CMake and build the project
cmake -DCMAKE_BUILD_TYPE=$BUILD_TYPE ..
cmake --build .
