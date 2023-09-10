%{
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "ast.h"
#include "parser.tab.h"
#include "errors.h"
#include <stdarg.h>
%}

%option noyywrap
%option yylineno

letra [a-zA-Z]      
digito [0-9]
v_bool true|false

%%
"#"[^\n]*           { /* Ignora todo desde '#' hasta el final de la línea */ }

{digito}+           { yylval.int_val = atoi(yytext); return INT; }

"int"               { return TINT; }

{v_bool}            { yylval.int_val = strcmp(yytext, "true") == 0 ? 1 : 0; return BOOL; }
			  
"bool"              { return TBOOL; }

"return"            { return RETURN; }

"if" { return IF; }

{letra}({letra}|{digito})*          { yylval.id_val = (char *) malloc(yyleng + 1);
                                      strcpy(yylval.id_val, yytext); 
                                      return ID; }

"-"                       { return TMENOS; }    

[+*;()={}]                  { return *yytext; }

.|\n                          ; 


%%

void yyerror(const char* format, ...) {
    static char msg[256]; 
    va_list args;

    va_start(args, format);
    vsnprintf(msg, sizeof(msg), format, args);
    va_end(args);

    if(numErrors < MAX_ERRORS) {
        errors[numErrors].message = strdup(msg);
        errors[numErrors].lineno = yylineno;
        numErrors++;
    }
}
