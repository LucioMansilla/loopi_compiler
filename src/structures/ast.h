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
ASTNode* create_return_node(ASTNode* node, int line);
ASTNode* create_assign_node(ASTNode* left, ASTNode* right, int line);
ASTNode* create_sentence_list_node(ASTNode* left, ASTNode* right);
ASTNode* create_single_decl_node(ValueType value_type, ASTNode* left, ASTNode* right, int line);
ASTNode* create_list_decl_node(ASTNode* left, ASTNode* right);
ASTNode* create_program_node(ASTNode* left, ASTNode* right);
ASTNode* create_if_node(ASTNode* condition, ASTNode* true_branch, ASTNode* false_branch, int line);
ASTNode* create_decl_func(ValueType value_type, char* name, char* parameter_list, ASTNode* body, int line);

int get_next_offset();
void print_ast(ASTNode* node);
void generate_dot_file(ASTNode* root, const char* filename);

#endif  // AST_H