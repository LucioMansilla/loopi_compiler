

./build/Compiler  tests/accept/test_if.txt
echo "============================="
gcc output.s src/backend/assembly-codegen/asm_io.c  
./a.out
