#ifndef EVAL_H
#define EVAL_H
#include "ast.h"
#include "symbol_table.h"

void eval(ASTNode *node, SymbolTable *table);


#endif