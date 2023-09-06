#ifndef ERRORS_H
#define ERRORS_H

#define MAX_ERRORS 100

typedef struct {
    char* message;
    int lineno;
} Error;

extern Error errors[MAX_ERRORS];
extern int numErrors;
void save_error(int lineno, const char *format, ...);

void printErrors();

#endif  // ERRORS_H