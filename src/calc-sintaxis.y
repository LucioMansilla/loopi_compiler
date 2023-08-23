%{

#include <stdlib.h>
#include <stdio.h>

%}
 
%token INT
%token ID
%token BOOL
%token TINT
%token TBOOL
%token RETURN
%type expr
%type valor
    
%left '+' TMENOS 
%left '*'
 
%%
 
prog: decl sentence_list  { printf("No hay errores \n"); } 
    ;
    
decl: type ID '=' expr ';' decl 
     | type ID '=' expr ';' { printf("Declaracion correcta \n"); }
    ;

sentence_list: sentence  sentence_list | sentence { printf("Sentencia correcta \n"); }
    ;

sentence: ID '=' expr ';' | RETURN expr ';' { printf("Sentencia correcta \n"); }
    ;

expr: valor               

    | expr '+' expr    
    
    | expr '*' expr

    | '(' expr ')'      
    ;
    
type: TINT | TBOOL 
    ;  

valor : INT | BOOL            
    ;
 
%%

