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
extern int curr_offset;
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
%token NOT
%token TMENOS
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
%left NOT TMINUS 
%%

init: program 
      ;
program: PROGRAM '{'{ open_level(); } body_program '}' {
        $$ = $4;
        root = $4;
        }
      ;
body_program: declarations methods { $$ = create_program_node($1,$2);}
            | declarations { $$ = create_program_node($1,NULL);}
            | methods { $$ = create_program_node(NULL,$1);}
            ;
            
methods: method_decl methods { $$ = create_methods_decl_list_node($1,$2);}
        |  method_decl { $$ = $1;}
      ;
method_decl:
    type ID param {
        if(lookup_in_current_level($2) != NULL) 
            save_error(yylineno,"Try to declare the method: %s but the identifier already declared", $2);
       
        add_func_to_st($1,$2,$3,yylineno,false);
        if($3->length > 0)
            curr_offset = $3->tail->info->offset;
    } 
    block { 
            close_level();
            Attributes* info = lookup_in_all_levels($2);
            ASTNode* temp = create_decl_func_node(info,$5);
            temp->info->offset = curr_offset;
            curr_offset = 0;
            $$ = temp;
     }
    | TVOID ID param {
        if(lookup_in_current_level($2) != NULL) 
            yyerror("Try to declare the method: %s but the identifier already declared", $2);
        add_func_to_st(TYPE_VOID,$2,$3,yylineno,false);
    } 
    block {  close_level();
            Attributes* info = lookup_in_all_levels($2);
            ASTNode* temp = create_decl_func_node(info,$5);
            $$ = temp; }

    | TVOID ID param EXTERN {
        if(lookup_in_current_level($2) != NULL) 
            yyerror("Try to declare the method: %s but the identifier already declared", $2);
        add_func_to_st(TYPE_VOID,$2,$3,yylineno,true);
        
    } 
    ';' {
            Attributes* info = lookup_in_all_levels($2);
            ASTNode* temp = create_decl_func_node(info,NULL);
            $$ = temp;     
          }

    | type ID param EXTERN {
        if(lookup_in_current_level($2) != NULL) 
            yyerror("Try to declare the method: %s but the identifier already declared", $2);
        add_func_to_st($1,$2,$3,yylineno,true);
    } 
    ';' {   Attributes* info = lookup_in_all_levels($2);
            ASTNode* temp = create_decl_func_node(info,NULL);
            $$ = temp;
    }
;

block: '{' { open_level(); } declarations sentence_list '}' { close_level(); 
                $$ = create_block_node($3,$4,yylineno);
}
        | '{' sentence_list '}' { $$ = create_block_node(NULL,$2,yylineno); }
        ;

param: '(' ')' { 
    $$ = create_symbol_table(); }
      | '(' param_list ')' { $$ = $2; }
      ;

param_list: type ID { 
                SymbolTable* table = create_symbol_table();
                if(lookup_symbol(table,$2) != NULL) 
                    yyerror("Identifier %s already declared", $2);
                else {
                    Attributes* info = create_attributes($1,0,$2,yylineno,CLASS_FORMAL_PARAM);
                    info->offset = get_next_offset();
                    append_symbol(table,info);
                }
                $$ = table;
           }
         | param_list ',' type ID { 
                if(lookup_symbol($1,$4) != NULL) 
                    yyerror("Identifier %s already declared", $4);
                else {
                    Attributes* info = create_attributes($3,0,$4,yylineno,CLASS_FORMAL_PARAM);
                    info->offset = get_next_offset();
                    append_symbol($1,info);
                }
                $$ = $1;
           }
           ;

declarations: declarations var_decl { $$ = create_list_decl_node($1,$2); }
             | var_decl { $$ = $1; }
             ;

var_decl: type ID '=' expr ';' { 
            Attributes* info = lookup_in_current_level($2);
            if (info != NULL) 
                yyerror("Identifier %s already declared", $2);
            else {
                ASTNode* id = create_id_node($2,yylineno);
                add_symbol_to_current_level(id->info);
                $$ = create_single_decl_node($1,id,$4,yylineno);
            }
     }
     ;
sentence_list: sentence sentence_list { $$ = create_sentence_list_node($1,$2);}
              | sentence { $$ = $1; }
              ;

