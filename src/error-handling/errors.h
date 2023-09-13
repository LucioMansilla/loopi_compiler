#ifndef ERRORS_H
#define ERRORS_H

#define MAX_ERRORS 100
#define UNDECLARED_VARIABLE_CODE 2
#define TYPE_ERROR_OPERATION "Type Error in operation %s : left-hand side has type %s but right-hand side has type %s"
#define TYPE_ERROR_ASSIGNMENT "Type Error in : variable of type %s cannot be assigned a value of type %s"
#define TYPE_ERROR_DECLARATION "Type Error in : variable declared as %s but initialized with a value of type %s"

typedef struct {
    char* message;
    int lineno;
} Error;

extern Error errors[MAX_ERRORS];
extern int numErrors;
void save_error(int lineno, const char* format, ...);
void store_error(int lineno, const char* msg);
void printErrors();

#endif  // ERRORS_H
