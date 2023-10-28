#include "ast.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "symbol_table.h"

int curr_offset = 0;

int get_next_offset() {
    curr_offset -= 16;
    return curr_offset;
}

ASTNode* create_methods_decl_list_node(ASTNode* left, ASTNode* right) {
    Attributes* attr = create_attributes(NOT_TYPE, 0, "METHODS_DECL_LIST", 0, CLASS_METHODS_DECL_LIST);
    return create_ast_node(attr, left, right);
}

ASTNode* create_return_expr_node(ASTNode* left, int line) {
    Attributes* attr = create_attributes(NOT_TYPE, 0, "RETURN_EXPR", line, CLASS_RETURN_EXPR);
    return create_ast_node(attr, left, NULL);
}

ASTNode* create_return_node(int line) {
    Attributes* attr = create_attributes(TYPE_VOID, 0, "RETURN", line, CLASS_RETURN);
    return create_ast_node(attr, NULL, NULL);
}

ASTNode* create_ast_node(Attributes* info, ASTNode* left, ASTNode* right) {
    ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
    node->info = info;
    node->left = left;
    node->right = right;
    return node;
}

ASTNode* create_call_func_node(Attributes* info, ASTNode* expr_list_params, int line) {
    Attributes* new_info = create_attributes(info->value_type, info->value, info->tag, line, CLASS_CALL_FUNCTION);
    new_info->parameter_list = info->parameter_list;
    return create_ast_node(new_info, expr_list_params, NULL);
}

ASTNode* create_sentence_list_node(ASTNode* left, ASTNode* right) {
    Attributes* attr = create_attributes(NOT_TYPE, 0, "SENTENCE_LIST", 0, CLASS_SENTENCE_LIST);
    return create_ast_node(attr, left, right);
}

ASTNode* create_list_call_node(ASTNode* left, ASTNode* right) {
    Attributes* attr = create_attributes(NOT_TYPE, 0, ";", 0, CLASS_ACTUAL_PARAM);
    return create_ast_node(attr, left, right);
}

ASTNode* create_decl_func_node(Attributes* info, ASTNode* body) {
    return create_ast_node(info, body, NULL);
}

ASTNode* create_int_node(int value, int line) {
    Attributes* attr = create_attributes(TYPE_INT, value, "INT", line, CLASS_CONSTANT);
    return create_ast_node(attr, NULL, NULL);
}

ASTNode* create_bool_node(int value, int line) {
    Attributes* attr = create_attributes(TYPE_BOOL, value, "BOOL", line, CLASS_CONSTANT);
    return create_ast_node(attr, NULL, NULL);
}

ASTNode* create_id_node(char* id, int line) {
    Attributes* attr = create_attributes(NOT_TYPE, 0, id, line, CLASS_VAR);
    attr->offset = get_next_offset();
    return create_ast_node(attr, NULL, NULL);
}

ASTNode* create_assign_node(ASTNode* left, ASTNode* right, int line) {
    Attributes* attr = create_attributes(NOT_TYPE, 0, "=", line, CLASS_ASSIGN);
    return create_ast_node(attr, left, right);
}

ASTNode* create_single_decl_node(ValueType value_type, ASTNode* left, ASTNode* right, int line) {
    Attributes* attr = create_attributes(value_type, 0, "=", line, CLASS_DECL);
    return create_ast_node(attr, left, right);
}

ASTNode* create_list_decl_node(ASTNode* left, ASTNode* right) {
    Attributes* attr = create_attributes(NOT_TYPE, 0, "DECL_LIST", 0, CLASS_DECL_LIST);
    return create_ast_node(attr, left, right);
}
ASTNode* create_program_node(ASTNode* left, ASTNode* right) {
    Attributes* attr = create_attributes(NOT_TYPE, 0, "PROGRAM", 0, CLASS_PROGRAM);
    return create_ast_node(attr, left, right);
}

// Utilizaremos esta variable para asignar IDs únicos a los nodos
int nodeId = 0;

void generate_dot(ASTNode* node, FILE* fp) {
    if (node == NULL) return;

    int currentId = nodeId++;
    fprintf(fp, "  %d [label=\"", currentId);

    switch (node->info->class_type) {
        case CLASS_CONSTANT:
            fprintf(fp, "CONSTANT\\nValor: %d\\nTipo: ", node->info->value);
            if (node->info->value_type == TYPE_INT) {
                fprintf(fp, "int");
            } else if (node->info->value_type == TYPE_BOOL) {
                fprintf(fp, "bool");
            }
            break;
        default:
            if (node->info->tag != NULL) fprintf(fp, "%s", node->info->tag);
            break;
    }

    fprintf(fp, "\"];\n");

    if (node->left != NULL) {
        int leftId = nodeId;
        generate_dot(node->left, fp);
        fprintf(fp, "  %d -> %d;\n", currentId, leftId);
    }

    if (node->middle != NULL) {
        int middleId = nodeId;
        generate_dot(node->middle, fp);
        fprintf(fp, "  %d -> %d;\n", currentId, middleId);
    }

    if (node->right != NULL) {
        int rightId = nodeId;
        generate_dot(node->right, fp);
        fprintf(fp, "  %d -> %d;\n", currentId, rightId);
    }
}

void generate_dot_file(ASTNode* root, const char* filename) {
    FILE* fp = fopen(filename, "w");
    fprintf(fp, "digraph AST {\n");
    generate_dot(root, fp);
    fprintf(fp, "}\n");
    fclose(fp);
}

ASTNode* create_if_node(ASTNode* condition, ASTNode* block, int line) {
    Attributes* attr = create_attributes(NOT_TYPE, 0, "IF NODE", line, CLASS_IF);
    ASTNode* new_tree = create_ast_node(attr, condition, NULL);
    new_tree->middle = block;
    new_tree->middle->info->tag = "IF_BLOCK";
    return new_tree;
}

ASTNode* create_if_else_node(ASTNode* condition, ASTNode* true_block, ASTNode* false_block, int line) {
    Attributes* attr = create_attributes(NOT_TYPE, 0, "IF ELSE NODE", line, CLASS_IF_THEN_ELSE);
    ASTNode* new_tree = create_ast_node(attr, condition, false_block);
    new_tree->middle = true_block;
    new_tree->middle->info->tag = "IF_BLOCK";
    new_tree->right->info->tag = "ELSE_BLOCK";
    return new_tree;
}

ASTNode* create_while_node(ASTNode* condition, ASTNode* block, int line) {
    Attributes* attr = create_attributes(NOT_TYPE, 0, "WHILE", line, CLASS_WHILE);
    return create_ast_node(attr, condition, block);
}

ASTNode* create_empty_node(int line) {
    Attributes* attr = create_attributes(NOT_TYPE, 0, " ; ", line, CLASS_EMPTY);
    return create_ast_node(attr, NULL, NULL);
}

ASTNode* create_block_node(ASTNode* left, ASTNode* right, int line) {
    Attributes* attr = create_attributes(NOT_TYPE, 0, "BLOCK", line, CLASS_BLOCK);

    return create_ast_node(attr, left, right);
}