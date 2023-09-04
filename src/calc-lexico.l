%{

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "ast.h"
#include "calc-sintaxis.tab.h"
#include "symbol_table.h"
#include "errors.h"
#include "semantic.h"
#include "eval.h"
#include <stdarg.h>
extern ASTNode* root;
extern SymbolTable* table;
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
    static char msg[256]; // Buffer estático para el mensaje
    va_list args;

    va_start(args, format);
    vsnprintf(msg, sizeof(msg), format, args);
    va_end(args);

    if(numErrors < MAX_ERRORS) {
        errors[numErrors].message = strdup(msg); // Duplicar la cadena para evitar problemas con el buffer estático
        errors[numErrors].lineno = yylineno;
        numErrors++;
    }
}


int main(int argc,char *argv[]){
    ++argv, --argc;

        if (argc > 0) {
            yyin = fopen(argv[0], "r");
            if (yyin == NULL) {
                fprintf(stderr, "Could not open file: %s\n", argv[0]);
                exit(1);
            }
        } else {
            yyin = stdin;
        }

    yyparse();
    if (numErrors) {
        printErrors();
        exit(1);
    }
    check_types(root, table);
    if (numErrors) {
        printErrors();
        exit(1);
    }

    eval(root, table);
    generate_dot_file(root,"ast.dot");



}

