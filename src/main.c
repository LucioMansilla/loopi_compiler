#include <stdio.h>
#include <stdlib.h>

#include "errors.h"
#include "semantic.h"
extern int yyparse(void);
extern FILE* yyin;
ASTNode* root = NULL;

int main(int argc, char* argv[]) {
    ++argv, --argc;

    if (argc > 0) {
        yyin = fopen(argv[0], "r");
        if (yyin == NULL) {
            fprintf(stderr, "Could not open file: %s\n", argv[0]);
            exit(1);
        }
    } else {
        yyin = stdin;
    }

    yyparse();

    if (numErrors) {
        printErrors();
        exit(1);
    }

    check_types(root);

    if (numErrors) {
        printErrors();
        exit(1);
    }

    eval(root);
    generate_dot_file(root, "ast.dot");
}
