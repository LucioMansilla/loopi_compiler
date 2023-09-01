%{
#include <stdlib.h>
#include <stdio.h>
#include "symbol_table.h"
#include "ast.h"
ASTNode* root = NULL;
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
%token  TINT
%token  TBOOL
%token RETURN
%type <node> expr
%type <node> valor
%type <node> decl
%type <node> sentence_list
%type <node> sentence
%type <node> prog
%type <type_val> type
    
%left '+' TMENOS 
%left '*'

%%
 
prog: decl sentence_list 
     { 
         $$ = create_program_node($1, $2); 
         root = $$; 
         SymbolTable* table = malloc(sizeof(SymbolTable));
         table->head = NULL;
         check_types(root,table);
         //eval(root,table);
          
         generate_dot_file(root, "ast.dot");
     }
    | decl 
    { 
        $$ = $1;
        root = $$;  
    }
    | sentence_list 
    { 
        $$ = $1;
        root = $$; 
    }
    ;

    
decl: type ID '=' expr ';' decl  
     { 
         ASTNode* a = create_single_decl_node($1, create_id_node($2,yylineno), $4,yylineno);
         $$ = create_list_decl_node(a, $6); 
     }
     | type ID '=' expr ';'  
     { 
         $$ = create_single_decl_node($1, create_id_node($2,yylineno), $4, yylineno); 
     }
    ;


sentence_list: sentence sentence_list 
              { 
                  $$ = create_sentence_list_node($1, $2);
              }
              | sentence 
              { 
                  $$ = $1 ;
              }
    ;

sentence: ID '=' expr ';' 
         { 
             ASTNode* node_id  = create_id_node($1, yylineno);
             $$ = create_assign_node(node_id, $3, yylineno);
         }
         | RETURN expr ';' 
         { 
             $$ = create_return_node($2,yylineno); 
         }
    ;

expr: valor 
     { 
         $$ = $1;
     }              

    | ID  
     { 
         $$ = create_id_node($1, yylineno);  
     }

    | expr '+' expr  
     { 
         Attributes* attr = create_op_attributes(NOT_TYPE, '+', 0, CLASS_OPERATION);
         $$ = create_ast_node(attr, $1, $3);
     }

    | expr '*' expr  
     { 
         Attributes* attr = create_op_attributes(NOT_TYPE, '*',0, CLASS_OPERATION);
         $$ = create_ast_node(attr, $1, $3);
     }

    | '(' expr ')'  
     { 
         $$ = $2;
     }
;


type: TINT { $$ = TYPE_INT; }
    | TBOOL { $$ = TYPE_BOOL; }
    ;


valor : INT { $$ = create_int_node($1, yylineno); }
       | BOOL { $$ = create_bool_node($1, yylineno);}
    ;
 
%%
