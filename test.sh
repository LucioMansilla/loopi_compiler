#!/bin/bash

./build.sh
# Variable to count failed tests
failed=0

# Loop through all test files in both directories
for example in tests/accept/*.lp tests/reject/*.lp; do

    # Extract the expected value from the first line of the test file
    expected_output=$(grep '^# expected =' $example | cut -d'=' -f2- | sed 's/^ *//;s/ *$//')

    echo "Testing $example ..."

    if echo "$example" | grep -q "tests/accept"; then
        # Logic for 'accept' tests
        ./build/Compiler $example > /dev/null 2>&1
        gcc output.s src/backend/assembly-codegen/asm_io.c > /dev/null 2>&1
        output=$(./a.out | tail -n 1)
    else
        # Logic for 'reject' tests
        output=$(./build/Compiler $example 2>&1)
    fi

    # Compare the program output with the expected output
    if [ "$output" != "$expected_output" ]; then
        echo "Test failed for $example!"
        echo "Expected: $expected_output"
        echo "Got: $output"
        failed=$((failed + 1))
    else
        echo "Test passed for $example!"
    fi

    rm -f a.out output.s
done

# Print summary
if [ $failed -eq 0 ]; then
    echo "All tests passed!"
    cat test_passed.txt
else
    echo "$failed tests failed."
    exit 1
fi
