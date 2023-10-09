#include "attributes.h"

#include <stdlib.h>

#include "ast.h"
#include "stdio.h"
Attributes* create_attributes(ValueType value_type, int value, char* tag, int line, ClassType class_type) {
    Attributes* attr = (Attributes*)malloc(sizeof(Attributes));
    attr->value_type = value_type;
    attr->value = value;
    attr->tag = tag;
    attr->line = line;
    attr->class_type = class_type;
    attr->offset = 0;

    return attr;
}

Attributes* create_func_attributes(ValueType value_type, SymbolTable* parameter_list, char* name, int line) {
    Attributes* attr = create_attributes(value_type, 0, name, line, CLASS_DECL_FUNCTION);
    attr->parameter_list = parameter_list;
    return attr;
}

Attributes* create_op_attributes(ValueType value_type, char* op, int line, ClassType class_type) {
    Attributes* new_attr = create_attributes(value_type, 0, op, line, class_type);
    new_attr->offset = get_next_offset();
    return new_attr;
}

char* get_type_str(int type) {
    switch (type) {
        case TYPE_INT:
            return "int";
        case TYPE_BOOL:
            return "bool";
        case TYPE_STRING:
            return "string";
        case TYPE_VOID:
            return "void";
        default:
            return "unknown";
    }
}
