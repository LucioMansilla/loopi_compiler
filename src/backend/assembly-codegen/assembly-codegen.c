#include "assembly-codegen.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ast.h"
#include "symbol_table.h"

char* name_func = NULL;

typedef struct {
    void* memory_address;
    const char* assembly_register;
} SymbolTableEntry;

#define MAX_ENTRIES 7
SymbolTableEntry symbol_table[MAX_ENTRIES];
int symbol_table_count = 0;

const char* available_registers[] = {"%ebx", "%ecx", "%edx", "%esi", "%edi", "%r8d", "%r9d"};

const char* registers_param[] = {"%rdi", "%rsi", "%rdx", "%rcx", "%r8", "%r9"};

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
}

void generate_div(Instruction* current, FILE* fp) {
    if (current->dir1->class_type == CLASS_CONSTANT)
        fprintf(fp, "    movq $%d, %%rax\n", current->dir1->value);
    else
        fprintf(fp, "    movq %d(%%rbp), %%rax\n", current->dir1->offset);

    fprintf(fp, "    cqto\n");

    if (current->dir2->class_type == CLASS_CONSTANT) {
        fprintf(fp, "    movq $%d, %%rcx\n", current->dir2->value);
        fprintf(fp, "    idivq %%rcx\n");
    } else
        fprintf(fp, "    idivq %d(%%rbp)\n", current->dir2->offset);
}

void generate_rel_operator(Attributes* operator_1, Attributes* operator_2, Attributes* result, FILE* fp, CodOp op_code) {
    if (operator_1->class_type == CLASS_CONSTANT)
        fprintf(fp, "    movq $%d, %%rax\n", operator_1->value);
    else
        fprintf(fp, "    movq %d(%%rbp), %%rax\n", operator_1->offset);

    if (operator_2->class_type == CLASS_CONSTANT)
        fprintf(fp, "    cmpq $%d, %%rax\n", operator_2->value);
    else
        fprintf(fp, "    cmpq %d(%%rbp), %%rax\n", operator_2->offset);

    if (op_code == EQUALS)
        fprintf(fp, "    sete %%al\n");
    else if (op_code == GREATER)
        fprintf(fp, "    setg %%al\n");
    else if (op_code == LESS)
        fprintf(fp, "    setl %%al\n");

    fprintf(fp, "    movzbq %%al, %%rax\n");
    fprintf(fp, "    movq %%rax, %d(%%rbp)\n", result->offset);
}

void generate_global(Instruction* current, FILE* fp) {
    Instruction* aux = current;
    fprintf(fp, ".data\n");

    while (aux != NULL && aux->op_code == GLOBAL) {
        fprintf(fp, "%s:\n", aux->res->tag);
        fprintf(fp, "    .long %d\n", aux->dir1->value);
        aux = aux->next;
    }
}

