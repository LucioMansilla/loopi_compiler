#include "symbol_table.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void insert_symbol(SymbolTable* table, Attributes* info) {
    Symbol* symbol = (Symbol*)malloc(sizeof(Symbol));
    symbol->info = info;
    symbol->next = table->head;
    table->head = symbol;
}

Attributes* lookup_symbol(SymbolTable* table, char* id) {
    Symbol* symbol = table->head;
    while (symbol != NULL) {
        if (strcmp(symbol->info->tag, id) == 0) {
            return symbol->info;
        }
        symbol = symbol->next;
    }
    return NULL;
}

void print_symbol_table(SymbolTable* table) {
    Symbol* symbol = table->head;
    while (symbol != NULL) {
        printf("Symbol: %s\n", symbol->info->tag);
        symbol = symbol->next;
    }
}

SymbolTable* create_symbol_table() {
    SymbolTable* table = (SymbolTable*)malloc(sizeof(SymbolTable));
    table->head = NULL;
    return table;
}