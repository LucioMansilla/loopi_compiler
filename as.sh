./build/Compiler  tests/accept/prog.txt
as output.s -o program.o
ld program.o -o program
./program
echo $?
