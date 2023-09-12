#include "semantic.h"

#include <stdio.h>
#include <stdlib.h>

#include "errors.h"  // Asegúrate de incluir este archivo
#include "semantic.h"

void check_binary_operation(ASTNode* node) {
    if (node->left->info->value_type != node->right->info->value_type) {
        char* left_type = get_type_str(node->left->info->value_type);
        char* right_type = get_type_str(node->right->info->value_type);

        switch (node->info->class_type) {
            case CLASS_ADD:
            case CLASS_MUL:
                save_error(node->info->line, TYPE_ERROR_OPERATION, node->info->tag, left_type, right_type);
                break;

            case CLASS_ASSIGN:
                save_error(node->info->line, TYPE_ERROR_ASSIGNMENT, left_type, right_type);
                break;

            case CLASS_DECL:
                save_error(node->info->line, TYPE_ERROR_DECLARATION, left_type, right_type);
                break;

            default:
                break;
        }
    }
}

void check_types(ASTNode* node) {
    if (node == NULL) return;

    switch (node->info->class_type) {
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

        case CLASS_ADD:
        case CLASS_MUL:
            check_types(node->left);
            check_types(node->right);
            check_binary_operation(node);
            node->info->value_type = node->left->info->value_type;
            break;

        case CLASS_RETURN:
            check_types(node->left);
            node->info->value_type = node->left->info->value_type;
            break;

        case CLASS_IF:
            check_types(node->left);
            check_types(node->right);
            break;

        default:
            check_types(node->left);
            check_types(node->right);
            break;
    }
}
