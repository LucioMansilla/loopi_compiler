// errors.c

#include "errors.h"

Error errors[MAX_ERRORS];
int numErrors = 0;

void printErrors() {
    for (int i = 0; i < numErrors; i++) {
        printf("Error: %s at line %d\n", errors[i].message, errors[i].lineno);
    }
}