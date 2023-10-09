#ifndef STACK_H
#define STACK_H
#include "frontend/symbol_table.h"
#include "stdbool.h"
#include "stdlib.h"

typedef struct SymbolStack {
    SymbolTable *table;
    struct SymbolStack *next;
} SymbolStack;

void open_level(/*SymbolStack *stack,*/);
void close_level(/*SymbolStack *stack*/);
void insert_level(SymbolTable *table);
Attributes *lookup_in_all_levels(char *name);
void add_symbol_to_current_level(Attributes *info);
Attributes *lookup_in_current_level(char *name);
Attributes *lookup_in_global_level(char *name);
void add_func_to_st(ValueType type,char *tag, SymbolTable *param_list, int line, bool isExtern);
#endif