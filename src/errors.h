#define MAX_ERRORS 100

typedef struct {
    char* message;
    int lineno;
} Error;

extern Error errors[MAX_ERRORS];
extern int numErrors;
void yyerror(const char* format, ...);
void yyerror_with_lineno(int lineno, const char* format, ...);

void printErrors();