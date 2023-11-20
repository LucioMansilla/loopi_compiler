

./build/Compiler  tests/accept/test_change_var_global.txt 
echo "============================="
gcc output.s src/backend/assembly-codegen/asm_io.c  
./a.out
