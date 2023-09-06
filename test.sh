./build.sh
# Variable para contar tests fallidos
failed=0

# Loop para todos los archivos de prueba en el directorio 'tests/accept'
for example in tests/accept/*.txt; do
    echo "Testing $example..."

    # Extraer el output esperado del archivo de prueba
    expected_output=$(grep '^# expected =' $example | cut -d'=' -f2 | tr -d ' ')

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
