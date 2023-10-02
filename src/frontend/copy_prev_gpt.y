%{
#include <stdlib.h>
#include <stdio.h>
#include "stack.h"
#include "ast.h"
#include "errors.h"

int yylex(void);
void yyerror(const char *format,...);
extern  ASTNode* root; 
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
%token <int_val> TVOID
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
%type <node> expr
%type <node> valor
%type <node> sentence_list
%type <node> sentence
%type <node> declarations
%type <node> program
%type <node> method_decl
%type <node> methods
%type <node> block
%type <node> param
%type <node> param_list
%type <node> var_decl
%type <node> method_call
%type <node> expr_params
%type <node> body_program
%type <type_val> type


%left OR
%left AND
%nonassoc EQUALS '<' '>' 
%left '+' '-'
%left '*' '/' '%'
%right '!' TMENOS //como definir precedencia unaria
%%

init: program 
      ;

program: PROGRAM '{'{ open_level(); } body_program '}' {$$ = $4;}
      ;

body_program: declarations methods { $$ = create_ast_node(NULL,$1,$2);}
            | declarations { $$ = create_ast_node(NULL,$1,NULL);}
            | methods { $$ = create_ast_node(NULL,NULL,$1);}
            ;
            
methods: method_decl methods { $$ = root;}
        |  method_decl { $$ = root;}
      ;

method_decl: type ID param {
            if(look_and_hook($2) != NULL) 
                yyerror("method %s already declared", $2);
          
            } block {create_decl_func($1,$2,NULL,$4,yylineno);}

            | TVOID ID param {
            if(look_and_hook($2) != NULL) 
                yyerror("method %s already declared", $2);
            } block {create_decl_func(TYPE_VOID,$2,NULL,$4);}

            | TVOID ID param EXTERN {
            if(look_and_hook($2) != NULL) 
                yyerror("method %s already declared", $2);
            } ';' 
            
            | type ID param EXTERN {
            if(look_and_hook($2) != NULL) 
                yyerror("method %s already declared", $2);
            } ';' 
        ;
        
block: '{' {open_level();} declarations sentence_list '}'{close_level();
                        $$ = $3;} 
        | '{' sentence_list'}' {$$ = $2;}        ;
    
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

method_call: ID '(' expr_params ')' 
           | ID '(' ')' ;

expr_params: expr ',' expr_params 
            | expr 
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



type: TINT {$$ = TYPE_INT;}
    | TBOOL {$$ = TYPE_BOOL;}
    ;


valor : INT 
      | BOOL

    ;
 
%%
