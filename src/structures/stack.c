#include "stack.h"

SymbolStack *stack = NULL;

void close_level() {
    if (stack != NULL) 
      stack = stack->next;
}

void open_level() {
    SymbolStack* temp = (SymbolStack*)malloc(sizeof(SymbolStack));
    temp->table = create_symbol_table();
    temp->next = stack;
    stack = temp;
}

void insert_symbol_in_stack(Attributes* info) {
    insert_symbol(stack->table, info);
}

bool search_symbol(char* name) {
    SymbolStack* temp = stack;
    while (temp != NULL) {
        Attributes* res = lookup_symbol(temp->table, name);
        if (res != NULL) return true;
        temp = temp->next;
    }
    return false;
}

Attributes* look_and_hook(char * name){
    return lookup_symbol(stack->table,name);
}
