#include <stdio.h>
#include <stdlib.h>

#include "backend/assembly-codegen/assembly-codegen.h"
#include "backend/intermediate-codegen/pseudo-codegen.h"
#include "backend/interpreter/eval.h"
#include "error-handling/errors.h"
#include "frontend/semantic.h"

extern int yyparse(void);
extern FILE* yyin;
extern int yylineno;
ASTNode* root = NULL;

void init_syntax_analysis();
void init_semantic_analysis();

int main(int argc, char* argv[]) {
    ++argv, --argc;

    if (argc > 0) {
        yyin = fopen(argv[0], "r");
        if (yyin == NULL) {
            fprintf(stderr, "Could not open file: %s\n", argv[0]);
            exit(EXIT_FAILURE);
        }
    } else {
        yyin = stdin;
    }

    init_syntax_analysis();
    init_semantic_analysis();

    // eval(root);
    InstructionList* list = generate_tac(root);
    //print_instruction_list(list);
    generate_gnu_assembly(list);
    generate_dot_file(root, "ast.dot");
    return EXIT_SUCCESS;
}

void init_syntax_analysis() {
    yyparse();
    if (numErrors) {
        printErrors();
        exit(1);
    }
}

void init_semantic_analysis() {
    if (!has_main(root)) save_error(yylineno, MISSING_MAIN);

    check_types(root);
    if (numErrors) {
        printErrors();
        exit(EXIT_FAILURE);
    }
}