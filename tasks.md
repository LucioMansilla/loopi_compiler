
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


    - [x] En parser.y declaramos una variable global count_params para contar la cantidad de parámetros que tiene un método, pero capaz existe una mejor forma de realizarlo.
        - [ ] por ahora dijo que esa esta bien.. pensar una mejor.

    - [x] Analizar en el no terminal "expr" en la regla "method_call" del mismo si colocar la lógica del method_call ahí o hacerlo en la propia definicion del method_call.
    

    - [x] Analizar todo el method_decl ya que esta porción de código se repite:
           if(lookup_in_current_level($2) != NULL) 
            yyerror("Identifier %s already declared", $2);
        Attributes* info = create_func_attributes($1,$3,$2,yylineno);
        add_symbol_to_current_level(info);
        
        A lo sumo cambia el primer parámetro que se envia a create_func_attributes, pero el resto es igual.
        Una primera aproximación es en el stack.h crear un función llamada "insert_function" que reciba como parámetros el tipo, la cantidad de parámetros y el nombre del método y un flag que indique si es externo o no. 
      Resuelto: al final usamos add_func_to_st.. 

    - [ ] Analizar method_call por ahora manejamos una lisrta de nodos punto y coma (list_call_node), donde si es unitario no es una lista unitaria(mismo tratamiento que sentence_list y declaration_list).

    - [X] Cambiar el nombre de la función ASTNode* create_decl_func(Attributes* info, ASTNode* body) por create_decl_func_node.

    v: significa que lo revisamos y nos queda pendiente.
    ??: significa que no tenemos ni idea esa nota.

    - [v] Para los extern ver donde crear los nodos. <--

    - [v] Mejorar la funcion generate_dot para mostrar la informacion de los nodos.

    - [??] Mejorar el chequeo de returns..

    - [x] Invertir la lista de parametros formales.

    - [X] Hacer chequeo de la funcion main.
        - [X] Testear que funcione.
        - [v] No hay arrastre de errores para la función main. añadirlo

    - [x] Encapsular logica repetida en el codigo de 3 direcciones (operandos binarios: como mul,div,equals,etc..)
        - Lucio.

    - [v] Hacer testeos para el chequeo de tipos.

    - [ ] mejorar los switchs cases..

    - [P] Ya hicimos el less ( < ) en assembler, preguntarle a pancho si es correcto , de ser así hacer el greater y el equals.

    - [P] al momento de hacer testq lo estamos haciendo sobre el rax, queda averiguar la semántica del testq, si se puede hacer entre dir de memoria.. y si solo se puede hacer entre valor y registro | registro y registro.. en ese caso quizás se puede plantear algo como testq <registro> <memoria.>
    

    - [!P!] Preguntar a profe porque cuando hago subq con negativo tira segmentation fault pero el valor lo tira bien ( 2)   pero cuando hago subq con positivo anda de 10 ! .

        .text
    .globl main
    .type main, @function
main:
    pushq %rbp
    movq %rsp, %rbp
    subq $32, %rsp
    movq $2, -8(%rbp)
    movq $3, %rax
    cmpq $5, %rax
    setl %al
    movzbq %al, %rax
    movq %rax, -16(%rbp)
    testq %rax, %rax
    jz LABEL_1
    movq $0, -24(%rbp)
    movq $1, -24(%rbp)
    jmp LABEL_2
LABEL_1:
    movq $10, -8(%rbp)
LABEL_2:
    movq -8(%rbp) , %rax
    movq %rax, -8(%rbp)
    movq %rax, %rdi
    movq $0, %rsi
    call print
    leave
    ret
    .section .note.GNU-stack,"",@progbits

