#include "semantic.h"

#include <stdio.h>
#include <stdlib.h>

#include "errors.h"

void check_binary_operation(ASTNode* node, SymbolTable* table, char* name) {
    if (node->left->info->valueType != node->right->info->valueType) {
        save_error(node->info->line, "%s: %s", name, node->info->tag);
    }
}

void check_types(ASTNode* node, SymbolTable* table) {
    if (node == NULL) return;

    switch (node->info->classType) {
        case CLASS_DECL:
            node->left->info->valueType = node->info->valueType;
            check_types(node->right, table);
            check_binary_operation(node, table, "declaration");
            break;

        case CLASS_ASSIGN:
            check_types(node->right, table);
            check_binary_operation(node, table, "assignment");
            node->info->valueType = node->left->info->valueType;
            break;

        case CLASS_ADD:
        case CLASS_MUL:
            check_types(node->left, table);
            check_types(node->right, table);
            check_binary_operation(node, table, "operation");
            node->info->valueType = node->left->info->valueType;
            break;

        case CLASS_RETURN:
            check_types(node->left, table);
            node->info->valueType = node->left->info->valueType;
            break;

        default:
            check_types(node->left, table);
            check_types(node->right, table);
            break;
    }
}
