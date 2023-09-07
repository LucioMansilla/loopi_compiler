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

void eval(ASTNode* node) {
    Attributes* left = NULL;
    if (node == NULL) return;

    switch (node->info->classType) {

        case CLASS_PROGRAM:
        case CLASS_DECL_LIST:
        case CLASS_SENTENCE_LIST:
            eval(node->left);
            eval(node->right);
            break;

        case CLASS_VAR:
        case CLASS_CONSTANT:
            break;

        case CLASS_DECL:
            eval(node->right);
            node->left->info->value = node->right->info->value;
            break;

        case CLASS_ASSIGN:
            eval(node->right);
            node->left->info->value = node->right->info->value;
            break;
        case CLASS_RETURN:
            eval(node->left);
            print_result(node->left->info);
            break;

        case CLASS_ADD:
            eval(node->left);
            eval(node->right);
            node->info->value = node->left->info->value + node->right->info->value;   
            break;

        case CLASS_MUL:
            eval(node->left);
            eval(node->right);
            node->info->value = node->left->info->value * node->right->info->value;
            break;

        default :
            break;

    }
}