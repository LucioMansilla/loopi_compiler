

./build/Compiler  tests/prueba.txt
echo "============================="
gcc output.s src/backend/assembly-codegen/asm_io.c  
./a.out
