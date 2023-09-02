%{
#include <stdlib.h>
#include <stdio.h>
#include "symbol_table.h"
#include "ast.h"
ASTNode* root = NULL;
SymbolTable* table = NULL;   
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
%type <node> declarations
%type <type_val> type
    
%left '+' TMENOS 
%left '*'

%%

init: {
    table = malloc(sizeof(SymbolTable));
    table->head = NULL;
    }prog
    ;
prog:
 declarations sentence_list 
     {
         $$ = create_program_node($1, $2); 
         root = $$; 
         check_types(root,table);
         eval(root,table);
          
         generate_dot_file(root, "ast.dot");
     }

    ;

declarations : decl declarations 
             { 
                 $$ = create_list_decl_node($1, $2); 
             }
             | decl 
             { 
                 $$ = $1; 
             }
    ;

decl: type ID '=' expr ';'
     { 
         Attributes* info = lookup_symbol(table, $2);
         if(info != NULL){
             printf("Error: variable %s already declared\n", $2);
             exit(1);
         }
         ASTNode* id = create_id_node($2,yylineno);
         insert_symbol(table, id->info);
         printf("Inserting symbol %s\n", id->info->tag);
         print_symbol_table(table);
         $$ = create_single_decl_node($1, id, $4,yylineno);
         
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
            Attributes* info = lookup_symbol(table,$1);
            if(info == NULL){
                printf("Error variableasdasdsa %s undeclared",$1);
                exit(1);
            }

            ASTNode* node_id =  create_ast_node(info, NULL, NULL);
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
        printf("Estoy en expr: valor ID: ");
        print_symbol_table(table);

        Attributes* info = lookup_symbol(table, $1);
        if (info == NULL){
            printf("Error: variaasdasdklfasjflkasjflkble %s undeclared\n", $1);
            exit(1);
        }

        $$ = create_ast_node(info,NULL,NULL);  
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
