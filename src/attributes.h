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
    CLASS_FUNCTION,
    CLASS_CONSTANT, 
    CLASS_OPERATION, //CLAS_ADD
    CLASS_ASSIGN, 
    CLASS_DECL, 
    CLASS_RETURN, 
    CLASS_SENTENCE_LIST,
    CLASS_DECL_LIST,
    CLASS_PROGRAM,
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