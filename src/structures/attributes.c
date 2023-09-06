#include "attributes.h"
#include <stdlib.h>

Attributes* create_attributes(ValueType valueType, int value, char* tag, int line, ClassType classType) {
    Attributes* attr = (Attributes*)malloc(sizeof(Attributes));
    attr->valueType = valueType;
    attr->value = value;
    attr->tag = tag;
    attr->line = line;
    attr->classType = classType;

    return attr;
}
Attributes* create_op_attributes(ValueType valueType, char op, int line, ClassType classType) {
    char* tag = (char*)malloc(2 * sizeof(char));
    tag[0] = op;
    tag[1] = '\0';
    return create_attributes(valueType, 0, tag, line, classType);
}