sentence: ID '=' expr ';' { 
         Attributes* info = lookup_in_all_levels($1);
         if (info == NULL) yyerror("Identifier %s not declared", $1);
         $$ = create_assign_node((create_ast_node(info,NULL,NULL)), $3, yylineno);
          }
         | method_call ';' { $$ = $1; }
         | RETURN expr ';' { $$ = create_return_expr_node($2,yylineno); }
         | RETURN ';' { $$ = create_return_node(yylineno); }
         | IF '(' expr ')' THEN block { 
                                    $$ = create_if_node($3,$6,yylineno);
                                     }
         | IF '(' expr ')' THEN block ELSE block { 
                                    $$ = create_if_else_node($3,$6,$8,yylineno); }

         | WHILE '(' expr ')' block { $$ = create_while_node($3,$5,yylineno); }
         | ';' { $$ = create_empty_node(yylineno); }
         | block { $$ = $1; }
        ;

method_call: ID '(' expr_params ')' {
                Attributes* info = lookup_in_global_level($1);
                if(info == NULL || info->class_type != CLASS_DECL_FUNCTION)
                    yyerror("Method %s not declared", $1);
                if(info->parameter_list->length  != count_params){
                    printf("CountParams: %d",count_params);
                    printf("\nst_length: %d",info->parameter_list->length);
                    yyerror("Error with the params on: %s", $1);
                }
                count_params = 0;
                $$ = create_call_func_node(info,$3,yylineno);
                }
           | ID '(' ')' { 
                Attributes* info = lookup_in_global_level($1);
                if(info == NULL || info->class_type != CLASS_DECL_FUNCTION)
                    yyerror("Method %s not declared", $1);
                $$ = create_call_func_node(info,NULL,yylineno);
            }
           ;




expr_params: expr{count_params++;} ',' expr_params { $$ = create_list_call_node($1,$4); }
            | expr { $$ = create_list_call_node($1,NULL); 
                    count_params++;}
            ;

expr: valor { $$ = $1; }
    | ID   { 
               Attributes* info = lookup_in_all_levels($1);
               if (info == NULL)
                    yyerror("Identifier %s not declared", $1);
               else
                  $$ = create_ast_node(info,NULL,NULL);  
             }
    | expr '+' expr
            {
               Attributes* attr = create_op_attributes(TYPE_INT, "+", yylineno, CLASS_ADD);
               $$ = create_ast_node(attr, $1, $3); 
            } 
    | expr '*' expr 
            { Attributes* attr = create_op_attributes(TYPE_INT, "*",yylineno, CLASS_MUL);
              $$ = create_ast_node(attr, $1, $3);           
            }
    | '(' expr ')'
        {
            $$ = $2;
        }
    | expr OR expr
            {
                Attributes* attr = create_op_attributes(TYPE_BOOL,"||",yylineno,CLASS_OR);
                $$ = create_ast_node(attr, $1, $3);
            } 
    | expr AND expr 
            {
                Attributes* attr = create_op_attributes(TYPE_BOOL,"&&",yylineno,CLASS_AND);
                $$ = create_ast_node(attr, $1, $3);
            }
    | method_call {
        $$ = $1;
    }
    | TMENOS expr %prec TMINUS
    {
                Attributes* attr = create_op_attributes(TYPE_INT,"-",yylineno,CLASS_MINUS);
                $$ = create_ast_node(attr, $2, NULL);   
    } 
    | '!' expr %prec NOT
            {
                Attributes* attr = create_op_attributes(TYPE_BOOL,"!",yylineno,CLASS_NOT);
                $$ = create_ast_node(attr, $2, NULL);
            }
    | expr '<' expr
            {
                Attributes* attr = create_op_attributes(TYPE_BOOL,"<",yylineno,CLASS_LESS);
                $$ = create_ast_node(attr, $1, $3);
            } 
    | expr '>' expr 
            {
                Attributes* attr = create_op_attributes(TYPE_BOOL,">",yylineno,CLASS_GREATER);
                $$ = create_ast_node(attr, $1, $3);
            }
    | expr EQUALS expr 
            {
                Attributes* attr = create_op_attributes(TYPE_BOOL,"==",yylineno,CLASS_EQUALS);
                $$ = create_ast_node(attr, $1, $3);
            }
    | expr '-' expr 
            {
                Attributes* attr = create_op_attributes(TYPE_INT,"-",yylineno,CLASS_SUB);
                $$ = create_ast_node(attr, $1, $3);
            }
    | expr '/' expr 
            {
                Attributes* attr = create_op_attributes(TYPE_INT,"/",yylineno,CLASS_DIV);
                $$ = create_ast_node(attr, $1, $3);
            }
    | expr '%' expr 
            {
                Attributes* attr = create_op_attributes(TYPE_INT,"%",yylineno,CLASS_MOD);
                $$ = create_ast_node(attr, $1, $3);
            }
    ;

type: TINT { $$ = TYPE_INT; }
    | TBOOL { $$ = TYPE_BOOL; }
    ;

valor: INT { $$ = create_int_node($1,yylineno); }
      | BOOL { $$ = create_bool_node($1,yylineno); }
    ;
%%
