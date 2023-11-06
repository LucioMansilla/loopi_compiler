

./build/Compiler  tests/test_call_f.txt
echo "============================="
gcc output.s src/backend/assembly-codegen/asm_io.c  
./a.out
