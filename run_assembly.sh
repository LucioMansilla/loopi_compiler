

./build/Compiler  tests/test.txt 
echo "============================="
gcc output.s src/backend/assembly-codegen/asm_io.c  
./a.out
