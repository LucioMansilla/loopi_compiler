#!/bin/bash

./build.sh
# Variable para contar tests fallidos
failed=0

# Loop para todos los archivos de prueba en el directorio 'tests/accept'
for example in tests/accept/*.txt tests/reject/*.txt; do

    if echo "$example" | grep -q "tests/accept"; then
        expected_output=$(grep '^# expected =' $example | cut -d'=' -f2- | tr -d ' ' | tr '\n' ';' | sed 's/;$//')
    else
        expected_output=$(grep '^# expected =' $example | cut -d'=' -f2- | tr -s ' ' | tr '\n' ';' | sed 's/;$//')
    fi

    echo "Testing $example ..."

    # Ejecutar el compilador en el archivo de prueba y capturar el output (ignorando stderr)
    output=$(./build/Compiler $example 2>/dev/null | tr '\n' ';' | sed 's/;$//')
    
    IFS=';' read -ra expected_array <<< "$expected_output"
    IFS=';' read -ra output_array <<< "$output"
    
    # Clasifica los arrays para facilitar la comparación
    sorted_expected=$(printf '%s\n' "${expected_array[@]}" | sort | tr '\n' ';')
    sorted_output=$(printf '%s\n' "${output_array[@]}" | sort | tr '\n' ';')
    
    # Comparar el output del compilador con el output esperado
    if [ "$sorted_output" != "$sorted_expected" ]; then
        echo "Test failed!"
        echo "Expected: $expected_output"
        echo "Got: $output"
        failed=$((failed + 1))
    else
        echo "Test passed!"
    fi
done

# Imprimir resumen
if [ $failed -eq 0 ]; then
    echo "All tests passed!"
    cat test_passed.txt
else
    echo "$failed tests failed."
    exit 1
fi
 Variable para contar tests fallidos
failed=0

# Loop para todos los archivos de prueba en el directorio 'tests/accept'
for example in tests/accept/*.txt tests/reject/*.txt; do

    if echo "$example" | grep -q "tests/accept"; then
        expected_output=$(grep '^# expected =' $example | cut -d'=' -f2- | tr -d ' ' | tr '\n' ';' | sed 's/;$//')
    else
        expected_output=$(grep '^# expected =' $example | cut -d'=' -f2- | tr -s ' ' | tr '\n' ';' | sed 's/;$//')
    fi

    echo "Testing $example ..."

    # Ejecutar el compilador en el archivo de prueba y capturar el output (ignorando stderr)
    output=$(./build/Compiler $example 2>/dev/null | tr '\n' ';' | sed 's/;$//')
    
    IFS=';' read -ra expected_array <<< "$expected_output"
    IFS=';' read -ra output_array <<< "$output"
    
    # Clasifica los arrays para facilitar la comparación
    sorted_expected=$(printf '%s\n' "${expected_array[@]}" | sort | tr '\n' ';')
    sorted_output=$(printf '%s\n' "${output_array[@]}" | sort | tr '\n' ';')
    
    # Comparar el output del compilador con el output esperado
    if [ "$sorted_output" != "$sorted_expected" ]; then
        echo "Test failed!"
        echo "Expected: $expected_output"
        echo "Got: $output"
        failed=$((failed + 1))
    else
        echo "Test passed!"
    fi
done

# Imprimir resumen
if [ $failed -eq 0 ]; then
    echo "All tests passed!"
    cat test_passed.txt
else
    echo "$failed tests failed."
    exit 1
fi
 Variable to count failed tests
failed=0

# Loop through all test files in the 'tests/accept' directory
for example in tests/accept/*.txt tests/reject/*.txt; do

    if echo "$example" | grep -q "tests/accept"; then
        expected_output=$(grep '^# expected =' $example | cut -d'=' -f2- | tr -d ' ' | tr '\n' ';' | sed 's/;$//')
    else
        expected_output=$(grep '^# expected =' $example | cut -d'=' -f2- | tr -s ' ' | tr '\n' ';' | sed 's/;$//')
    fi

    echo "Testing $example ..."

    # Run the compiler on the test file and capture the output (ignoring stderr)
    output=$(./build/Compiler $example 2>/dev/null | tr '\n' ';' | sed 's/;$//')
    
    IFS=';' read -ra expected_array <<< "$expected_output"
    IFS=';' read -ra output_array <<< "$output"
    
    # Sort the arrays for easier comparison
    sorted_expected=$(printf '%s\n' "${expected_array[@]}" | sort | tr '\n' ';')
    sorted_output=$(printf '%s\n' "${output_array[@]}" | sort | tr '\n' ';')
    
    # Compare the compiler output with the expected output
    if [ "$sorted_output" != "$sorted_expected" ]; then
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
