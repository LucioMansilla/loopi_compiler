#include "instruction3dir.h"

#include <stdio.h>

Instruction* create_instruction(CodOp opcode, Attributes* op1, Attributes* op2, Attributes* res) {
    Instruction* instr = (Instruction*)malloc(sizeof(Instruction));
    instr->opcode = opcode;
    instr->op1 = op1;
    instr->op2 = op2;
    instr->res = res;
    return instr;
}

void generate_assembly(ASTNode* node, InstructionList* list) {
    if (node == NULL) return;

    switch (node->info->class_type) {
        case CLASS_PROGRAM:
        case CLASS_DECL_LIST:
        case CLASS_SENTENCE_LIST:
            generate_assembly(node->left, list);
            generate_assembly(node->right, list);
            break;

        case CLASS_DECL:
        case CLASS_ASSIGN:
            generate_assembly(node->right, list);
            CodOp opcode = node->right->info->class_type == CLASS_CONSTANT ? MOV_C : MOV_V;
            Instruction* movInstr = create_instruction(opcode, node->right->info, NULL, node->left->info);
            append_instruction(list, movInstr);
            break;

        case CLASS_ADD:
            generate_assembly(node->left, list);
            generate_assembly(node->right, list);
            CodOp addOp = node->left->info->value_type == TYPE_INT ? ADD_I : ADD_B;
            Instruction* addInstr = create_instruction(addOp, node->left->info, node->right->info, node->info);
            append_instruction(list, addInstr);
            break;

        case CLASS_MUL:
            generate_assembly(node->left, list);
            generate_assembly(node->right, list);
            CodOp mulOp = node->left->info->value_type == TYPE_INT ? MULT_I : MULT_B;
            Instruction* mulInstr = create_instruction(mulOp, node->left->info, node->right->info, node->info);
            append_instruction(list, mulInstr);
            break;

        case CLASS_RETURN:
            generate_assembly(node->left, list);
            Instruction* retInstr = create_instruction(RETURN_A, NULL, NULL, node->left->info);
            append_instruction(list, retInstr);
            break;

        case CLASS_VAR:
        case CLASS_CONSTANT:
            break;
    }
}

void print_instruction(Instruction* instruction) {
    switch (instruction->opcode) {
        case MOV_C:
            printf("mov_c ");
            break;
        case MOV_V:
            printf("mov_v ");
            break;
        case ADD_I:
            printf("add_i ");
            break;
        case ADD_B:
            printf("add_b ");
            break;
        case MULT_I:
            printf("mult_i ");
            break;
        case MULT_B:
            printf("mult_b ");
            break;
        case RETURN_A:
            printf("ret ");
            break;
        default:
            break;
    }

    if (instruction->op1 != NULL) {
        printf("%p ", instruction->op1);
    }
    if (instruction->op2 != NULL) {
        printf("%p ", instruction->op2);
    }
    if (instruction->res != NULL) {
        printf("%p ", instruction->res);
    }
    printf("\n");
}

void print_instruction_list(InstructionList* instructionList) {
    Instruction* instruction = instructionList->head;
    while (instruction != NULL) {
        print_instruction(instruction);
        instruction = instruction->next;
    }
}

InstructionList* gen_assembly(ASTNode* node) {
    InstructionList* list = (InstructionList*)malloc(sizeof(InstructionList));
    list->head = NULL;
    generate_assembly(node, list);
    print_instruction_list(list);
    return list;
}

void append_instruction(InstructionList* instructionList, Instruction* instruction) {
    if (instructionList->head == NULL) {
        instructionList->head = instruction;
        return;
    }
    Instruction* last = instructionList->head;
    while (last->next != NULL) {
        last = last->next;
    }
    last->next = instruction;
}
