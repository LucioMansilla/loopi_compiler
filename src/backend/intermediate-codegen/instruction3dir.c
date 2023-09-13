#include "instruction3dir.h"

#include <stdio.h>


Instruction* create_instruction(CodOp op_code, Attributes* dir1, Attributes* dir2, Attributes* res) {
    Instruction* instr = (Instruction*)malloc(sizeof(Instruction));
    instr->op_code = op_code;
    instr->dir1 = dir1;
    instr->dir2 = dir2;
    instr->res = res;
    return instr;
}

void print_instruction(Instruction* instruction) {
  
  printf("%s ", COD_OP_STRING[instruction->op_code]); 
  
  if (instruction->dir1 != NULL) {
    printf("%p ", instruction->dir1); 
  }
  if (instruction->dir2 != NULL) {
    printf("%p ", instruction->dir2);
  }
  if (instruction->res != NULL) {
    printf("%p ", instruction->res);
  }
  printf("\n");
}

void print_instruction_list(InstructionList* instruction_list) {
    Instruction* instruction = instruction_list->head;
    while (instruction != NULL) {
        print_instruction(instruction);
        instruction = instruction->next;
    }
}

void append_instruction(InstructionList* instruction_list, Instruction* instruction) {
    if (instruction_list->head == NULL) {
        instruction_list->head = instruction;
        return;
    }
    Instruction* last = instruction_list->head;
    while (last->next != NULL) {
        last = last->next;
    }
    last->next = instruction;
}