void generate_gnu_assembly(InstructionList* list) {
    FILE* fp = fopen("output.s", "w");
    int max_offset = get_next_offset();
    Instruction* current = list->head;

    generate_global(current, fp);

    while (current != NULL) {
        switch (current->op_code) {
            case GLOBAL:
                break;

            case DECL_FUNC_INIT:
                name_func = current->res->tag;
                prologue(current->res->tag, current->res->offset, fp);
                Symbol* param_list = current->res->parameter_list->head;
                int i = 0;
                while (param_list != NULL) {
                    fprintf(fp, "    movq %s, %d(%%rbp)\n", registers_param[i], param_list->info->offset);
                    param_list = param_list->next;
                    i++;
                }
                break;

            case DECL_FUNC_END:
                fprintf(fp, "LABEL_RET_%s:\n", name_func);
                epilogue(fp);
                fprintf(fp, "    .section .note.GNU-stack,\"\",@progbits\n");
                break;

            case RETURN_EXPR:

                if (current->res->class_type == CLASS_GLOBAL)
                    fprintf(fp, "    movq %s(%%rip), %%rdi\n", current->res->tag);
                else if (current->res->class_type != CLASS_CONSTANT)
                    fprintf(fp, "    movq %d(%%rbp), %%rdi\n", current->res->offset);
                else
                    fprintf(fp, "    movq $%d, %%rdi\n", current->res->value);

                fprintf(fp, "    movq $%d, %%rsi\n", current->res->value_type);
                 fprintf(fp, "    call print\n");

                if (current->res->class_type == CLASS_GLOBAL)
                    fprintf(fp, "    movq %s(%%rip), %%rax\n", current->res->tag);
                else if (current->res->class_type != CLASS_CONSTANT)
                    fprintf(fp, "    movq  %d(%%rbp), %%rax\n", current->res->offset);
                else
                    fprintf(fp, "    movq $%d, %%rax\n", current->res->value);

                fprintf(fp, "    jmp LABEL_RET_%s\n", name_func);
                break;

            case RETURN_A:
                fprintf(fp, "    jmp LABEL_RET_%s\n", name_func);
                break;

            case MOV_G:
                if (current->dir1->value_type == CLASS_CONSTANT)
                    fprintf(fp, "    movq $%d, %s(%%rip)\n", current->dir1->value, current->res->tag);
                else
                    fprintf(fp, "    movq %d(%%rbp), %%rax\n", current->dir1->offset);
                    fprintf(fp, "    movq %%rax, %s(%%rip)\n", current->res->tag);
                break;

            case MOV_C:
                fprintf(fp, "    movq $%d, %d(%%rbp)\n", current->dir1->value, current->res->offset);
                break;

            case MOV_V:
                fprintf(fp, "    movq %d(%%rbp) , %%rax\n", current->dir1->offset);
                fprintf(fp, "    movq %%rax, %d(%%rbp)\n", current->res->offset);
                break;

            case OR:
            case ADD:
                if (current->dir1->class_type == CLASS_GLOBAL)
                    fprintf(fp, "    movq %s(%%rip), %%rax\n", current->dir1->tag);
                else if (current->dir1->class_type == CLASS_CONSTANT)
                    fprintf(fp, "    movq $%d, %%rax\n", current->dir1->value);
                else
                    fprintf(fp, "    movq %d(%%rbp), %%rax\n", current->dir1->offset);

                if (current->dir2->class_type == CLASS_GLOBAL)
                    fprintf(fp, "    addq %s(%%rip), %%rax\n", current->dir2->tag);
                else if (current->dir2->class_type == CLASS_CONSTANT)
                    fprintf(fp, "    addq $%d, %%rax\n", current->dir2->value);
                else
                    fprintf(fp, "    addq %d(%%rbp), %%rax\n", current->dir2->offset);

                    fprintf(fp, "    movq %%rax, %d(%%rbp)\n", current->res->offset);
                break;
         
            case AND:
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

            case SUB:
                if (current->dir1->class_type == CLASS_CONSTANT)
                    fprintf(fp, "    movq $%d, %%rax\n", current->dir1->value);
                else
                    fprintf(fp, "    movq %d(%%rbp), %%rax\n", current->dir1->offset);

                if (current->dir2->class_type == CLASS_CONSTANT)
                    fprintf(fp, "    subq $%d, %%rax\n", current->dir2->value);
                else
                    fprintf(fp, "    subq %d(%%rbp), %%rax\n", current->dir2->offset);

                fprintf(fp, "    movq %%rax, %d(%%rbp)\n", current->res->offset);
                break;

            case DIV:
                generate_div(current, fp);
                fprintf(fp, "    movq %%rax, %d(%%rbp)\n", current->res->offset);
                break;

            case MOD:
                generate_div(current, fp);
                fprintf(fp, "    movq %%rdx, %d(%%rbp)\n", current->res->offset);
                break;

            case MINUS:
                if (current->dir1->class_type == CLASS_CONSTANT) {
                    fprintf(fp, "    movq $%d, %%rax\n", current->dir1->value);
                } else {
                    fprintf(fp, "    movq %d(%%rbp), %%rax\n", current->dir1->offset);
                }

                fprintf(fp, "    negq %%rax\n");
                fprintf(fp, "    movq %%rax, %d(%%rbp)\n", current->res->offset);
                break;

            case EQUALS:
                generate_rel_operator(current->dir1, current->dir2, current->res, fp, current->op_code);
                break;

            case GREATER:
                generate_rel_operator(current->dir1, current->dir2, current->res, fp, current->op_code);
                break;

            case LESS:
                generate_rel_operator(current->dir1, current->dir2, current->res, fp, current->op_code);
                break;

            case NOT:
                if (current->dir1->class_type == CLASS_CONSTANT) {
                    fprintf(fp, "    movq $%d, %%rax\n", current->dir1->value);
                } else {
                    fprintf(fp, "    movq %d(%%rbp), %%rax\n", current->dir1->offset);
                }
                fprintf(fp, "    cmpq $0, %%rax\n");
                fprintf(fp, "    sete %%al\n");
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
                fprintf(fp, "    movq %%rax, %d(%%rbp)\n", current->res->offset);
                break;

            case LOAD:
                if (current->res->class_type != CLASS_CONSTANT)
                    fprintf(fp, "    movq %d(%%rbp),%s \n", current->res->offset, registers_param[current->dir2->value - 1]);
                else
                    fprintf(fp, "    movq $%d,%s \n", current->res->value, registers_param[current->dir2->value - 1]);
                break;

            default:
                break;
        }
        current = current->next;
    }
    fclose(fp);
}
