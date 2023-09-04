#include "errors.h"

#include <stdarg.h>
#include <stdio.h>
#include <string.h>

Error errors[MAX_ERRORS];
int numErrors = 0;

void printErrors() {
    for (int i = 0; i < numErrors; i++) {
        printf("Error %s at line %d\n", errors[i].message, errors[i].lineno);
    }
}

void save_error(int lineno, const char *format, ...) {
    static char msg[256];  // Buffer estático para el mensaje
    va_list args;

    va_start(args, format);
    vsnprintf(msg, sizeof(msg), format, args);
    va_end(args);

    if (numErrors < MAX_ERRORS) {
        errors[numErrors].message = strdup(msg);  // Duplicar la cadena para evitar problemas con el buffer estático
        errors[numErrors].lineno = lineno;
        numErrors++;
    }
}