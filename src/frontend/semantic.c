#include "semantic.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "errors.h"

void check_binary_operation(ASTNode* node) {
    if (node->left->info->value_type != node->right->info->value_type) {
        char* left_type = get_type_str(node->left->info->value_type);
        char* right_type = get_type_str(node->right->info->value_type);

        switch (node->info->class_type) {
            case CLASS_ASSIGN:
                save_error(node->info->line, TYPE_ERROR_ASSIGNMENT, left_type, right_type);
                break;

            case CLASS_DECL:
                save_error(node->info->line, TYPE_ERROR_DECLARATION, left_type, right_type);
                break;

            default:
                save_error(node->info->line, TYPE_ERROR_OPERATION, node->info->tag, left_type, right_type);
                break;
        }
    }
}

bool check_return_existence(ASTNode* node) {
    // Esta funcion chequea si existe un return en el arbol.--
    if (node == NULL) return false;

    switch (node->info->class_type) {
        case CLASS_RETURN_EXPR:
        case CLASS_RETURN:
            return true;
            break;

        default:
            // Chequea en el nodo izquierdo
            if (node->left != NULL && check_return_existence(node->left)) {
                return true;
            }
            
            // Chequea en el nodo del medio
            if (node->middle != NULL && check_return_existence(node->middle)) {
                return true;
            }
            
            // Chequea en el nodo derecho
            if (node->right != NULL && check_return_existence(node->right)) {
                return true;
            }
            break;
    }
    return false;
}

ValueType method_type = TYPE_VOID;

void check_types(ASTNode* node) {
    if (node == NULL) return;

    switch (node->info->class_type) {
        case CLASS_METHODS_DECL_LIST:
        case CLASS_PROGRAM:
            check_types(node->left);
            check_types(node->right);
            break;

        case CLASS_DECL_FUNCTION:
            if (node->left != NULL) {  // Un caso donde no es extern.
                method_type = node->info->value_type;
                if (!check_return_existence(node->left)) {
                    printf("Error de tipo en la linea %d: La funcion no tiene un return.\n", node->info->line);
                    exit(1);
                }
                check_types(node->left);
            }

            break;

        case CLASS_BLOCK:
            check_types(node->left);
            check_types(node->right);
            break;

        case CLASS_DECL:
            node->left->info->value_type = node->info->value_type;
            check_types(node->right);
            check_binary_operation(node);
            break;

        case CLASS_ASSIGN:
            check_types(node->right);
            check_binary_operation(node);
            node->info->value_type = node->left->info->value_type;
            break;

        case CLASS_OR:
        case CLASS_AND:
        case CLASS_LESS:
        case CLASS_GREATER:
        case CLASS_EQUALS:
        case CLASS_ADD:
        case CLASS_SUB:
        case CLASS_DIV:
        case CLASS_MOD:
        case CLASS_MUL:
            check_types(node->left);
            check_types(node->right);
            check_binary_operation(node);
            break;

        case CLASS_RETURN:
            if (method_type != node->info->value_type) {
                printf("Error de tipo en la linea %d: El tipo de retorno no coincide con el tipo de la funcion.\n",
                       node->info->line);
                exit(1);
            }
            break;

        case CLASS_RETURN_EXPR:
            check_types(node->left);
            node->info->value_type = node->left->info->value_type;
            if (method_type != node->info->value_type) {
                printf("Error de tipo con el return en la linea %d: El tipo de retorno no coincide con el tipo de la funcion.\n",
                       node->info->line);
                exit(1);
            }
            break;

        case CLASS_IF:
            if (node->left->info->value_type != TYPE_BOOL) {
                printf("Error de tipo en la linea %d: La condicion del if no es booleana.\n", node->info->line);
                exit(1);
            }
            check_types(node->middle);
            break;

        case CLASS_IF_THEN_ELSE:
            if (node->left->info->value_type != TYPE_BOOL) {
                printf("Error de tipo en la linea %d: La condicion del if no es booleana.\n", node->info->line);
                exit(1);
            }

            check_types(node->middle);
            check_types(node->right);
            break;

        case CLASS_WHILE:
            if (node->left->info->value_type != TYPE_BOOL) {
                printf("Error de tipo en la linea %d: La condicion del while no es booleana.\n", node->info->line);
                exit(1);
            }
            check_types(node->right);
            break;

        case CLASS_EMPTY:
            break;

        default:
            check_types(node->left);
            check_types(node->right);
            break;
    }
}
