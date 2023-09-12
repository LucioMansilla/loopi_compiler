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
%token RETURN
%token IF
%token OR
%token AND
%type <node> expr
%type <node> valor
%type <node> declaration
%type <node> sentence_list
%type <node> sentence
%type <node> prog
%type <node> declarations
%type <type_val> type
    
%left '+' TMENOS OR
%left '*' AND

%%

init: { table = create_symbol_table(); } prog { root = $2; }
    ;

prog:
 declarations sentence_list { $$ = create_program_node($1, $2); }
             ;

declarations : declaration declarations { $$ = create_list_decl_node($1, $2); }
               | declaration { $$ = $1; }
             ;

declaration: type ID '=' expr ';'
     { 
         Attributes* info = lookup_symbol(table, $2);
         if(info != NULL) yyerror("Variable %s already declared", $2);
         
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
            if (info == NULL) save_error(yylineno,"Variable %s undeclared", $1,2);
            $$ = create_assign_node(create_ast_node(info, NULL, NULL), $3, yylineno);
         }
         | RETURN expr ';' { $$ = create_return_node($2,yylineno); }
         | IF '(' expr ')' '{' sentence_list '}'   
         { 
            $$ = create_if_node($3, $6, NULL, yylineno); 
         }
        ;       


expr: valor  { $$ = $1; }              
      | ID   { 
               Attributes* info = lookup_symbol(table, $1);
               if (info == NULL) save_error(yylineno,"Variable %s undeclared", $1,2);
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
        
        ;


type: TINT { $$ = TYPE_INT; }
    | TBOOL { $$ = TYPE_BOOL; }
    
    ;


valor : INT { $$ = create_int_node($1, yylineno); }
      | BOOL { $$ = create_bool_node($1, yylineno); }

    ;
 
%%
