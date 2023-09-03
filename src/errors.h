// errors.h

#define MAX_ERRORS 10

typedef struct {
    char* message;
    int lineno;
} Error;

extern Error errors[MAX_ERRORS];
extern int numErrors;

void printErrors();