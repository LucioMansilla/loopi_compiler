#include "eval.h"
#include <stdio.h>

void print_result(Attributes* info) {
    if (info->valueType == TYPE_INT)
        printf("%d\n", info->value);
    else if (info->value) {
        printf("true\n");
    } else
        printf("false\n");
}

void eval(ASTNode* node, SymbolTable* table) {
    Attributes* left = NULL;
    if (node == NULL) return;

    switch (node->info->classType) {
        case CLASS_PROGRAM:
            eval(node->left, table);
            eval(node->right, table);
            break;

        case CLASS_VAR:
        case CLASS_CONSTANT:
            break;

        case CLASS_DECL:
            left = lookup_symbol(table, node->left->info->tag);
            eval(node->right, table);
            left->value = node->right->info->value;
            break;

        case CLASS_ASSIGN:
            left = lookup_symbol(table, node->left->info->tag);
            eval(node->right, table);
            left->value = node->right->info->value;
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
            print_result(node->left->info);
            break;

        case CLASS_ADD:
            eval(node->left, table);
            eval(node->right, table);
            if (node->info->valueType == TYPE_INT) {
                node->info->value = node->left->info->value + node->right->info->value;
            } else {
                node->info->value = node->left->info->value || node->right->info->value;
            }
            break;

        case CLASS_MUL:
            eval(node->left, table);
            eval(node->right, table);
            if (node->info->valueType == TYPE_INT) {
                node->info->value = node->left->info->value * node->right->info->value;
            } else {
                node->info->value = node->left->info->value && node->right->info->value;
            }
            break;
        default :
            break;

    }
}