#include "attributes.h"
typedef struct Symbol {
    Attributes* info;
    struct Symbol* next;
} Symbol;

typedef struct SymbolTable {
    Symbol* head;
} SymbolTable;

void insert_symbol(SymbolTable *table, Attributes *info);
Symbol* lookup_symbol(SymbolTable *table, char *id);
void delete_symbol(SymbolTable *table, char *id);
void destroy_symbol_table(SymbolTable *table);

