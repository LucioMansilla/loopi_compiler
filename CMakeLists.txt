cmake_minimum_required(VERSION 3.10)
project(Compiler)

set(CMAKE_C_STANDARD 11)

find_package(BISON)
find_package(FLEX)

FLEX_TARGET(MyScanner src/frontend/lexer.l  ${CMAKE_CURRENT_BINARY_DIR}/lex.yy.c)
BISON_TARGET(MyParser src/frontend/parser.y ${CMAKE_CURRENT_BINARY_DIR}/parser.tab.c)
ADD_FLEX_BISON_DEPENDENCY(MyScanner MyParser)

include_directories(${CMAKE_CURRENT_BINARY_DIR} src/  src/frontend/ src/structures/ src/backend/interpreter/
src/backend/intermediate-codegen/ src/backend/assembly-codegen/ src/error-handling/ src/backend/assembly-codegen/)

add_executable(Compiler ${BISON_MyParser_OUTPUTS} ${FLEX_MyScanner_OUTPUTS} src/main.c src/structures/stack.c src/structures/ast.c  src/frontend/symbol_table.c src/structures/attributes.c  src/error-handling/errors.c src/frontend/semantic.c src/backend/interpreter/eval.c src/backend/intermediate-codegen/instruction3dir.c src/backend/assembly-codegen/assembly-codegen.c src/backend/intermediate-codegen/pseudo-codegen.c )
target_link_libraries(Compiler ${FLEX_LIBRARIES} ${BISON_LIBRARIES} m)
