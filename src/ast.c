#include "ast.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "symbol_table.h"

// Simulamos una tabla de símbolos simple con un arreglo y su tamaño
#define MAX_VARIABLES 100

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

void print_ast(ASTNode* node) {
    if (node == NULL) return;

    switch (node->info->classType) {
        case CLASS_CONSTANT:
            printf("\n[CONSTANT, Valor: %d]", node->info->value);
            break;
        case CLASS_VAR:
            printf("\n[VARIABLE, Nombre: %s]", node->info->tag);
            break;
        case CLASS_OPERATION:
            printf("\n[OPERACIÓN, Operador: %c]", node->info->tag[0]);
            break;
        case CLASS_RETURN:
            printf("\n[RETURN]");
            break;
        case CLASS_ASSIGN:
            printf("\n[ASIGNACIÓN]");
            break;
        case CLASS_DECL:
            if (node->info->valueType == TYPE_INT) {
                printf("\n[DECLARACIÓN, Tipo: int]");
            } else if (node->info->valueType == TYPE_BOOL) {
                printf("\n[DECLARACIÓN, Tipo: bool]");
            } else if (node->info->valueType == TYPE_STRING) {
                printf("\n[DECLARACIÓN, Tipo: string]");
            } else if (node->info->valueType == TYPE_VOID) {
                printf("\n[DECLARACIÓN, Tipo: void]");
            }
            break;
        case CLASS_SENTENCE_LIST:
            printf("\n[SENTENCE LIST]");
            break;
        case CLASS_PROGRAM:
            printf("\n[PROGRAM]");
            break;
        case CLASS_DECL_LIST:
            printf("\n[DECL LIST]");
            break;
        default:
            printf("\n[Tipo de nodo desconocido]");
            break;
    }

    if (node->left != NULL) printf("(");
    print_ast(node->left);
    if (node->left != NULL) printf(",");

    print_ast(node->right);

    if (node->left != NULL) printf(")");
}

char* variable_names[MAX_VARIABLES];
int variable_values[MAX_VARIABLES];
int variable_count = 0;

// Función para añadir una variable a la tabla de símbolos
void add_variable(char* name, int value) {
    // Comprobar si la variable ya existe
    for (int i = 0; i < variable_count; i++) {
        if (strcmp(variable_names[i], name) == 0) {
            printf("Error: variable %s ya declarada.\n", name);
            exit(1);
        }
    }
    // Si la variable no existe, añadirla
    variable_names[variable_count] = strdup(name);
    variable_values[variable_count] = value;
    variable_count++;
}

// Función para buscar una variable en la tabla de símbolos
int get_variable_value(char* name) {
    for (int i = 0; i < variable_count; i++) {
        if (strcmp(variable_names[i], name) == 0) {
            return variable_values[i];
        }
    }
    printf("Variable no encontrada: %s\n", name);
    exit(1);
}

// Función para evaluar el AST
int evaluate_ast(ASTNode* node) {
    if (node == NULL) return 0;

    switch (node->info->classType) {
        case CLASS_CONSTANT:
            return node->info->value;

        case CLASS_VAR:
            return get_variable_value(node->info->tag);

        case CLASS_OPERATION:
            if (node->info->tag[0] == '+') {
                return evaluate_ast(node->left) + evaluate_ast(node->right);
            } else if (node->info->tag[0] == '*') {
                return evaluate_ast(node->left) * evaluate_ast(node->right);
            }
            break;

        case CLASS_DECL:
            add_variable(node->left->info->tag, evaluate_ast(node->right));
            break;

        case CLASS_ASSIGN:
            // Suponiendo que el nodo izquierdo es un nodo de variable
            // y que ya hemos añadido esta variable antes en el caso de CLASS_DECL
            for (int i = 0; i < variable_count; i++) {
                if (strcmp(variable_names[i], node->left->info->tag) == 0) {
                    variable_values[i] = evaluate_ast(node->right);
                    return variable_values[i];
                }
            }
            printf("Variable no declarada: %s\n", node->left->info->tag);
            exit(1);
            break;

        case CLASS_RETURN:
            printf("Resultado: %d\n", evaluate_ast(node->left));
            break;

            // notar que si pongo algo abajo del return es inalcanzable

        case CLASS_PROGRAM:
            evaluate_ast(node->left);
            evaluate_ast(node->right);
            break;

        case CLASS_SENTENCE_LIST:
            evaluate_ast(node->left);
            evaluate_ast(node->right);
            break;
        case CLASS_DECL_LIST:
            evaluate_ast(node->left);
            evaluate_ast(node->right);
            break;

        // notar que si pongo algo abajo del return es inalcanzable
        default:
            printf("Nodo no soportado, Tipo: %d\n", node->info->classType);
            break;
    }

    return 0;
}

Attributes* check_types(ASTNode* node, SymbolTable* table) {
    Attributes* left = NULL;
    Attributes* right = NULL;

    if (node == NULL) return 0;

    switch (node->info->classType) {
        case CLASS_PROGRAM:
            check_types(node->left, table);
            check_types(node->right, table);
            return NULL;
            break;

        case CLASS_CONSTANT:
            return node->info;
            break;

        case CLASS_VAR:
            left = lookup_symbol(table, node->info->tag);
            if (left == NULL) {
                printf("Variable no declarada: %s\n", node->info->tag);
                exit(1);
            } else {
                printf("Variable encontrada: %s\n", node->info->tag);
                printf("valor : %d\n", left->value);
                node->info->valueType = left->valueType;
                return left;
            }
            break;

        case CLASS_DECL:
            left = lookup_symbol(table, node->left->info->tag);
            if (left != NULL) {
                printf("Variable ya declarada: %s\n", node->left->info->tag);
                exit(1);
            } else {
                insert_symbol(table, node->left->info);
                node->left->info->valueType = node->info->valueType;
                right = check_types(node->right, table);
                if (node->left->info->valueType != right->valueType) {
                    printf("Error de tipos en la declaración de la variable: %s\n", node->left->info->tag);
                    exit(1);
                }
                return NULL;
            }
            break;

        case CLASS_ASSIGN:
            left = lookup_symbol(table, node->left->info->tag);
            if (left == NULL) {
                printf("Variable no declarada: %s\n", node->left->info->tag);
                exit(1);
            } else {
                right = check_types(node->right, table);
                if (left->valueType != right->valueType) {
                    printf("Error de tipos en la asignación de la variable: %s\n", node->left->info->tag);
                    exit(1);
                }
                node->left->info->valueType = left->valueType;
                node->info->valueType = left->valueType;

                return NULL;
            }
            break;

        case CLASS_OPERATION:
            left = check_types(node->left, table);
            right = check_types(node->right, table);
            if (left->valueType != right->valueType) {
                printf("Error de tipos en la operación: %c\n", node->info->tag[0]);
                exit(1);
            }
            node->info->valueType = left->valueType;
            return node->info;
            break;

        case CLASS_RETURN:
            left = check_types(node->left, table);
            node->info->valueType = left->valueType;
            return left;
            break;

        case CLASS_DECL_LIST:
            check_types(node->left, table);
            check_types(node->right, table);
            break;

        case CLASS_SENTENCE_LIST:
            check_types(node->left, table);
            check_types(node->right, table);
            break;

        default:
            printf("Nodo no soportado, Tipo: %d\n", node->info->classType);
            break;
    }

    return 0;
}

// El nodo en este punto ya esta etiquetado y los programas terminan en return <expr entera>
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
