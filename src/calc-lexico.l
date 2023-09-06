%{
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "ast.h"
#include "calc-sintaxis.tab.h"
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

{digito}+ { yylval.int_val = atoi(yytext); return INT; }

"int"                          {  //printf("%s\n",yytext);
                                  return TINT;}

{v_bool} { yylval.int_val = strcmp(yytext, "true") == 0 ? 1 : 0; return BOOL; }

								  
"bool"                         {  //printf("%s\n",yytext);
                                  return TBOOL;}

"return"                  		 {  //printf("%s\n",yytext);
                                  return RETURN;}

{letra}({letra}|{digito})* { 
    yylval.id_val = (char *) malloc(yyleng + 1);
    strcpy(yylval.id_val, yytext); 
    return ID; 
}

"-"                       {  //printf("%s\n",yytext);
                                  return TMENOS;}    

[+*;()=]                   {  //printf("%s\n",yytext);
                                  return *yytext;}

.|\n                          ; /* ignore all the rest */


%%

// lexer.l
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

