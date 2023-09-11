#include "semantic.h"

#include <stdio.h>
#include <stdlib.h>

void check_binary_operation(ASTNode* node, char* name) {
    if (node->left->info->value_type != node->right->info->value_type) {
        save_error(node->info->line, "%s: %s", name, node->info->tag);
    }
}

void check_types(ASTNode* node) {
    if (node == NULL) return;

    switch (node->info->class_type) {
        case CLASS_DECL:
            node->left->info->value_type = node->info->value_type;
            check_types(node->right);
            check_binary_operation(node, "declaration");
            break;

        case CLASS_ASSIGN:
            check_types(node->right);
            check_binary_operation(node, "assignment");
            node->info->value_type = node->left->info->value_type;
            break;

        case CLASS_ADD:
        case CLASS_MUL:
            check_types(node->left);
            check_types(node->right);
            check_binary_operation(node, "operation");
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
