#ifndef PSEUDOCODEGEN_H
#define PSEUDOCODEGEN_H
#include "instruction3dir.h"
#include "structures/ast.h"

InstructionList* generate_tac(ASTNode* node);
void generate_binary_operator(ASTNode* node, CodOp op, InstructionList* list);
#endif