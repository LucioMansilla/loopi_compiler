#ifndef INSTRUCTION3DIR_H
#define INSTRUCTION3DIR_H
#include "stdlib.h"
#include "structures/attributes.h"

#define FOREACH_OPCOD(COD) \
    COD(MOV_C)             \
    COD(MOV_V)             \
    COD(RETURN_A)          \
    COD(RETURN_EXPR)       \
    COD(ADD)               \
    COD(MUL)               \
    COD(SUB)               \
    COD(DIV)               \
    COD(MOD)               \
    COD(NOT)               \
    COD(AND)               \
    COD(OR)                \
    COD(LESS)              \
    COD(GREATER)           \
    COD(EQUALS)            \
    COD(DECL_FUNC_INIT)    \
    COD(DECL_FUNC_END)     \
    COD(LABEL)             \
    COD(JMP_F)             \
    COD(JMP)               \
    COD(CALL)

#define GENERATE_ENUM(ENUM) ENUM,
#define GENERATE_STRING(STRING) #STRING,

typedef enum { FOREACH_OPCOD(GENERATE_ENUM) } CodOp;

static const char* COD_OP_STRING[] = {FOREACH_OPCOD(GENERATE_STRING)};

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
