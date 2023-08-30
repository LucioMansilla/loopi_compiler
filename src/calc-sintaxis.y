%{
#include <stdlib.h>
#include <stdio.h>
#include "ast.h"
ASTNode* root = NULL;  
%}

%union {
    int int_val;
    char *id_val;
    ASTNode *node;

}
%token <int_val> INT
%token <id_val> ID
%token <int_val> BOOL
%token TINT
%token TBOOL
%token RETURN
%type expr
%type <int_val> valor
    
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

valor : INT 
     | BOOL     
    ;
 
%%

