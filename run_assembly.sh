./build/Compiler  tests/syntax_error.txt
echo "============================="
gcc output.s src/backend/assembly-codegen/asm_io.c  
./a.out
