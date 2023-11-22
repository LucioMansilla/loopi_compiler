# Compilador para el Lenguaje LP

Este proyecto consiste en un compilador desarrollado en C como trabajo práctico para la materia "Taller de Diseño de Software". El compilador toma como entrada programas escritos en el Lenguaje LP y genera codigo ensamblador para la arquitectura x86-64.

## Estructura del Proyecto

El proyecto tiene la siguiente estructura de carpetas:

- **src/**: Contiene el codigo fuente del compilador dividido por modulos
  - **backend/**: Generación de codigo intermedio y assembly.
  - **error-handling/**: Manejador de errores
  - **frontend/**: Analisis lexico, sintactico y semantico
  - **structures/**: Estructuras de datos utilizadas
- **tests/**: Suite de pruebas unitarias
  - **accept/**: Casos validos que debe aceptar
  - **reject/**: Casos invalidos que debe rechazar
- **build.sh**: Script para construir el compilador
- **test.sh**: Script para ejecutar la test suite.
- **loopi.sh**: Script para compilar, linkear y ejecutar programas .lp
- **report/**: Documentación y reporte del proyecto

## Dependencias

Para construir y ejecutar el compilador se requiere:

- [CMake >= 3.10](https://cmake.org/)
- Compilador C (Recomendado GCC)
- En algunos casos g++

## Compilación y Ejecución

### Para construir el compilador ejecutar:
```bash
./build.sh
```
Esto generará el ejecutable **Compiler** en la carpeta **build/** que podrá ser utilizado para compilar programas .lp


### Para ejecutar todas las pruebas:
```bash
./test.sh
```

Cada caso de prueba será informado por la salida estandar stderr.

### Para compilar y ejecutar un programa .lp:
```bash
./loopi.sh ruta/al/programa.lp
```
Por ejemplo para ejecutar el programa **tests/accept/test_fib.lp**:
```bash
./loopi.sh tests/accept/test_fib.lp
```

## Documentación

En la carpeta **report/** se encuentra un informe detallado del desarrollo del proyecto, configuraciones, toma de decisiones relevantes y limitaciones.

## Autores

- Brenda Dichiara
- Lucio Mansilla