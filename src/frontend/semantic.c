#include "semantic.h"

#include <stdio.h>
#include <stdlib.h>

void check_binary_operation(ASTNode* node, char* name) {
    if (node->left->info->valueType != node->right->info->valueType) {
        save_error(node->info->line, "%s: %s", name, node->info->tag);
    }
}

void check_types(ASTNode* node) {
    if (node == NULL) return;

    switch (node->info->classType) {
        case CLASS_DECL:
            node->left->info->valueType = node->info->valueType;
            check_types(node->right);
            check_binary_operation(node, "declaration");
            break;

        case CLASS_ASSIGN:
            check_types(node->right);
            check_binary_operation(node, "assignment");
            node->info->valueType = node->left->info->valueType;
            break;

        case CLASS_ADD:
        case CLASS_MUL:
            check_types(node->left);
            check_types(node->right);
            check_binary_operation(node, "operation");
            node->info->valueType = node->left->info->valueType;
            break;

        case CLASS_RETURN:
            check_types(node->left);
            node->info->valueType = node->left->info->valueType;
            break;

        case CLASS_IF:
            check_types(node->left);   // Check the condition
            check_types(node->right);  // Check the body
            // If there are specific semantic checks for if statements, add them here
            break;
        default:
            check_types(node->left);
            check_types(node->right);
            break;
    }
}