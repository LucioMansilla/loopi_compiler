
#include <stdio.h>

extern int yyparse();

int main(int argc, char **argv) {
    // Add code here to open and read from specific files
    // For now, we'll just parse from standard input
    yyparse();
    return 0;
}
