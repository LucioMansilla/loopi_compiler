
1. **Implementación del Stack para la Tabla de Símbolos**:
    - [x] Diseñar la estructura de datos para la Tabla de Símbolos.
    - [x] Implementar operaciones básicas para el stack: PUSH, POP, PEEK.
    - [x] Implementar la función de búsqueda en el stack (recorrido sin popear).

2. **Modificación del Parser de Bison**:
    - [x] Integrar la Tabla de Símbolos en el parser de Bison.
    - [x] Implementar el inicio y cierre de ámbitos (push y pop en el stack) en las reglas pertinentes del parser.

3. **Chequeo de Tipos**:
    - [ ] Añadir verificaciones para garantizar operaciones válidas entre diferentes tipos.

4. **Modificación del Árbol de Sintaxis Abstracta (AST)**:
    - [x] Rediseñar la estructura de nodo del AST para soportar tres hijos.

5. ** STACK **
    - [ ] print the stack
    - [X] añadir el comentario //
    
6- **Parser**
    - [ ] method_decl modificar el look_and_hook para recibir también el tipo.

--------------------------------------------------------------------------------------

7- **Para después**
    - [ ] Arreglar la precedencia de los operadores unitarios con %prec.
    - [ ] Cambiar los nombres de los métodos en stack.h
    - [x] Borrar create func attributes
    - [ ] Method_call actualmente usamos search_symbol para buscar en el global, pero es ineficiente, programar un buscador de nivel 0.
    - [ ] Method_call debatir quien debe manejar la lógica de verificar el tipo del identificador buscado.
    - [ ] Method decl fijarse que: 
            type ID param {
        if(look_and_hook($2) != NULL) 
            yyerror("Identifier %s already declared", $2);
        Attributes* info = create_attributes($1,0,$2,yylineno,CLASS_DECL_FUNCTION);
        insert_symbol_in_stack(info);
        insert_level($3); //push the params and insert into a new level.
    } 
     estamos usando create_attributes para crear el "info" y luego usamos create_decl_function más abajo pero solo llama a create_ast.. quizás podamos usar create_ast directamente..
    - [ ] En parser.y declaramos una variable global count_params para contar la cantidad de parámetros que tiene un método, pero capaz existe una mejor forma de realizarlo.
     
    - [ ] Analizar en el no terminal "expr" en la regla "method_call" del mismo si colocar la lógica del method_call ahí o hacerlo en la propia definicion del method_call.
    


