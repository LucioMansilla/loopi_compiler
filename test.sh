./build.sh
# Variable para contar tests fallidos
failed=0

# Loop para todos los archivos de prueba en el directorio 'tests/accept'
for example in tests/accept/*.txt tests/reject/*.txt; do

    if echo "$example" | grep -q "tests/accept"; then
        expected_output=$(grep '^# expected =' $example | cut -d'=' -f2 | tr -d ' ' | tr -d '\n')
    else
        expected_output=$(grep '^# expected =' $example | cut -d'=' -f2 | tr -s ' ' | tr -d '\n')
    fi

    echo "Testing $example ..."

    # Ejecutar el compilador en el archivo de prueba y capturar el output (ignorando stderr)
    output=$(./build/Compiler $example 2>/dev/null)
    

    # Comparar el output del compilador con el output esperado
    if [ "$output" != "$expected_output" ]; then
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
