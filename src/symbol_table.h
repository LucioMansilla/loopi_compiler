#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H
#include "attributes.h"
typedef struct Symbol {
    Attributes *info;
    struct Symbol *next;
} Symbol;

typedef struct SymbolTable {
    Symbol *head;
} SymbolTable;

void insert_symbol(SymbolTable *table, Attributes *info);
Symbol *lookup_symbol(SymbolTable *table, char *id);

#endif  // SYMBOL_TABLE_H