#ifndef ATTRIBUTES_H
#define ATTRIBUTES_H
typedef enum {
    TYPE_INT,
    TYPE_BOOL,
} ValueType;

typedef enum {
    CLASS_VAR,
    CLASS_FUNCTION,
    CLASS_CONSTANT,
    CLASS_OPERATION,
    CLASS_ASIGN,
} ClassType;

typedef struct Attributes {
    ValueType valueType;
    int value;
    char *tag;
    int line;
    ClassType classType;
} Attributes;

#endif  // ATTRIBUTES_H