#include "attributes.h"

#include <stdlib.h>

Attributes* create_attributes(ValueType value_type, int value, char* tag, int line, ClassType class_type) {
    Attributes* attr = (Attributes*)malloc(sizeof(Attributes));
    attr->value_type = value_type;
    attr->value = value;
    attr->tag = tag;
    attr->line = line;
    attr->class_type = class_type;

    return attr;
}
Attributes* create_op_attributes(ValueType value_type, char op, int line, ClassType class_type) {
    char* tag = (char*)malloc(2 * sizeof(char));
    tag[0] = op;
    tag[1] = '\0';
    return create_attributes(value_type, 0, tag, line, class_type);
}

char* get_type_str(int type) {
    switch (type) {
        case TYPE_INT: return "int";
        case TYPE_BOOL: return "bool";
        case TYPE_STRING: return "string";
        case TYPE_VOID: return "void";
        default: return "unknown";
    }
}
