#include "symbol_table.h"

SymbolTable* create_symbol_table() {
    SymbolTable* table = (SymbolTable*)malloc(sizeof(SymbolTable));
    table->head = NULL;
    return table;
}

void insert_symbol(SymbolTable* table, Attributes* info) {
    Symbol* new_symbol = (Symbol*)malloc(sizeof(Symbol));
    new_symbol->info = info;
    new_symbol->next = table->head;
    table->head = new_symbol;
}

Symbol* lookup_symbol(SymbolTable* table, char* id) {
    Symbol* current = table->head;
    while (current != NULL) {
        if (strcmp(current->info->id, id) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

void delete_symbol(SymbolTable* table, char* id) {
    Symbol* current = table->head;
    Symbol* previous = NULL;
    while (current != NULL) {
        if (strcmp(current->info->id, id) == 0) {
            if (previous == NULL) {
                table->head = current->next;
            } else {
                previous->next = current->next;
            }
            free(current);
            return;
        }
        previous = current;
        current = current->next;
    }
}
