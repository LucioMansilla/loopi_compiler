#!/bin/bash

# Check if an argument is provided
if [ "$#" -ne 1 ]; then
    echo "Usage: $0 <program-path>"
    exit 1
fi

# Compile the provided program
if ./build/Compiler "$1"; then

    # Compile and link the generated assembly code
    gcc output.s src/backend/assembly-codegen/asm_io.c  

    # Run the program
    ./a.out
else
    echo "Compilation failed."
    exit 1
fi
