#ifndef ATTRIBUTES_H
#define ATTRIBUTES_H

typedef struct SymbolTable SymbolTable;
typedef enum {
    TYPE_INT,
    TYPE_BOOL,
    TYPE_STRING,
    TYPE_VOID,
    NOT_TYPE,
} ValueType;

typedef enum {
    CLASS_VAR,
    CLASS_DECL_FUNCTION,
    CLASS_CALL_FUNCTION,
    CLASS_CONSTANT,
    CLASS_ADD,
    CLASS_MUL,
    CLASS_ASSIGN,
    CLASS_DECL,
    CLASS_RETURN,
    CLASS_SENTENCE_LIST,
    CLASS_DECL_LIST,
    CLASS_PROGRAM,
    CLASS_OR,
    CLASS_IF,
    CLASS_FORMAL_PARAM,
} ClassType;

typedef struct Attributes {
    ValueType value_type;
    int value;
    char* tag;
    int line;
    ClassType class_type;
    int offset;
    SymbolTable* parameter_list;
} Attributes;

Attributes* create_attributes(ValueType value_type, int value, char* tag, int line, ClassType class_type);
Attributes* create_op_attributes(ValueType value_type, char op, int line, ClassType class_type);
Attributes* create_func_attributes(ValueType value_type, SymbolTable* parameter_list, char* name, int line);

char* get_type_str(int type);
#endif  // ATTRIBUTES_H