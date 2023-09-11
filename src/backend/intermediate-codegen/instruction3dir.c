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
