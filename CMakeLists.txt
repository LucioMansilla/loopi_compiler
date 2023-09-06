cmake_minimum_required(VERSION 3.10)
project(Compiler)

set(CMAKE_C_STANDARD 11)

find_package(BISON)
find_package(FLEX)

FLEX_TARGET(MyScanner src/calc-lexico.l  ${CMAKE_CURRENT_BINARY_DIR}/lex.yy.c)
BISON_TARGET(MyParser src/calc-sintaxis.y ${CMAKE_CURRENT_BINARY_DIR}/calc-sintaxis.tab.c)
ADD_FLEX_BISON_DEPENDENCY(MyScanner MyParser)

include_directories(${CMAKE_CURRENT_BINARY_DIR} src/)

add_executable(Compiler ${BISON_MyParser_OUTPUTS} ${FLEX_MyScanner_OUTPUTS} src/main.c src/ast.c src/attributes.c src/symbol_table.c src/semantic.c src/errors.c src/eval.c src/instruction3dir.c)
target_link_libraries(Compiler ${FLEX_LIBRARIES} ${BISON_LIBRARIES})
