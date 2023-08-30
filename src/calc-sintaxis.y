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

         printf("Programa:\n");
         //int res = evaluate_ast(root);
         print_ast(root);
     }
    | decl 
    { 
        $$ = $1;
        root = $$;  
        printf("Programa2:\n");
         //int res = evaluate_ast(root);

    }
    | sentence_list 
    { 
        $$ = $1;
        root = $$; 
        printf("Programa:\n");
         //int res = evaluate_ast(root);

    }
    ;

    
decl: type ID '=' expr ';' decl  
     { 
         ASTNode* a = create_single_decl_node($1, create_id_node($2,0), $4,0);
         $$ = create_list_decl_node(a, $6); 
     }
     | type ID '=' expr ';'  
     { 
         $$ = create_single_decl_node($1, create_id_node($2,0), $4,0); 
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
             ASTNode* node_id  = create_id_node($1, 0);
             $$ = create_assign_node(node_id, $3,0);
         }
         | RETURN expr ';' 
         { 
             $$ = create_return_node($2,0); 
         }
    ;

expr: valor 
     { 
         $$ = $1;
     }              

    | ID  
     { 
         $$ = create_id_node($1, 0);  
     }

    | expr '+' expr  
     { 
         Attributes* attr = create_op_attributes(TYPE_INT, '+', 0, CLASS_OPERATION);
         $$ = create_ast_node(attr, $1, $3);
     }

    | expr '*' expr  
     { 
         Attributes* attr = create_op_attributes(TYPE_INT, '*',0, CLASS_OPERATION);
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


valor : INT { $$ = create_int_node($1, 1); }
       | BOOL { $$ = create_bool_node($1, 1);}
    ;
 
%%
