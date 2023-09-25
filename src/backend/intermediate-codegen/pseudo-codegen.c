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
            generate_pseudo_assembly(node->left, list);
            generate_pseudo_assembly(node->right, list);
            Instruction* addInstr = create_instruction(ADD, node->left->info, node->right->info, node->info);
            append_instruction(list, addInstr);
            break;

        case CLASS_MUL:
            generate_pseudo_assembly(node->left, list);
            generate_pseudo_assembly(node->right, list);
            Instruction* mulInstr = create_instruction(MUL, node->left->info, node->right->info, node->info);
            append_instruction(list, mulInstr);
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
