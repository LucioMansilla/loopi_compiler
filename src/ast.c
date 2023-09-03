#include "ast.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "symbol_table.h"

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

ASTNode* create_return_node(ASTNode* node, int line) {  // el hijo izq es el hijo return
    Attributes* attr = create_attributes(NOT_TYPE, 0, NULL, line, CLASS_RETURN);
    return create_ast_node(attr, node, NULL);
}
ASTNode* create_assign_node(ASTNode* left, ASTNode* right, int line) {
    Attributes* attr = create_attributes(NOT_TYPE, '=', NULL, line, CLASS_ASSIGN);
    return create_ast_node(attr, left, right);
}

ASTNode* create_sentence_list_node(ASTNode* left, ASTNode* right) {
    Attributes* attr = create_attributes(NOT_TYPE, 0, NULL, 0, CLASS_SENTENCE_LIST);
    return create_ast_node(attr, left, right);
}

ASTNode* create_single_decl_node(ValueType valueType, ASTNode* left, ASTNode* right, int line) {
    Attributes* attr = create_attributes(valueType, '=', 0, line, CLASS_DECL);
    return create_ast_node(attr, left, right);
}

ASTNode* create_list_decl_node(ASTNode* left, ASTNode* right) {
    Attributes* attr = create_attributes(NOT_TYPE, 0, NULL, 0, CLASS_DECL_LIST);
    return create_ast_node(attr, left, right);
}
ASTNode* create_program_node(ASTNode* left, ASTNode* right) {
    Attributes* attr = create_attributes(TYPE_VOID, 0, NULL, 0, CLASS_PROGRAM);
    return create_ast_node(attr, left, right);
}

// El nodo en este punto ya esta etiquetado y los programas terminan en return 
int eval(ASTNode* node, SymbolTable* table) {
    Attributes* left = NULL;
    if (node == NULL) return 0;

    switch (node->info->classType) {
        case CLASS_PROGRAM:
            eval(node->left, table);
            eval(node->right, table);
            break;
        case CLASS_CONSTANT:
            return node->info->value;
            break;

        case CLASS_VAR:
            return node->info->value;
            break;

        case CLASS_DECL:
            left = lookup_symbol(table, node->left->info->tag);
            left->value = eval(node->right, table);
            break;
        case CLASS_ASSIGN:
            left = lookup_symbol(table, node->left->info->tag);
            left->value = eval(node->right, table);
            break;
        case CLASS_DECL_LIST:
            eval(node->left, table);
            eval(node->right, table);
            break;
        case CLASS_SENTENCE_LIST:
            eval(node->left, table);
            eval(node->right, table);
            break;
        case CLASS_RETURN:
            eval(node->left, table);
            if (node->left->info->valueType == TYPE_INT)
                printf("ResultadoEntero: %d\n", node->left->info->value);
            else if (node->left->info->value) {
                printf("ResultadoTRue: True\n");
            } else
                printf("ResultadoFalse: False\n");
            break;
        case CLASS_OPERATION:
            eval(node->left, table);
            eval(node->right, table);
            if (node->info->valueType == TYPE_INT) {
                if (node->info->tag[0] == '+')
                    node->info->value = node->left->info->value + node->right->info->value;
                else if (node->info->tag[0] == '*')
                    node->info->value = node->left->info->value * node->right->info->value;
            } else {
                if (node->info->tag[0] == '+')
                    node->info->value = node->left->info->value || node->right->info->value;
                else if (node->info->tag[0] == '*')
                    node->info->value = node->left->info->value && node->right->info->value;
            }
            return node->info->value;
            break;
    }
}

// Utilizaremos esta variable para asignar IDs únicos a los nodos
int nodeId = 0;

void generate_dot(ASTNode* node, FILE* fp) {
    if (node == NULL) return;

    // Imprimimos la etiqueta del nodo actual
    int currentId = nodeId++;
    fprintf(fp, "  %d [label=\"", currentId);

    switch (node->info->classType) {
        case CLASS_CONSTANT:
            fprintf(fp, "CONSTANT\\nValor: %d\\nTipo: ", node->info->value);
            if (node->info->valueType == TYPE_INT) {
                fprintf(fp, "int");
            } else if (node->info->valueType == TYPE_BOOL) {
                fprintf(fp, "bool");
            }
            break;
        case CLASS_VAR:
            fprintf(fp, "VARIABLE\\nNombre: %s\\nTipo: ", node->info->tag);
            if (node->info->valueType == TYPE_INT) {
                fprintf(fp, "int");
            } else if (node->info->valueType == TYPE_BOOL) {
                fprintf(fp, "bool");
            }
            break;
        case CLASS_OPERATION:
            fprintf(fp, "OPERACIÓN\\nOperador: %c\\nTipo: ", node->info->tag[0]);
            if (node->info->valueType == TYPE_INT) {
                fprintf(fp, "int");
            } else if (node->info->valueType == TYPE_BOOL) {
                fprintf(fp, "bool");
            }
            break;
        case CLASS_RETURN:
            fprintf(fp, "RETURN\\nTipo: ");
            if (node->info->valueType == TYPE_INT) {
                fprintf(fp, "int");
            } else if (node->info->valueType == TYPE_BOOL) {
                fprintf(fp, "bool");
            }
            break;
        case CLASS_ASSIGN:
            fprintf(fp, "ASIGN\\nTipo: ");
            if (node->info->valueType == TYPE_INT) {
                fprintf(fp, "int");
            } else if (node->info->valueType == TYPE_BOOL) {
                fprintf(fp, "bool");
                break;
                case CLASS_DECL:
                    fprintf(fp, "DECL\\nTipo: ");
                    if (node->info->valueType == TYPE_INT) {
                        fprintf(fp, "int");
                    } else if (node->info->valueType == TYPE_BOOL) {
                        fprintf(fp, "bool");
                    } else if (node->info->valueType == TYPE_STRING) {
                        fprintf(fp, "string");
                    } else if (node->info->valueType == TYPE_VOID) {
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
