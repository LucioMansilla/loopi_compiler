./build.sh
# Variable to count failed tests
failed=0

# Loop through all test files in the 'examples' directory
for example in examples/*.txt; do
    echo "Testing $example..."

    # Extract the expected output from the example file
    expected_output=$(grep '^# expected =' $example | cut -d'=' -f2 | tr -d ' ')

    # Run the compiler on the example file and capture the output (ignoring stderr)
    output=$(./build/Compiler $example 2>/dev/null)
    # Compare the compiler's output with the expected output
    if [ "$output" != "$expected_output" ]; then
        echo "Test failed!"
        echo "Expected: $expected_output"
        echo "Got: $output"
        failed=$((failed + 1))
    else
        echo "Test passed!"
    fi
done

# Print summary
if [ $failed -eq 0 ]; then
    echo "All tests passed!"
    cat test_passed.txt
else
    echo "$failed tests failed."
    exit 1
fi
