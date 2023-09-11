#include "semantic.h"

#include <stdio.h>
#include <stdlib.h>

void check_binary_operation(ASTNode* node) {

    if (node->left->info->value_type != node->right->info->value_type) {

        char* left_type = get_type_str(node->left->info->value_type);
        char* right_type = get_type_str(node->right->info->value_type);
    
        switch (node->info->class_type)
        {
        case CLASS_ADD:
        case CLASS_MUL:
            save_error(node->info->line, "Type Error in operation %s : left-hand side has type %s but right-hand side has type %s", node->info->tag, left_type, right_type);
            break;
        
        case CLASS_ASSIGN:
            save_error(node->info->line, "Type Error in assignment: variable of type %s cannot be assigned a value of type %s", left_type, right_type);
            break;

        case CLASS_DECL:      
            save_error(node->info->line, "Type Error in declaration: variable declared as %s but initialized with a value of type %s", left_type, right_type);
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
