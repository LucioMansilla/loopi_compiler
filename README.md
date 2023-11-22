# LP Language Compiler

This project consists of a compiler developed in C as a practical work for the "Software Design Workshop" course. The compiler takes as input programs written in the LP Language and generates x86-64 assembly code.

## Project Structure

The project has the following folder structure:

- **src/**: Source code of the compiler divided into modules
  - **backend/**: Intermediate and assembly code generation 
  - **error-handling/**: Error handler
  - **frontend/**: Lexical, syntactic and semantic analysis
  - **structures/**: Data structures used
- **tests/**: Test suite
  - **accept/**: Valid test cases that should be accepted
  - **reject/**: Invalid test cases that should be rejected   
- **build.sh**: Script to build the compiler  
- **test.sh**: Script to execute the test suite
- **loopi.sh**: Script to compile, link and execute .lp programs
- **report/**: Documentation and project report   

## Dependencies   

The following dependencies are required to build and execute the compiler:

- [CMake >= 3.10](https://cmake.org/)
- C Compiler (GCC recommended)  
- In some cases g++

## Compilation and Execution

### To build the compiler execute:   

```bash
./build.sh  
```

This will generate the **Compiler** executable inside **build/** that can be used to compile .lp programs.

### To execute the test suite:  

```bash   
./test.sh
```  

Test results will be informed via standard error output.

### To compile and execute a .lp program:

```bash
./loopi.sh path/to/program.lp  
```

For example, to execute **tests/accept/test_fib.lp**:

```bash   
./loopi.sh tests/accept/test_fib.lp   
```

## Documentation   

The **report/** folder contains a detailed report of the project development, configurations, relevant decisions and limitations.  

## Authors   

- Brenda Dichiara
- Lucio Mansilla