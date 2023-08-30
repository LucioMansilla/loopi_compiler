#ifndef AST_H
#define AST_H
#include "attributes.h"

typedef struct ASTNode {
    Attributes* info;
    struct ASTNode* left;
    struct ASTNode* right;
} ASTNode;

ASTNode* create_ast_node(Attributes* info, ASTNode* left, ASTNode* right);

#endif  // AST_H