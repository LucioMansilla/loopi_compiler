#ifndef INSTRUCTION3DIR_H
#define INSTRUCTION3DIR_H
#include "stdlib.h"
#include "structures/ast.h"
#include "structures/attributes.h"

#define FOREACH_OPCOD(COD)  \
    COD(MOV_C)              \
    COD(MOV_V)              \
    COD(RETURN_A)           \
    COD(ADD_B)              \
    COD(ADD_I)              \
    COD(MULT_B)             \
    COD(MULT_I)             \
  

#define GENERATE_ENUM(ENUM) ENUM,
#define GENERATE_STRING(STRING) #STRING,

typedef enum {
    FOREACH_OPCOD(GENERATE_ENUM)
} CodOp;

static const char *COD_OP_STRING[] = {
    FOREACH_OPCOD(GENERATE_STRING)
};

typedef struct Instruction {
    CodOp op_code;
    Attributes* dir1;
    Attributes* dir2;
    Attributes* res;
    struct Instruction* next;
} Instruction;

typedef struct InstructionList {
    Instruction* head;
} InstructionList;

void print_instruction_list(InstructionList* instruction_list);
Instruction* create_instruction(CodOp op_code, Attributes* dir1, Attributes* dir2, Attributes* res);
void append_instruction(InstructionList* instruction_list, Instruction* instruction);

#endif
