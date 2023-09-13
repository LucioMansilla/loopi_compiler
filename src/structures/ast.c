#include "ast.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

ASTNode* create_ast_node(Attributes* info, ASTNode* left, ASTNode* right) {
    ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
    node->info = info;
    node->left = left;
    node->right = right;
    return node;
}

ASTNode* create_int_node(int value, int line) {
    Attributes* attr = create_attributes(TYPE_INT, value, NULL, line, CLASS_CONSTANT);
    return create_ast_node(attr, NULL, NULL);
}

ASTNode* create_bool_node(int value, int line) {
    Attributes* attr = create_attributes(TYPE_BOOL, value, NULL, line, CLASS_CONSTANT);
    return create_ast_node(attr, NULL, NULL);
}

ASTNode* create_id_node(char* id, int line) {
    Attributes* attr = create_attributes(NOT_TYPE, 0, id, line, CLASS_VAR);
    return create_ast_node(attr, NULL, NULL);
}

ASTNode* create_return_node(ASTNode* node, int line) {
    Attributes* attr = create_attributes(NOT_TYPE, 0, NULL, line, CLASS_RETURN);
    return create_ast_node(attr, node, NULL);
}

ASTNode* create_assign_node(ASTNode* left, ASTNode* right, int line) {
    Attributes* attr = create_attributes(NOT_TYPE, 0, "=", line, CLASS_ASSIGN);
    return create_ast_node(attr, left, right);
}

ASTNode* create_sentence_list_node(ASTNode* left, ASTNode* right) {
    Attributes* attr = create_attributes(NOT_TYPE, 0, NULL, 0, CLASS_SENTENCE_LIST);
    return create_ast_node(attr, left, right);
}

ASTNode* create_single_decl_node(ValueType value_type, ASTNode* left, ASTNode* right, int line) {
    Attributes* attr = create_attributes(value_type, 0, "=", line, CLASS_DECL);
    return create_ast_node(attr, left, right);
}

ASTNode* create_list_decl_node(ASTNode* left, ASTNode* right) {
    Attributes* attr = create_attributes(NOT_TYPE, 0, NULL, 0, CLASS_DECL_LIST);
    return create_ast_node(attr, left, right);
}
ASTNode* create_program_node(ASTNode* left, ASTNode* right) {
    Attributes* attr = create_attributes(NOT_TYPE, 0, NULL, 0, CLASS_PROGRAM);
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
        case CLASS_VAR:
            fprintf(fp, "VARIABLE\\nNombre: %s\\nTipo: ", node->info->tag);
            if (node->info->value_type == TYPE_INT) {
                fprintf(fp, "int");
            } else if (node->info->value_type == TYPE_BOOL) {
                fprintf(fp, "bool");
            }
            break;
        case CLASS_ADD:
        case CLASS_MUL:
            fprintf(fp, "OPERACIÓN\\nOperador: %c\\nTipo: ", node->info->tag[0]);
            if (node->info->value_type == TYPE_INT) {
                fprintf(fp, "int");
            } else if (node->info->value_type == TYPE_BOOL) {
                fprintf(fp, "bool");
            }
            break;
        case CLASS_RETURN:
            fprintf(fp, "RETURN\\nTipo: ");
            if (node->info->value_type == TYPE_INT) {
                fprintf(fp, "int");
            } else if (node->info->value_type == TYPE_BOOL) {
                fprintf(fp, "bool");
            }
            break;
        case CLASS_ASSIGN:
            fprintf(fp, "ASIGN\\nTipo: ");
            if (node->info->value_type == TYPE_INT) {
                fprintf(fp, "int");
            } else if (node->info->value_type == TYPE_BOOL) {
                fprintf(fp, "bool");
                break;
                case CLASS_DECL:
                    fprintf(fp, "DECL\\nTipo: ");
                    if (node->info->value_type == TYPE_INT) {
                        fprintf(fp, "int");
                    } else if (node->info->value_type == TYPE_BOOL) {
                        fprintf(fp, "bool");
                    } else if (node->info->value_type == TYPE_STRING) {
                        fprintf(fp, "string");
                    } else if (node->info->value_type == TYPE_VOID) {
                        fprintf(fp, "void");
                    }
                    break;
                case CLASS_SENTENCE_LIST:
                    fprintf(fp, "SENTENCE LIST");
                    break;
                case CLASS_PROGRAM:
                    fprintf(fp, "PROGRAM");
                    break;
                case CLASS_DECL_LIST:
                    fprintf(fp, "DECL LIST");
                    break;
                default:
                    fprintf(fp, "Tipo de nodo desconocido");
                    break;
            }
    }

    fprintf(fp, "\"];\n");

    if (node->left != NULL) {
        int leftId = nodeId;
        generate_dot(node->left, fp);
        fprintf(fp, "  %d -> %d;\n", currentId, leftId);
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
ASTNode* create_if_node(ASTNode* condition, ASTNode* true_branch, ASTNode* false_branch, int line) {
    Attributes* attr = create_attributes(NOT_TYPE, 0, NULL, line, CLASS_IF);
    return create_ast_node(attr, condition, true_branch);
}