
1. **Implementación del Stack para la Tabla de Símbolos**:
    - [ ] Diseñar la estructura de datos para la Tabla de Símbolos.
    - [ ] Implementar operaciones básicas para el stack: PUSH, POP, PEEK.
    - [ ] Implementar la función de búsqueda en el stack (recorrido sin popear).

2. **Modificación del Parser de Bison**:
    - [ ] Integrar la Tabla de Símbolos en el parser de Bison.
    - [ ] Implementar el inicio y cierre de ámbitos (push y pop en el stack) en las reglas pertinentes del parser.
    - [ ] Añadir el chequeo semántico para garantizar que las variables y funciones se utilicen correctamente (ej. verificación de declaraciones y usos adecuados).

3. **Chequeo de Tipos**:
    - [ ] Extender el sistema actual de chequeo de tipos, si es que ya hay uno implementado.
    - [ ] Implementar reglas de promoción y conversión de tipos, si es necesario.
    - [ ] Añadir verificaciones para garantizar operaciones válidas entre diferentes tipos.

4. **Modificación del Árbol de Sintaxis Abstracta (AST)**:
    - [ ] Rediseñar la estructura de nodo del AST para soportar tres hijos.
    - [ ] Actualizar las funciones de creación y manipulación de nodos del AST para adaptarse al nuevo diseño.
    - [ ] Modificar las reglas en Bison donde se construye el AST para que utilicen la nueva estructura de tres hijos.

5. ** STACK **
    - [ ] print the stack
    - [ ] añadir el comentario //
    
6- **Parser**
    - [ ] method_decl modificar el look_and_hook para recibir también el tipo.