# Taller de Diseño de Software  

Este proyecto es un 'compilador' desarrollado como parte de la materia 'Taller de Diseño de Software'. 



## Environment 

Dependencies:

- [CMake >= 3.10](https://cmake.org/)

- Any C Compiler (We like [GCC](https://gcc.gnu.org/))

- In some cases you may need to install [g++](https://gcc.gnu.org/)

## Estructura del Proyecto

El proyecto se estructura de la siguiente manera:

- `src/`: Código fuente del compilador, dividido en módulos:
  - `backend/`: Contiene la generación de código ensamblador e interpretación.
  - `error-handling/`: Manejo de errores y mensajes de error.
  - `frontend/`: Análisis sintáctico, léxico y semántico.
  - `structures/`: Estructuras de datos utilizadas en el compilador.
- `tests/`: Pruebas divididas en aceptación y rechazo, con ejemplos variados.
- `run_assembly.sh`: Script para ejecutar y compilar un archivo específico.
- `test.sh`: Script para realizar pruebas automatizadas del compilador.
- `build.sh`: Script para construir el proyecto.
- `README.md`: Este archivo.
- `tasks.md`: Tareas pendientes y notas del proyecto.
- `test_passed.txt`: Mensaje de éxito para las pruebas.

## Configuración del Entorno

Para construir y ejecutar el compilador, se utilizan los siguientes scripts:

```bash
chmod +x build.sh test.sh run_assembly.sh
./build.sh
./test.sh
