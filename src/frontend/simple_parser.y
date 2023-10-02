%{
#include <stdlib.h>
#include <stdio.h>
#include "symbol_table.h"
#include "ast.h"
#include "errors.h"

int yylex(void);
void yyerror(const char *format,...);
extern  ASTNode* root; 
SymbolTable* table;    
extern int yylineno;  
%}

%union {
    int int_val;
    char *id_val;
    ASTNode *node;
    ValueType type_val;
}

%token <int_val> INT
%token <id_val> ID
%token <int_val> BOOL
%token TINT
%token TBOOL
%token TVOID
%token RETURN
%token IF
%token OR
%token AND
%token PROGRAM
%token EXTERN
%token THEN
%token ELSE
%token WHILE
%token EQUALS
%type expr
%type valor
%type sentence_list
%type sentence
%type declarations
%type program
%type method_decl
%type methods
%type block
%type param
%type param_list
%type var_decl
%type type
    
%right EQUALS
%left OR
%left AND
%left '<' '>'
%left '+' '-'
%left '*' '/' '%'
%right '!' TMENOS
%%

init: program 
      ;

program: PROGRAM '{' declarations methods '}'
         | PROGRAM '{' declarations '}'
         | PROGRAM '{' methods '}'
      ;

methods: method_decl methods 
        |  method_decl
      ;


method_decl: type ID param block
            | TVOID ID param block
            | TVOID ID param EXTERN ';'
            | type ID param EXTERN ';' 
                      ;
block: '{' declarations sentence_list '}' 
        | '{' sentence_list'}'
        ;
    
param: '(' ')' | '(' param_list ')' ;

param_list : type ID ',' param_list |  type ID ; 

declarations :  declarations var_decl 
               | var_decl 
             ;

var_decl: type ID '=' expr ';'
    ;             
sentence_list: sentence sentence_list 
              | sentence 
         ;
sentence: ID '=' expr ';'
         | method_call ';'
         | RETURN expr ';' 
         | RETURN ';'
         | IF '(' expr ')' THEN block 
         | IF '(' expr ')' THEN block ELSE block  
         | WHILE '(' expr ')' block
         | ';'
         | block
        ;       

method_call: ID '(' expr_params ')' ;

expr_params: expr ',' expr_params 
            | expr 
            | 
          ;

expr: valor              
    | ID   
    | expr '+' expr  
    | expr '*' expr  
    | '(' expr ')'
    | expr OR expr 
    | expr AND expr 
    | method_call
    | TMENOS expr
    | '!' expr
    | expr '<' expr 
    | expr '>' expr
    | expr EQUALS expr
    | expr '-' expr
    | expr '/' expr
    | expr '%' expr  
    ;



type: TINT 
    | TBOOL 
    ;


valor : INT 
      | BOOL

    ;
 
%%
