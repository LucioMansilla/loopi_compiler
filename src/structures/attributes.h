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
    CLASS_SUB,
    CLASS_DIV,
    CLASS_MOD,
    CLASS_MINUS,
    CLASS_ASSIGN,
    CLASS_DECL,
    CLASS_RETURN,
    CLASS_RETURN_EXPR,
    CLASS_SENTENCE_LIST,
    CLASS_METHODS_DECL_LIST,
    CLASS_DECL_LIST,
    CLASS_PROGRAM,
    CLASS_OR,
    CLASS_AND,
    CLASS_NOT,
    CLASS_LESS,
    CLASS_GREATER,
    CLASS_EQUALS,
    CLASS_WHILE,
    CLASS_EMPTY,
    CLASS_BLOCK,
    CLASS_IF,
    CLASS_IF_THEN_ELSE,
    CLASS_ACTUAL_PARAM,
    CLASS_FORMAL_PARAM,
    CLASS_LABEL
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
Attributes* create_op_attributes(ValueType value_type, char* op, int line, ClassType class_type);
Attributes* create_func_attributes(ValueType value_type, SymbolTable* parameter_list, char* name, int line);
Attributes* create_attribute_order(int order);

char* get_type_str(int type);
#endif  // ATTRIBUTES_H