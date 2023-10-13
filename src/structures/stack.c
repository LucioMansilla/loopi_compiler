#include "stack.h"

SymbolStack* stack = NULL;

void close_level() {
    if (stack != NULL) stack = stack->next;
}

void open_level() {
    SymbolStack* temp = (SymbolStack*)malloc(sizeof(SymbolStack));
    temp->table = create_symbol_table();
    temp->next = stack;
    stack = temp;
}

void insert_level(SymbolTable* table) {
    SymbolStack* temp = (SymbolStack*)malloc(sizeof(SymbolStack));
    temp->table = table;
    temp->next = stack;
    stack = temp;
}

void add_symbol_to_current_level(Attributes* info) {
    insert_symbol(stack->table, info);
}

Attributes* lookup_in_all_levels(char* name) {
    SymbolStack* temp = stack;
    while (temp != NULL) {
        Attributes* res = lookup_symbol(temp->table, name);
        if (res != NULL) return res;
        temp = temp->next;
    }
    return NULL;
}

Attributes* lookup_in_current_level(char* name) {
    return lookup_symbol(stack->table, name);
}

Attributes* lookup_in_global_level(char* name) {
    SymbolStack* temp = stack;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    return lookup_symbol(temp->table, name);
}

void add_func_to_st(ValueType type, char* tag, SymbolTable* param_list, int line, bool isExtern) {
    Attributes* info = create_func_attributes(type, param_list, tag, line);
    add_symbol_to_current_level(info);
    if (!isExtern) 
        insert_level(param_list);
}
