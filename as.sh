./build/Compiler  tests/syntax_error.txt
echo "============================="
as output.s -o program.o
ld program.o -o program
./program
echo $?
