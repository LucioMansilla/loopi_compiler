#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H
#include "structures/attributes.h"

typedef struct Symbol {
    Attributes *info;
    struct Symbol *next;
} Symbol;

typedef struct SymbolTable {
    Symbol *head;
    Symbol *tail;  // Pointer to the last element of the list
    int length;
} SymbolTable;

void insert_symbol(SymbolTable *table, Attributes *info);
void append_symbol(SymbolTable *table, Attributes *info);
Attributes *lookup_symbol(SymbolTable *table, char *id);
void print_symbol_table(SymbolTable *table);
SymbolTable *create_symbol_table();
#endif