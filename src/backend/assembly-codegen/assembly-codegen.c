#include "assembly-codegen.h"

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

void generate_gnu_assembly(InstructionList* list) {
    FILE* fp = fopen("output.s", "w");

    fprintf(fp, ".section .text\n");
    fprintf(fp, ".globl _start\n");
    fprintf(fp, "_start:\n");

    Instruction* current = list->head;
    while (current != NULL) {
        const char* dest_reg = current->res ? get_or_add_symbol(current->res) : NULL;
        const char* dir1_reg = current->dir1 ? get_or_add_symbol(current->dir1) : NULL;
        const char* dir2_reg = current->dir2 ? get_or_add_symbol(current->dir2) : NULL;

        switch (current->op_code) {
            case MOV_C:
                if (dir1_reg && dest_reg) {
                    fprintf(fp, "    mov $%d, %s\n", current->dir1->value, dest_reg);
                }
                break;

            case RETURN_A:
                if (dest_reg) {
                    fprintf(fp, "    mov %s, %%ebx\n", dest_reg);
                    fprintf(fp, "    mov $1, %%eax\n");
                    fprintf(fp, "    int $0x80\n");
                }
                break;

            case ADD_I:
                if (current->dir1->class_type == CLASS_CONSTANT) {
                    fprintf(fp, "    add $%d, %s\n", current->dir1->value, dir2_reg);
                } else if (current->dir2->class_type == CLASS_CONSTANT) {
                    fprintf(fp, "    add $%d, %s\n", current->dir2->value, dir2_reg);
                } else {
                    fprintf(fp, "    add %s, %s\n", dir1_reg, dir2_reg);
                }
                fprintf(fp, "    mov %s, %s\n", dir2_reg, dest_reg);
                break;
            case MULT_I:
                fprintf(fp, "    imul %s, %s\n", dir1_reg, dir2_reg);
                fprintf(fp, "    mov %s, %s\n", dir2_reg, dest_reg);
                break;
            case ADD_B:  // boolean or
                fprintf(fp, "    or %s, %s\n", dir1_reg, dir2_reg);
                fprintf(fp, "    mov %s, %s\n", dir2_reg, dest_reg);
                break;
            case MULT_B:  // boolean and
                fprintf(fp, "    and %s, %s\n", dir1_reg, dir2_reg);
                fprintf(fp, "    mov %s, %s\n", dir2_reg, dest_reg);
                break;
            case MOV_V:  // mov variable
                fprintf(fp, "    mov %s, %s\n", dir1_reg, dest_reg);
                break;
            default:
                break;
        }
        current = current->next;
    }

    fclose(fp);
}
