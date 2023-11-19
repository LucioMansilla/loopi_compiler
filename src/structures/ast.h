#ifndef AST_H
#define AST_H
#include "attributes.h"

typedef struct ASTNode {
    Attributes* info;
    struct ASTNode* left;
    struct ASTNode* middle;
    struct ASTNode* right;
} ASTNode;

ASTNode* create_ast_node(Attributes* info, ASTNode* left, ASTNode* right);
ASTNode* create_int_node(int value, int line);
ASTNode* create_bool_node(int value, int line);
ASTNode* create_id_node(char* id, int line);
ASTNode* create_return_node(int line);
ASTNode* create_return_expr_node(ASTNode* left, int line);
ASTNode* create_assign_node(ASTNode* left, ASTNode* right, int line);
ASTNode* create_single_decl_node(ValueType value_type, ASTNode* left, ASTNode* right, int line);
ASTNode* create_program_node(ASTNode* left, ASTNode* right);
ASTNode* create_if_node(ASTNode* condition, ASTNode* block, int line);
ASTNode* create_if_else_node(ASTNode* condition, ASTNode* true_block, ASTNode* false_block, int line);
ASTNode* create_while_node(ASTNode* condition, ASTNode* block, int line);
ASTNode* create_block_node(ASTNode* left, ASTNode* right, int line);
ASTNode* create_decl_func_node(Attributes* info, ASTNode* body);
ASTNode* create_call_func_node(Attributes* info, ASTNode* expr_list_params, int line);
ASTNode* create_empty_node(int line);
ASTNode* create_sentence_list_node(ASTNode* left, ASTNode* right);
ASTNode* create_list_decl_node(ASTNode* left, ASTNode* right);
ASTNode* create_list_call_node(ASTNode* left, ASTNode* right);
ASTNode* create_methods_decl_list_node(ASTNode* left, ASTNode* right);
ASTNode* create_global_decl_node(ValueType value_type, ASTNode* left, ASTNode* right, int line);
ASTNode* create_id_global(char* id, int line);

int get_next_offset();
void print_ast(ASTNode* node);
void generate_dot_file(ASTNode* root, const char* filename);

#endif  // AST_H