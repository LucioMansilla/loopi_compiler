#ifndef ATTRIBUTES_H
#define ATTRIBUTES_H
typedef enum {
    TYPE_INT,
    TYPE_BOOL,
    TYPE_STRING,
    TYPE_VOID,
    NOT_TYPE,
} value_type;

typedef enum {
    CLASS_VAR,
    CLASS_FUNCTION,
    CLASS_CONSTANT,
    CLASS_ADD,
    CLASS_MUL,
    CLASS_ASSIGN,
    CLASS_DECL,
    CLASS_RETURN,
    CLASS_SENTENCE_LIST,
    CLASS_DECL_LIST,
    CLASS_PROGRAM,
    CLASS_IF,
} ClassType;

typedef struct Attributes {
    value_type value_type;
    int value;
    char* tag;
    int line;
    ClassType class_type;
} Attributes;

Attributes* create_attributes(value_type value_type, int value, char* tag, int line, ClassType class_type);
Attributes* create_op_attributes(value_type value_type, char op, int line, ClassType class_type);

#endif  // ATTRIBUTES_H