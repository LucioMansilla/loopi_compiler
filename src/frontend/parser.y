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
int count_params = 0;
%}

%union {
    int int_val;
    char *id_val;
    ASTNode *node;
    ValueType type_val;
    struct SymbolTable* st;
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
%type <st> param
%type <st> param_list
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
        Attributes* info = create_func_attributes($1,$3,$2,yylineno);
        insert_symbol_in_stack(info);
        insert_level($3); //push the params and insert into a new level.
    } 
    block { 
            close_level();
            Attributes* info = search_symbol($2);
            ASTNode* temp = create_decl_func(info,$5, yylineno);
            $$ = temp;
     }

    | TVOID ID param {
        if(look_and_hook($2) != NULL) 
            yyerror("Identifier %s already declared", $2);
        Attributes* info = create_func_attributes(TYPE_VOID,$3,$2,yylineno);
        insert_symbol_in_stack(info);
        insert_level($3);
    } 
    block {  close_level();
            Attributes* info = search_symbol($2);
            ASTNode* temp = create_decl_func(info,$5, yylineno);
            $$ = temp; }

    | TVOID ID param EXTERN {
        if(look_and_hook($2) != NULL) 
            yyerror("Identifier %s already declared", $2);
        Attributes* info = create_func_attributes(TYPE_VOID,$3,$2,yylineno);
        insert_symbol_in_stack(info);
    } 
    ';' {
         $$ = root; }

    | type ID param EXTERN {
        if(look_and_hook($2) != NULL) 
            yyerror("Identifier %s already declared", $2);
        Attributes* info = create_func_attributes(TYPE_VOID,$3,$2,yylineno);
        insert_symbol_in_stack(info);
    } 
    ';' { $$ = root; }
;


block: '{' { open_level(); } declarations sentence_list '}' { close_level(); $$ = $3; }
        | '{' sentence_list '}' { $$ = $2; }
        ;

param: '(' ')' { $$ = create_symbol_table(); }
      | '(' param_list ')' { $$ = $2; }
      ;

param_list: type ID { 
                SymbolTable* table = create_symbol_table();
                if(lookup_symbol(table,$2) != NULL) 
                    yyerror("Identifier %s already declared", $2);
                else {
                    Attributes* info = create_attributes($1,0,$2,yylineno,CLASS_FORMAL_PARAM);
                    insert_symbol(table,info);
                }
                $$ = table;
           }
         | param_list ',' type ID { 
                if(lookup_symbol($1,$4) != NULL) 
                    yyerror("Identifier %s already declared", $4);
                else {
                    Attributes* info = create_attributes($3,0,$4,yylineno,CLASS_FORMAL_PARAM);
                    insert_symbol($1,info);
                }
                $$ = $1;
           }
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

sentence_list: sentence sentence_list { $$ = create_sentence_list_node($1,$2);}
              | sentence { $$ = $1; }
              ;

sentence: ID '=' expr ';' { 
         Attributes* info = search_symbol($1);
         if (info == NULL) yyerror("Identifier %s not declared", $1);
         $$ = create_assign_node((create_ast_node(info,NULL,NULL)), $3, yylineno);
          }
         | method_call ';' { $$ = $1; }
         | RETURN expr ';' { $$ = create_return_node($2,yylineno); }
         | RETURN ';' { $$ = create_return_node(NULL,yylineno); }
         | IF '(' expr ')' THEN block { $$ = $6; }
         | IF '(' expr ')' THEN block ELSE block { $$ = $6; }
         | WHILE '(' expr ')' block { $$ = $5; }
         | ';' { $$ = root; }
         | block { $$ = $1; }
        ;

method_call: ID '(' expr_params ')' {
                Attributes* info = search_symbol($1);
                if(info == NULL || info->class_type != CLASS_DECL_FUNCTION)
                    yyerror("Method %s not declared", $1);
                if(info->parameter_list->length  != count_params){
                    printf("CountParams: %d",count_params);
                    printf("\nst_length: %d",info->parameter_list->length);
                    yyerror("Error with the params on: %s", $1);
                }
                count_params = 0;
                $$ = root;

                 }
           | ID '(' ')' { 
                Attributes* info = search_symbol($1);
                if(info == NULL || info->class_type != CLASS_DECL_FUNCTION)
                    yyerror("Method %s not declared", $1);

                $$ = root;
            }
           ;

expr_params: expr{
    count_params++;
} ',' expr_params { $$ = $1; }
            | expr { $$ = $1; count_params++;}
            ;

expr: valor { $$ = $1; }
    | ID   { 
               Attributes* info = search_symbol($1);
               if (info == NULL)
                    yyerror("Identifier %s not declared", $1);
               else
                  $$ = create_ast_node(info,NULL,NULL);  
             }
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

valor: INT { $$ = create_int_node($1,yylineno); }
      | BOOL { $$ = create_bool_node($1,yylineno); }
    ;
%%
