#ifndef ATTRIBUTES_H
#define ATTRIBUTES_H
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
} ClassType;

typedef struct Attributes {
    ValueType value_type;
    int value;
    char* tag;
    int line;
    ClassType class_type;
    int offset;
    char* parameter_list;
} Attributes;

Attributes* create_attributes(ValueType value_type, int value, char* tag, int line, ClassType class_type);
Attributes* create_op_attributes(ValueType value_type, char op, int line, ClassType class_type);
Attributes* create_func_attributes(ValueType value_type, char* parameter_list, char* name, ASTNode* body, int line);

char* get_type_str(int type);

#endif  // ATTRIBUTES_H