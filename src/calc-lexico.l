%{

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "calc-sintaxis.tab.h"

%}

%option noyywrap
%option yylineno

letra [a-zA-Z]      
digito [0-9]
v_bool true|false

%%

{digito}+                     { 
                                printf("INT : %d\n",atoi(yytext)); 
                                return INT;}

"int"                          {  printf("%s\n",yytext);
                                  return TINT;}

{v_bool}                       {  printf("%s\n",yytext);
                                  return BOOL;}
								  
"bool"                         {  printf("%s\n",yytext);
                                  return TBOOL;}

"return"                  		 {  printf("%s\n",yytext);
                                  return RETURN;}

{letra}({letra}|{digito})*    { 
                                printf("ID : %s\n",yytext);
                                return ID;}

"-"                       {  printf("%s\n",yytext);
                                  return TMENOS;}    

[+*;()=]                   {  printf("%s\n",yytext);
                                  return *yytext;}

.|\n                          ; /* ignore all the rest */





%%

void yyerror(){
	printf("%s%d\n","-> ERROR Sintactico en la linea: ",yylineno);
}

int main(int argc,char *argv[]){
    ++argv, --argc;

    if (argc > 0) {
        char filepath[256];
        snprintf(filepath, sizeof(filepath), "../examples/%s", argv[0]);

        yyin = fopen(filepath, "r");
        if (yyin == NULL) {
            fprintf(stderr, "Could not open file: %s\\n", filepath);
            exit(1);
        }
    } else {
        yyin = stdin;
    }

    yyparse();
}
