#ifndef STACK_H
#define STACK_H
#include "stdbool.h"
#include "stdlib.h"
#include "symbol_table.h"

typedef struct SymbolStack {
    SymbolTable *table;
    struct SymbolStack *next;
} SymbolStack;


void open_level(/*SymbolStack *stack,*/);
void close_level(/*SymbolStack *stack*/);
bool search_symbol(char *name);
void insert_symbol_in_stack(Attributes *info);
Attributes* look_and_hook(char *name);
#endif