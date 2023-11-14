#include "errors.h"

#include <limits.h>
#include <math.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "stack.h"
#include "symbol_table.h"


Error errors[MAX_ERRORS];
int numErrors = 0;
extern SymbolStack* stack;

void printErrors() {
    for (int i = 0; i < numErrors; i++) {
        printf("%s at line %d\n", errors[i].message, errors[i].lineno);
    }
}

int levenshtein_distance(const char* s1, const char* s2);
char* find_closest_match(SymbolTable* table, const char* var_name);

void save_error(int lineno, const char* format, ...) {
    static char msg[256];
    va_list args;
    char* suggestion = NULL;

    va_start(args, format);
    vsnprintf(msg, sizeof(msg), format, args);
    va_end(args);

    // Restart va_list before using it again
    va_start(args, format);

    const char* var_name = va_arg(args, const char*);
    int error_code = va_arg(args, int);

    print_symbol_table(stack->table);
    if (error_code == UNDECLARED_CODE) suggestion = find_closest_match(stack->table, var_name);
    va_end(args);

    if (suggestion) {
        strncat(msg, ";\nDid you mean: ", sizeof(msg) - strlen(msg) - 1);
        strncat(msg, suggestion, sizeof(msg) - strlen(msg) - 1);
        strncat(msg, "?", sizeof(msg) - strlen(msg) - 1);
        free(suggestion);
    }
    store_error(lineno, msg);
}

// void undeclared_error(int lineno,

void store_error(int lineno, const char* msg) {
    if (numErrors < MAX_ERRORS) {
        errors[numErrors].message = strdup(msg);
        errors[numErrors].lineno = lineno;
        numErrors++;
    }
}

char* find_closest_match(SymbolTable* table, const char* var_name) {
    char* closest_match = NULL;
    int min_distance = INT_MAX;
    Symbol* symbol = table->head;

    while (symbol != NULL) {
        if (symbol->info->tag == NULL || var_name == NULL) {
            symbol = symbol->next;
            continue;
        }
        int distance = levenshtein_distance(symbol->info->tag, var_name);
        if (distance < min_distance) {
            closest_match = symbol->info->tag;
            min_distance = distance;
        }
        symbol = symbol->next;
    }

    return closest_match ? strdup(closest_match) : NULL;
}

int levenshtein_distance(const char* s1, const char* s2) {
    int len1 = strlen(s1), len2 = strlen(s2);
    int dp[len1 + 1][len2 + 1];

    for (int i = 0; i <= len1; i++) {
        for (int j = 0; j <= len2; j++) {
            if (i == 0)
                dp[i][j] = j;
            else if (j == 0)
                dp[i][j] = i;
            else {
                int cost = (s1[i - 1] == s2[j - 1]) ? 0 : 1;
                dp[i][j] = fmin(fmin(dp[i - 1][j], dp[i][j - 1]) + 1, dp[i - 1][j - 1] + cost);
            }
        }
    }

    return dp[len1][len2];
}
