#ifndef INSTRUCTION3DIR_H
#define INSTRUCTION3DIR_H
#include "stdlib.h"
#include "structures/ast.h"
#include "structures/attributes.h"

typedef enum {
    MOV_C,
    MOV_V,
    RETURN_A,
    ADD_B,
    ADD_I,
    MULT_B,
    MULT_I,
} CodOp;

typedef struct Instruction {
    CodOp opcode;
    Attributes* op1;
    Attributes* op2;
    Attributes* res;
    struct Instruction* next;
} Instruction;

typedef struct InstructionList {
    Instruction* head;
} InstructionList;

void print_instruction(Instruction* instruction);
void print_instruction_list(InstructionList* instructionList);
Instruction* create_instruction(CodOp opcode, Attributes* op1, Attributes* op2, Attributes* res);
void append_instruction(InstructionList* instructionList, Instruction* instruction);
InstructionList* gen_assembly(ASTNode* node);
#endif
