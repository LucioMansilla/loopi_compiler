#include "symbol_table.h"
#include <stdlib.h>

void insert_symbol(SymbolTable* table, Attributes* info) {
    Symbol* symbol = (Symbol*)malloc(sizeof(Symbol));
    symbol->info = info;
    symbol->next = table->head;
    table->head = symbol;
}

Symbol* lookup_symbol(SymbolTable* table, char* id){
    Symbol* symbol = table->head;
    while (symbol != NULL) {
        if (strcmp(symbol->info->tag, id) == 0) {
            return symbol;
        }
        symbol = symbol->next;
    }
    return NULL;
}

