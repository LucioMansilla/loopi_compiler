#ifndef ATTRIBUTES_H
#define ATTRIBUTES_H
typedef enum {
    TYPE_INT,
    TYPE_BOOL,
    TYPE_STRING,
    TYPE_VOID,
} ValueType;

typedef enum {
    CLASS_VAR = 0,
    CLASS_FUNCTION = 1,
    CLASS_CONSTANT = 2,
    CLASS_OPERATION = 3,
    CLASS_ASSIGN = 4,
    CLASS_DECL = 5,
    CLASS_RETURN = 6,
    CLASS_SENTENCE_LIST = 7,
    CLASS_DECL_LIST = 8,
    CLASS_PROGRAM = 9,

} ClassType;

typedef struct Attributes {
    ValueType valueType;
    int value;
    char* tag;
    int line;
    ClassType classType;
} Attributes;

Attributes* create_attributes(ValueType valueType, int value, char* tag, int line, ClassType classType);
Attributes* create_op_attributes(ValueType valueType, char op, int line, ClassType classType);

#endif  // ATTRIBUTES_H