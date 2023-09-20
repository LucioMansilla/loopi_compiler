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

/*
        .file	"main.c"
        .text
        .globl	main
        .type	main, @function
main:
        pushq	%rbp
        movq	%rsp, %rbp
        subq    $24, %rsp
*/
void prologue(int offset, FILE* fp) {
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
}
void generate_gnu_assembly(InstructionList* list) {
    FILE* fp = fopen("output.s", "w");
    int max_offset = get_next_offset() + 8;

    prologue(max_offset, fp);

    Instruction* current = list->head;
    while (current != NULL) {
        switch (current->op_code) {
            case MOV_C:
                fprintf(fp, "    movq $%d, %d(%%rbp)\n", current->dir1->value, current->res->offset);
                break;
            case MOV_V:
                fprintf(fp, "    movq %d(%rbp) , %%rax\n", current->dir1->offset);
                fprintf(fp, "    movq %%eax, %d(%%rbp)\n", current->res->offset);
                break;
            case RETURN_A:
                if (current->res->class_type == CLASS_CONSTANT)
                    fprintf(fp, "    movq $%d, %%rax\n", current->res->value);
                else
                    fprintf(fp, "    movq %d(%%rbp), %%rax\n", current->res->offset);
                
                fprintf(fp, "    movq %%rax, %%rdi\n");
                fprintf(fp, "    movq $%d, %%rsi\n", current->res->value_type); 
                fprintf(fp, "    call print\n");

                epilogue(max_offset, fp);
                break;

            case ADD_I:
            case ADD_B:
                fprintf(fp, "    movq %d(%%rbp), %%rax\n", current->dir1->offset);
                fprintf(fp, "    addq %d(%%rbp), %%rax\n", current->dir2->offset);
                fprintf(fp, "    movq %%rax, %d(%%rbp)\n", current->res->offset);
            break;
            
            default:
                break;
        }
        current = current->next;
    }
    fclose(fp);
}
