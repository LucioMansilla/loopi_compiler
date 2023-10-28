

./build/Compiler  tests/test_call_function.txt
echo "============================="
gcc output.s src/backend/assembly-codegen/asm_io.c  
./a.out
