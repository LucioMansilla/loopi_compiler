%{
#include <stdlib.h>
#include <stdio.h>
#include "ast.h"
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
 
prog: decl sentence_list | decl | sentence_list  { return 0; }
    ;
    
decl: type ID '=' expr ';' decl  
     | type ID '=' expr ';'
    ;

sentence_list: sentence  sentence_list | sentence { printf("Sentencia correcta \n"); }
    ;

sentence: ID '=' expr ';' | RETURN expr ';' 
    ;

expr: valor               

    | ID 

    | expr '+' expr    
    
    | expr '*' expr

    | '(' expr ')'      
    ;
    
type: TINT | TBOOL 
    ;  

valor : INT | BOOL            
    ;
 
%%

