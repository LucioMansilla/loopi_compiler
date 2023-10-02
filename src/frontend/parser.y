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
        |  method_decl { $$ = $1;}
      ;

method_decl:
    type ID param {
        if(look_and_hook($2) != NULL) 
            yyerror("Identifier %s already declared", $2);
    } 
    block { ASTNode* temp = create_decl_func($1, $2, NULL, $5, yylineno);
            insert_symbol_in_stack(temp->info);
            $$ = temp;
     }

    | TVOID ID param {
        if(look_and_hook($2) != NULL) 
            yyerror("Identifier %s already declared", $2);
    } 
    block { $$ = create_decl_func(TYPE_VOID, $2, NULL, $5,yylineno); }

    | TVOID ID param EXTERN {
        if(look_and_hook($2) != NULL) 
            yyerror("Identifier %s already declared", $2);
    } 
    ';' { $$ = root; }

    | type ID param EXTERN {
        if(look_and_hook($2) != NULL) 
            yyerror("Identifier %s already declared", $2);
    } 
    ';' { $$ = root; }
;

        ;

block: '{' { open_level(); } declarations sentence_list '}' { close_level(); $$ = $3; }
        | '{' sentence_list '}' { $$ = $2; }
        ;

param: '(' ')' { $$ = root; }
      | '(' param_list ')' { $$ = $2; }
      ;

param_list: type ID ',' param_list { $$ = $4; }
           | type ID { $$ = root; }
           ;

declarations: declarations var_decl { $$ = create_list_decl_node($1,$2); }
             | var_decl { $$ = $1; }
             ;

var_decl: type ID '=' expr ';' { 
            Attributes* info = look_and_hook($2);
            if (info != NULL) 
                yyerror("Identifier %s already declared", $2);
            else {
                ASTNode* id = create_id_node($2,yylineno);
                insert_symbol_in_stack(id->info);
                $$ = create_single_decl_node($1,id,$4,yylineno);
            }
     }
        ;

sentence_list: sentence sentence_list { $$ = $1; }
              | sentence { $$ = $1; }
              ;

sentence: ID '=' expr ';' { $$ = $3; }
         | method_call ';' { $$ = $1; }
         | RETURN expr ';' { $$ = $2; }
         | RETURN ';' { $$ = root; }
         | IF '(' expr ')' THEN block { $$ = $6; }
         | IF '(' expr ')' THEN block ELSE block { $$ = $6; }
         | WHILE '(' expr ')' block { $$ = $5; }
         | ';' { $$ = root; }
         | block { $$ = $1; }
        ;

method_call: ID '(' expr_params ')' { $$ = $3; }
           | ID '(' ')' { $$ = root; }
           ;

expr_params: expr ',' expr_params { $$ = $1; }
            | expr { $$ = $1; }
            ;

expr: valor { $$ = $1; }
    | ID { $$ = root; }
    | expr '+' expr { $$ = $1; }
    | expr '*' expr { $$ = $1; }
    | '(' expr ')' { $$ = $2; }
    | expr OR expr { $$ = $1; }
    | expr AND expr { $$ = $1; }
    | method_call { $$ = $1; }
    | TMENOS expr { $$ = $2; }
    | '!' expr { $$ = $2; }
    | expr '<' expr { $$ = $1; }
    | expr '>' expr { $$ = $1; }
    | expr EQUALS expr { $$ = $1; }
    | expr '-' expr { $$ = $1; }
    | expr '/' expr { $$ = $1; }
    | expr '%' expr { $$ = $1; }
    ;

type: TINT { $$ = TYPE_INT; }
    | TBOOL { $$ = TYPE_BOOL; }
    ;

valor: INT { $$ = root; }
      | BOOL { $$ = root; }
    ;
%%
