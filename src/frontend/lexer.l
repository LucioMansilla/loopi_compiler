%{
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "ast.h"
#include "parser.tab.h"
#include "errors.h"
#include <stdarg.h>
void yyerror(const char* format, ...);
%}

%option noyywrap
%option yylineno
%x COMMENT

letra [a-zA-Z_]     
digito [0-9]
v_bool true|false

%%
"#"[^\n]*                           { /* Ignora todo desde '#' hasta el final de la línea */ }
"/*"                                { BEGIN(COMMENT); }
<COMMENT>"*/"                       { BEGIN(INITIAL); }
<COMMENT>.|\n                       { /* Ignora todo dentro de COMMENT */ }


{digito}+                           { yylval.int_val = atoi(yytext); return INT; }

"Program"                           { return PROGRAM; }

"extern"                            { return EXTERN; }

"void"                              { return TVOID; }

"while"                             { return WHILE; }

"then"                              { return THEN; }

"else"                              { return ELSE; }

"int"                               { return TINT; }

"=="                                { return EQUALS; }

{v_bool}                            { yylval.int_val = strcmp(yytext, "true") == 0 ? 1 : 0; return BOOL; }
			  
"bool"                              { return TBOOL; }

"return"                            { return RETURN; }

"if"                                { return IF; }

"||"|or                             { return OR; }

&&|and                              { return AND; }

{letra}({letra}|{digito})*          { yylval.id_val = (char *) malloc(yyleng + 1);
                                      strcpy(yylval.id_val, yytext); 
                                      return ID; }

"-"                                 { return TMENOS; }    

[<>!+*;()={}/%]                          { return *yytext; }

" "|\n                                ;

.                                   { yyerror("Invalid Character %s",yytext); }

%%

void yyerror(const char* format, ...) {
    static char msg[256]; 
    va_list args;

    va_start(args, format);
    vsnprintf(msg, sizeof(msg), format, args);
    va_end(args);
    

    if(strcmp(msg, "syntax error") == 0) 
        snprintf(msg, sizeof(msg), "Syntax error near '%s'", yytext);
    store_error(yylineno,msg);
}

