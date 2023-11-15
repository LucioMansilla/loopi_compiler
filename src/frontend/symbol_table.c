#include "symbol_table.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void append_symbol(SymbolTable* table, Attributes* info) {
    Symbol* symbol = (Symbol*)malloc(sizeof(Symbol));
    symbol->info = info;
    symbol->next = NULL;

    if (table->head == NULL) {
        table->head = symbol;
        table->tail = symbol;
    } else {
        table->tail->next = symbol;
        table->tail = symbol;
    }
    table->length++;
}

void insert_symbol(SymbolTable* table, Attributes* info) {
    Symbol* symbol = (Symbol*)malloc(sizeof(Symbol));
    symbol->info = info;
    symbol->next = table->head;
    table->head = symbol;
    table->length++;
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
    table->tail = NULL;
    table->length = 0;
    return table;
}