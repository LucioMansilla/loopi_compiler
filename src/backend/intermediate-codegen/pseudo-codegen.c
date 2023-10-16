#include "pseudo-codegen.h"

void generate_pseudo_assembly(ASTNode* node, InstructionList* list) {
    if (node == NULL) return;

    switch (node->info->class_type) {
        case CLASS_PROGRAM:
        case CLASS_DECL_LIST:
        case CLASS_SENTENCE_LIST:
            generate_pseudo_assembly(node->left, list);
            generate_pseudo_assembly(node->right, list);
            break;

        case CLASS_DECL:
        case CLASS_ASSIGN:
            generate_pseudo_assembly(node->right, list);
            CodOp op_code = node->right->info->class_type == CLASS_CONSTANT ? MOV_C : MOV_V;
            Instruction* movInstr = create_instruction(op_code, node->right->info, NULL, node->left->info);
            append_instruction(list, movInstr);
            break;

        case CLASS_ADD:
            generate_binary_operator(node, ADD, list);
            break;

        case CLASS_SUB:
            generate_binary_operator(node, SUB, list);
            break;

        case CLASS_DIV:
            generate_binary_operator(node, DIV, list);
            break;

        case CLASS_MOD:
            generate_binary_operator(node, MOD, list);
            break;

        case CLASS_GREATER:
            generate_binary_operator(node, GREATER, list);
            break;

        case CLASS_LESS:
            generate_binary_operator(node, LESS, list);
            break;

        case CLASS_EQUALS:
            generate_binary_operator(node, EQUALS, list);
            break;

        case CLASS_AND:
            generate_binary_operator(node, AND, list);
            break;

        case CLASS_OR:
            generate_binary_operator(node, OR, list);
            break;

        case CLASS_MUL:
            generate_binary_operator(node, MUL, list);
            break;

        case CLASS_RETURN:
            generate_pseudo_assembly(node->left, list);
            Instruction* retInstr = create_instruction(RETURN_A, NULL, NULL, node->left->info);
            append_instruction(list, retInstr);
            break;

        case CLASS_VAR:
        case CLASS_CONSTANT:
            break;
    }
}

InstructionList* generate_tac(ASTNode* node) {
    InstructionList* list = (InstructionList*)malloc(sizeof(InstructionList));
    list->head = NULL;
    generate_pseudo_assembly(node, list);
    return list;
}

void generate_binary_operator(ASTNode* node, CodOp op, InstructionList* list) {
    generate_pseudo_assembly(node->left, list);
    generate_pseudo_assembly(node->right, list);
    Instruction* instr = create_instruction(op, node->left->info, node->right->info, node->info);
    append_instruction(list, instr);
}
