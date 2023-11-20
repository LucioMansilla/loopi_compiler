#include "semantic.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "errors.h"
#include "stack.h"
#include "symbol_table.h"

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

bool check_param_types(ASTNode* current_actual_node, Symbol* current_formal_param) {
    check_types(current_actual_node);
    return current_actual_node->info->value_type == current_formal_param->info->value_type;
}

bool check_param_actuals(ASTNode* node_list_param_actual, Symbol* list_param_formal) {
    ASTNode* current_actual_node = node_list_param_actual;
    Symbol* current_formal_param = list_param_formal;

    while (current_actual_node != NULL) {
        if (!check_param_types(current_actual_node->left, current_formal_param)) return false;
        current_formal_param = current_formal_param->next;
        current_actual_node = current_actual_node->right;
    }

    return true;
}

ValueType method_type = TYPE_VOID;
bool has_main(ASTNode* node) {
    return lookup_in_global_level("main") != NULL;
}

void check_value_type(ValueType left, ValueType right, ASTNode* node) {
    if (left != right) {
        char* left_type = get_type_str(left);
        char* right_type = get_type_str(right);

        switch (node->info->class_type) {
            case CLASS_ASSIGN:
                save_error(node->info->line, TYPE_ERROR_ASSIGNMENT, left_type, right_type);
                break;

            case CLASS_DECL:
                save_error(node->info->line, TYPE_ERROR_DECLARATION, left_type, right_type);
                break;

            case CLASS_MINUS:
            case CLASS_NOT:
                save_error(node->info->line, TYPE_ERROR_UNARY, node->info->tag, left_type);
                break;

            case CLASS_RETURN:
            case CLASS_RETURN_EXPR:
                save_error(node->info->line, TYPE_ERROR_RETURN, left_type, right_type);
                break;

            default:
                save_error(node->info->line, TYPE_ERROR_OPERATION, node->info->tag, left_type, right_type);
                break;
        }
    }
}

void check_types(ASTNode* node) {
    if (node == NULL) return;

    switch (node->info->class_type) {
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

        case CLASS_CALL_FUNCTION:
            if (!check_param_actuals(node->left, node->info->parameter_list->head)) {
                printf("Error de tipo en la linea %d: Los parametros no coinciden con los formales.\n", node->info->line);
                exit(1);
            }
            break;

        case CLASS_DECL:
            node->left->info->value_type = node->info->value_type;
            if (node->left->info->class_type == CLASS_GLOBAL && node->right->info->class_type != CLASS_CONSTANT) {
                save_error(node->info->line, GLOBL_ERROR_DECLARATION, node->left->info->tag);
            }
         
            check_types(node->right);
            check_value_type(node->left->info->value_type, node->right->info->value_type, node);
            break;

        case CLASS_ASSIGN:
            check_types(node->right);
            check_value_type(node->left->info->value_type, node->right->info->value_type, node);
            node->info->value_type = node->left->info->value_type;
            break;

        case CLASS_NOT:
            check_types(node->left);
            check_value_type(node->left->info->value_type, TYPE_BOOL, node);
            break;

        case CLASS_MINUS:
            check_types(node->left);
            check_value_type(node->left->info->value_type, TYPE_INT, node);
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
            check_value_type(node->left->info->value_type, node->right->info->value_type, node);
            break;

        case CLASS_RETURN:
            check_value_type(method_type, TYPE_VOID, node);
            break;

        case CLASS_RETURN_EXPR:
            check_types(node->left);
            node->info->value_type = node->left->info->value_type;
            check_value_type(method_type, node->info->value_type, node);
            break;

        case CLASS_IF:
            check_types(node->left);
            check_value_type(node->left->info->value_type, TYPE_BOOL, node);
            check_types(node->middle);
            break;

        case CLASS_IF_THEN_ELSE:
            check_types(node->left);
            check_value_type(node->left->info->value_type, TYPE_BOOL, node);
            check_types(node->middle);
            check_types(node->right);
            break;

        case CLASS_WHILE:
            check_types(node->left);
            check_value_type(node->left->info->value_type, TYPE_BOOL, node);
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
