
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
    - [ ] method_decl modificar el lookup_in_current_level para recibir también el tipo.

--------------------------------------------------------------------------------------

7- **Para después**
    - [x] Arreglar la precedencia de los operadores unitarios con %prec.
        - [ ] Testear que funcione!!.
    - [x] Cambiar los nombres de los métodos en stack.h
    - [x] Borrar create func attributes
    - [x] Method_call actualmente usamos lookup_in_all_levels para buscar en el global, pero es ineficiente, programar un buscador de nivel 0.
        - [ ] Ya programamos el buscador pero el mismo no es el "más eficiente", se podría mejorar utilizando una lista doblemente enlazada y tener una referencia al primer elemento del stack (lvl 0).
        - [x] testear que funcione.
    
    - [!!!] Method_call debatir quien debe manejar la lógica de verificar el tipo del identificador buscado. 
    
    - [!!!] Method decl fijarse que: 
            type ID param {
        if(lookup_in_current_level($2) != NULL) 
            yyerror("Identifier %s already declared", $2);
        Attributes* info = create_attributes($1,0,$2,yylineno,CLASS_DECL_FUNCTION);
        add_symbol_to_current_level(info);
        insert_level($3); //push the params and insert into a new level.
    } 
     estamos usando create_attributes para crear el "info" y luego usamos create_decl_function más abajo pero solo llama a create_ast.. quizás podamos usar create_ast directamente..
        -Por ahora tomamos la convención de dejar todo como está..


    - [ ] En parser.y declaramos una variable global count_params para contar la cantidad de parámetros que tiene un método, pero capaz existe una mejor forma de realizarlo.
     
    - [ ] Analizar en el no terminal "expr" en la regla "method_call" del mismo si colocar la lógica del method_call ahí o hacerlo en la propia definicion del method_call.
    

    - [x] Analizar todo el method_decl ya que esta porción de código se repite:
           if(lookup_in_current_level($2) != NULL) 
            yyerror("Identifier %s already declared", $2);
        Attributes* info = create_func_attributes($1,$3,$2,yylineno);
        add_symbol_to_current_level(info);

        A lo sumo cambia el primer parámetro que se envia a create_func_attributes, pero el resto es igual.
        Una primera aproximación es en el stack.h crear un función llamada "insert_function" que reciba como parámetros el tipo, la cantidad de parámetros y el nombre del método y un flag que indique si es externo o no. 
      Resuelto: al final usamos add_func_to_st..


    




