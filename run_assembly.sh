

./build/Compiler  tests/test_func_offset.txt
echo "============================="
gcc output.s src/backend/assembly-codegen/asm_io.c  
./a.out
