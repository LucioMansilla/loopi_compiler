#include "attributes.h"

#include <stdlib.h>

Attributes* create_attributes(value_type value_type, int value, char* tag, int line, ClassType classType) {
    Attributes* attr = (Attributes*)malloc(sizeof(Attributes));
    attr->value_type = value_type;
    attr->value = value;
    attr->tag = tag;
    attr->line = line;
    attr->classType = classType;

    return attr;
}
Attributes* create_op_attributes(value_type value_type, char op, int line, ClassType classType) {
    char* tag = (char*)malloc(2 * sizeof(char));
    tag[0] = op;
    tag[1] = '\0';
    return create_attributes(value_type, 0, tag, line, classType);
}
