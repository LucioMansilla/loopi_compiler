#include "attributes.h"

typedef struct ASTNode {
    Attributes* info;
    struct ASTNode* left;
    struct ASTNode* right;
} ASTNode;

typedef struct AST {
    ASTNode* root;
} AST;

ASTNode* create_ast_node(Attributes* info, ASTNode* left, ASTNode* right);
AST* create_ast(ASTNode* root);
void traverse_ast(AST* ast);
void destroy_ast(AST* ast);
