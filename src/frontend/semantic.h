#ifndef SEMANTIC_H
#define SEMANTIC_H
#include <stdbool.h>

#include "../error-handling/errors.h"
#include "../structures/ast.h"

void check_types(ASTNode* node);
bool has_main(ASTNode* root);
#endif