- [P]          case RETURN_EXPR:
                fprintf(fp, "    movq %d(%%rbp), %%rdi\n", current->res->offset);
                fprintf(fp, "    movq $%d, %%rsi\n", 0);
                fprintf(fp, "    call print\n");
                epilogue(fp);
                break;


                lo que pasa acá es que si return <expr> y expr es una constante, entonces tengo q hacer un if para diferenciar ese caso todo esto es porque el rax hay casos donde esta pisado por ejemplo en el caso del while, si fuera del while la primer sentencia es return <expr> y busca en el rax va a encontrar un 0.. ¿Cómo paso el párametro a la función?... ¿Cómo manejo lo de return expr y return constante? ¿Lo manejo desde 3 direcciones?.

        - [P] !! ver lo del offset de alinear a 16bytes. mostrar el while cuando creas una nueva variable


        -[P] DUDAS EL MAIN PUEDE SER VOID?



Observar el type:
    .text
    .globl f
    .type f, @function
f:
    pushq %rbp
    movq %rsp, %rbp
    subq $128, %rsp
    movq $10, -16(%rbp)
    movq -16(%rbp), %rdi
    movq $0, %rsi
    call print
    leave
    ret
    .section .note.GNU-stack,"",@progbits
    .text
    .globl main
    .type main, @function
main:
    pushq %rbp
    movq %rsp, %rbp
    subq $128, %rsp
    movq $1, -32(%rbp)
    movq $1, -48(%rbp)
    movq $4, -64(%rbp)
LABEL_1:
    movq -32(%rbp), %rax
    cmpq -64(%rbp), %rax
    setl %al
    movzbq %al, %rax
    movq %rax, -80(%rbp)
    testq %rax, %rax
    jz LABEL_2
    movq $0, %rax
    movq -48(%rbp), %rax
    imul -32(%rbp), %rax
    movq %rax, -96(%rbp)
    movq -96(%rbp) , %rax
    movq %rax, -48(%rbp)
    movq -32(%rbp), %rax
    addq $1, %rax
    movq %rax, -112(%rbp)
    movq -112(%rbp) , %rax
    movq %rax, -32(%rbp)
    jmp LABEL_1
LABEL_2:
    call f
    movq -48(%rbp), %rdi
    movq $0, %rsi
    call print
    leave
    ret
    .section .note.GNU-stack,"",@progbits


esta dentro de f, esta bien así???.
Esta reservando 128 para f, cuando cada función deberia tener su propio offset.

En el proyecto dice que las variables deben inicializarse con 0 sin embargo en la gramática si o si te pide que la iguales a una expr. ¿Qué hacemos?.

----------------------------------------------------------------------

- [X] Cambiar call en 3 direcciones para quede:
        call g T1 
        -Notas:

        En Assembler:
        -[] return_expr dividir costante y memoria - falta if 
        -[] Mover el resultado de eax a T1
        -[] Ver en el return como saber el nombre de la funcion que retorna.

- [X] Para los parametros generar el offest en el parser antes de añadir cada parametro a la list_param_formal.

- [X] Cada funcion debe tener su propio offeset, por lo que se debe reniciar en la declaracion de cada funcion.

- [ ] En el codigo de 3 direcciones se debe hacer un
  LOAD_PARAM T1  1
  LOAD_PARAM T2  2
  y luego CALL func 
 
- [ ] El recorrido de los paramteros se hace en el assembler donde tenemos un maximo de 6 parametros (
    mov -16(%%rbp), %%rdi
    mov -24(%%rbp), %%rsi
)

- [ ] Hacer cmpq 0, %rax en vez de testq %rax, %rax

- [ ] Luego del return se debe cortar la ejecucion de la funcion, en assembler hacer leave y ret. Pero siempre al final de la funcion debe estar el epilogo si no se alcanzo el return.

- [ ] AND y OR en assembler que se comporte con la suma y la resta.

- [ ] En el assembler el mayor igual mismo comportamiento que el menor igual, dando vuelta los parametros.

- [ ] Las variables globales se deben inicializar en 0 en el data y para ejecutar su valor moves todo al main para cambiar el valor de la variable otro enfoque mas simple es semanticamente las variables globales solo pueden ser inicializadas con constantes.
