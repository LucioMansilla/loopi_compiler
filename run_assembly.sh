

./build/Compiler  tests/test_minus.txt
echo "============================="
gcc output.s src/backend/assembly-codegen/asm_io.c  
./a.out
