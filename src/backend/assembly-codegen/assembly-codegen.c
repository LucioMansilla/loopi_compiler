#include "assembly-codegen.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ast.h"
typedef struct {
    void* memory_address;
    const char* assembly_register;
} SymbolTableEntry;

#define MAX_ENTRIES 7
SymbolTableEntry symbol_table[MAX_ENTRIES];
int symbol_table_count = 0;

const char* available_registers[] = {"%ebx", "%ecx", "%edx", "%esi", "%edi", "%r8d", "%r9d"};
int available_register_count = 7;

const char* get_or_add_symbol(void* memory_address) {
    for (int i = 0; i < symbol_table_count; ++i) {
        if (symbol_table[i].memory_address == memory_address) {
            return symbol_table[i].assembly_register;
        }
    }

    if (symbol_table_count >= MAX_ENTRIES) {
        exit(1);
    }

    const char* new_register = available_registers[symbol_table_count];
    symbol_table[symbol_table_count].memory_address = memory_address;
    symbol_table[symbol_table_count].assembly_register = new_register;
    symbol_table_count++;

    return new_register;
}

bool exists_in_symbol_table(void* memory_address) {
    for (int i = 0; i < symbol_table_count; ++i) {
        if (symbol_table[i].memory_address == memory_address) {
            return true;
        }
    }
    return false;
}

/* void prologue(int offset, FILE* fp) {
    fprintf(fp, "    .text\n");
    fprintf(fp, "    .globl main\n");
    fprintf(fp, "    .type main, @function\n");
    fprintf(fp, "main:\n");
    fprintf(fp, "    pushq %%rbp\n");
    fprintf(fp, "    movq %%rsp, %%rbp\n");
    fprintf(fp, "    subq $%d, %%rsp\n", offset * -1);
}

void epilogue(int offset, FILE* fp) {
    fprintf(fp, "    addq $%d, %%rsp\n", offset * -1);
    fprintf(fp, "    popq  %%rbp\n");
    fprintf(fp, "    ret\n");
    fprintf(fp, "    .section	.note.GNU-stack,\"\",@progbits\n");
} */

void prologue(const char* function_name, int offset, FILE* fp) {
    fprintf(fp, "    .text\n");
    fprintf(fp, "    .globl %s\n", function_name);
    fprintf(fp, "    .type %s, @function\n", function_name);
    fprintf(fp, "%s:\n", function_name);
    fprintf(fp, "    pushq %%rbp\n");
    fprintf(fp, "    movq %%rsp, %%rbp\n");
    fprintf(fp, "    subq $%d, %%rsp\n", -1 * offset);
}

void epilogue(FILE* fp) {
    fprintf(fp, "    leave\n");
    fprintf(fp, "    ret\n");
    fprintf(fp, "    .section .note.GNU-stack,\"\",@progbits\n");
}

void generate_gnu_assembly(InstructionList* list) {
    FILE* fp = fopen("output.s", "w");
    int max_offset = get_next_offset();

    //   prologue(max_offset, fp);

    Instruction* current = list->head;
    while (current != NULL) {
        switch (current->op_code) {
            case DECL_FUNC_INIT:
                // int offset = calculate_offset_for_function(current->res->tag);
                prologue(current->res->tag, max_offset, fp);
                break;

            case DECL_FUNC_END:
                break;

            case RETURN_EXPR:
                fprintf(fp, "    movq %d(%%rbp), %%rdi\n", current->res->offset);
                fprintf(fp, "    movq $%d, %%rsi\n", current->res->value_type);
                fprintf(fp, "    call print\n");
                epilogue(fp);
                break;

            case RETURN_A:
                epilogue(fp);
                break;

            case MOV_C:
                fprintf(fp, "    movq $%d, %d(%%rbp)\n", current->dir1->value, current->res->offset);
                break;

            case MOV_V:
                fprintf(fp, "    movq %d(%%rbp) , %%rax\n", current->dir1->offset);
                fprintf(fp, "    movq %%rax, %d(%%rbp)\n", current->res->offset);
                break;

            case ADD:

                if (current->dir1->class_type == CLASS_CONSTANT)
                    fprintf(fp, "    movq $%d, %%rax\n", current->dir1->value);
                else
                    fprintf(fp, "    movq %d(%%rbp), %%rax\n", current->dir1->offset);

                if (current->dir2->class_type == CLASS_CONSTANT)
                    fprintf(fp, "    addq $%d, %%rax\n", current->dir2->value);
                else
                    fprintf(fp, "    addq %d(%%rbp), %%rax\n", current->dir2->offset);

                fprintf(fp, "    movq %%rax, %d(%%rbp)\n", current->res->offset);
                break;

            case MUL:

                fprintf(fp, "    movq $0, %%rax\n");

                if (current->dir1->class_type == CLASS_CONSTANT)
                    fprintf(fp, "    movq $%d, %%rax\n", current->dir1->value);
                else
                    fprintf(fp, "    movq %d(%%rbp), %%rax\n", current->dir1->offset);

                if (current->dir2->class_type == CLASS_CONSTANT)
                    fprintf(fp, "    imul $%d, %%rax\n", current->dir2->value);
                else
                    fprintf(fp, "    imul %d(%%rbp), %%rax\n", current->dir2->offset);

                fprintf(fp, "    movq %%rax, %d(%%rbp)\n", current->res->offset);
                break;

                // case GREATER:
                // case EQUALS:

            case LESS:

                if (current->dir1->class_type == CLASS_CONSTANT)
                    fprintf(fp, "    movq $%d, %%rax\n", current->dir1->value);
                else
                    fprintf(fp, "    movq %d(%%rbp), %%rax\n", current->dir1->offset);

                if (current->dir2->class_type == CLASS_CONSTANT)
                    fprintf(fp, "    cmpq $%d, %%rax\n", current->dir2->value);
                else
                    fprintf(fp, "    cmpq %d(%%rbp), %%rax\n", current->dir2->offset);

                fprintf(fp, "    setl %%al\n");
                fprintf(fp, "    movzbq %%al, %%rax\n");
                fprintf(fp, "    movq %%rax, %d(%%rbp)\n", current->res->offset);
                break;

            case JMP_F:
                fprintf(fp, "    testq %%rax, %%rax\n");
                fprintf(fp, "    jz LABEL_%d\n", current->res->value);
                break;

            case JMP:
                fprintf(fp, "    jmp LABEL_%d\n", current->res->value);
                break;
            case LABEL:
                fprintf(fp, "LABEL_%d:\n", current->res->value);
                break;

            case CALL:
                fprintf(fp, "    call %s\n", current->res->tag);
                break;
            default:
                break;
        }
        current = current->next;
    }
    fclose(fp);
}
