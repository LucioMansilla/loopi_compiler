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
%type <type_val> type
    
%left '+' TMENOS OR
%left '*' AND

%%

init: { table = create_symbol_table(); } program { root = $2; }
    ;

program: PROGRAM '{' declarations methods '}'
             ;
methods: method_decl methods 
        |  method_decl
        ;

method_decl: type ID param block
            | type ID param EXTERN ';' 
                      ;
block: '{' declarations sentence_list '}' ;
    
param: '(' ')' | '(' param_list ')' ;

param_list : type ID ',' param_list |  type ID ; 

declarations :  declarations var_decl { $$ = create_list_decl_node($1, $2); }
               | var_decl { $$ = $1; }
             ;

var_decl: type ID '=' expr ';'
     { 
         Attributes* info = lookup_symbol(table, $2);
         if(info != NULL) yyerror("variable %s already declared", $2);
         
         ASTNode* id = create_id_node($2,yylineno);
         insert_symbol(table, id->info);
         $$ = create_single_decl_node($1, id, $4,yylineno);
     }
    ;             

sentence_list: sentence sentence_list 
              { 
                  $$ = create_sentence_list_node($1, $2);
              }
              | sentence 
              { 
                  $$ = $1;
              }
         ;

sentence: ID '=' expr ';' 
         {  
            Attributes* info = lookup_symbol(table,$1);
            if (info == NULL) save_error(yylineno, "Variable %s undeclared", $1, table, UNDECLARED_VARIABLE_CODE);
            $$ = create_assign_node(create_ast_node(info, NULL, NULL), $3, yylineno);
         }
         | RETURN expr ';' { $$ = create_return_node($2,yylineno); } 
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

expr: valor  { $$ = $1; }              
      | ID   { 
               Attributes* info = lookup_symbol(table, $1);
               if (info == NULL) save_error(yylineno, "Variable %s undeclared", $1, table, UNDECLARED_VARIABLE_CODE);
               $$ = create_ast_node(info,NULL,NULL);  
             }

    | expr '+' expr  
             { 
               Attributes* attr = create_op_attributes(NOT_TYPE, '+', yylineno, CLASS_ADD);
               $$ = create_ast_node(attr, $1, $3);
             }

    | expr '*' expr  
            { 
              Attributes* attr = create_op_attributes(NOT_TYPE, '*',yylineno, CLASS_MUL);
              $$ = create_ast_node(attr, $1, $3);
            }

    | '(' expr ')' { $$ = $2; }

    | expr OR expr 
            { 
              Attributes* attr = create_attributes(TYPE_BOOL,0,"||",yylineno, CLASS_ADD);
              $$ = create_ast_node(attr, $1, $3);
            }
            
    | expr AND expr 
            { 
              Attributes* attr = create_attributes(TYPE_BOOL,0,"&&",yylineno, CLASS_MUL);
              $$ = create_ast_node(attr, $1, $3);
            }
        
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


type: TINT { $$ = TYPE_INT; }
    | TBOOL { $$ = TYPE_BOOL; }
    | TVOID { $$ = TYPE_VOID; }
    
    ;


valor : INT { $$ = create_int_node($1, yylineno); }
      | BOOL { $$ = create_bool_node($1, yylineno); }

    ;
 
%%
