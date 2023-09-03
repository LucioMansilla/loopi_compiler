#include "semantic.h"

#include <stdio.h>
#include <stdlib.h>

// Función auxiliar para manejar operaciones binarias y asignaciones
void check_binary_operation(ASTNode* node, SymbolTable* table) {
    check_types(node->right, table);

    if (node->left->info->valueType != node->right->info->valueType) {
        printf("Error de tipos en la operación: %s\n", node->left->info->tag);
        exit(1);
    }

    node->info->valueType = node->left->info->valueType;
}

// Función principal para el chequeo semántico
void check_types(ASTNode* node, SymbolTable* table) {
    if (node == NULL) return;

    switch (node->info->classType) {
        case CLASS_DECL:
            node->left->info->valueType = node->info->valueType;
            check_types(node->right, table);

            if (node->left->info->valueType != node->right->info->valueType) {
                printf("Error de tipos en la declaración de la variable: %s\n", node->left->info->tag);
                exit(1);
            }
            break;

        case CLASS_ASSIGN:
            check_binary_operation(node, table);
            break;

        case CLASS_OPERATION:
            check_types(node->left, table);
            check_types(node->right, table);

            if (node->left->info->valueType != node->right->info->valueType) {
                printf("Error de tipos en la operación: %c\n", node->info->tag[0]);
                exit(1);
            }

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
