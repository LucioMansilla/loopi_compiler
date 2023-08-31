#ifndef AST_H
#define AST_H
#include "attributes.h"
#include "symbol_table.h"

typedef struct ASTNode {
    Attributes* info;
    struct ASTNode* left;
    struct ASTNode* right;
} ASTNode;

ASTNode* create_ast_node(Attributes* info, ASTNode* left, ASTNode* right);
ASTNode* create_int_node(int value, int line);
ASTNode* create_bool_node(int value, int line);
ASTNode* create_id_node(char* id, int line);
ASTNode* create_return_node(ASTNode* node, int line);
ASTNode* create_assign_node(ASTNode* left, ASTNode* right, int line);
ASTNode* create_sentence_list_node(ASTNode* left, ASTNode* right);
ASTNode* create_single_decl_node(ValueType valueType, ASTNode* left, ASTNode* right, int line);
ASTNode* create_list_decl_node(ASTNode* left, ASTNode* right);
ASTNode* create_program_node(ASTNode* left, ASTNode* right);
Attributes* check_types(ASTNode* node,SymbolTable* table);
void print_ast(ASTNode* node);
#endif  // AST_H