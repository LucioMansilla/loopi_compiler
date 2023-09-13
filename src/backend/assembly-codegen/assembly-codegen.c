#include "assembly-codegen.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
        fprintf(stderr, "Out of registers, need to spill to memory (not implemented).\n");
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

void generate_gnu_assembly(InstructionList* list) {
    FILE* fp = fopen("output.s", "w");

    fprintf(fp, ".section .text\n");
    fprintf(fp, ".globl _start\n");
    fprintf(fp, "_start:\n");
    const char* res_reg;
    const char* dir1_reg;
    const char* dir2_reg;

    Instruction* current = list->head;
    while (current != NULL) {
        res_reg = NULL;
        dir1_reg = NULL;
        dir2_reg = NULL;

        switch (current->op_code) {
            case MOV_C:
                res_reg = get_or_add_symbol(current->res);
                fprintf(fp, "    mov $%d, %s\n", current->dir1->value, res_reg);
                break;
            case MOV_V:
                dir1_reg = get_or_add_symbol(current->dir1);
                res_reg = get_or_add_symbol(current->res);
                fprintf(fp, "    mov %s, %s\n", dir1_reg, res_reg);

                break;

            case RETURN_A:

                if (exists_in_symbol_table(current->res)) {
                    res_reg = get_or_add_symbol(current->res);
                    fprintf(fp, "    mov %s, %%ebx\n", res_reg);
                } else
                    fprintf(fp, "    mov $%d, %%ebx\n", current->res->value);

                fprintf(fp, "    mov $1, %%eax\n");
                fprintf(fp, "    int $0x80\n");

                break;
            case ADD_I:
                res_reg = get_or_add_symbol(current->res);
                if (exists_in_symbol_table(current->dir1)) {
                    dir1_reg = get_or_add_symbol(current->dir1);
                    fprintf(fp, "    mov %s, %s\n", dir1_reg, res_reg);
                } else {
                    fprintf(fp, "    mov $%d, %s\n", current->dir1->value, res_reg);
                }
                if (exists_in_symbol_table(current->dir2)) {
                    dir2_reg = get_or_add_symbol(current->dir2);
                    fprintf(fp, "    add %s, %s\n", dir2_reg, res_reg);
                } else {
                    fprintf(fp, "    add $%d, %s\n", current->dir2->value, res_reg);
                }
                break;

            case MULT_I: //mul enteros
                res_reg = get_or_add_symbol(current->res);
                if (exists_in_symbol_table(current->dir1)) {
                    dir1_reg = get_or_add_symbol(current->dir1);
                    fprintf(fp, "    mov %s, %s\n", dir1_reg, res_reg);
                } else {
                    fprintf(fp, "    mov $%d, %s\n", current->dir1->value, res_reg);
                }
                if (exists_in_symbol_table(current->dir2)) {
                    dir2_reg = get_or_add_symbol(current->dir2);
                    fprintf(fp, "    imul %s, %s\n", dir2_reg, res_reg);
                } else {
                    fprintf(fp, "    imul $%d, %s\n", current->dir2->value, res_reg);
                }

                

                break;
            default:
                break;
        }
        current = current->next;
    }

    fclose(fp);
}
