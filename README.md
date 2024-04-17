
# trabajo-estructura

En este *repl* puedes encontrar varios ejemplos que te pueden ayudar con las tareas de estructura.

## Código de Ejemplo (main)
Para ejecutar el main primero debemos compilar (en la carpeta raíz)

gcc tdas/*.c main.c -Wno-unused-result -o main


Y luego ejecutar:

./main


TDAs
En la carpeta `tdas` se encuentran implementados distintos TDAs que puedes utilizar (lista, pila, cola, cola con prioridad y mapas). 

Las implementaciones no son las más eficientes (todas usan como estructura de datos una **lista enlazada**), por lo que puedes reemplazarlas por las que has realizado en los labs.

Otros códigos (en carpeta examples)
Para ejecutar los distintos ejemplos que hay en la carpeta `examples`, primero debes compilarlos. Si estamos en la carpeta raíz:

gcc tdas/*.c examples/example2_menu.c -Wno-unused-result -o example

Y luego ejecutarlos:

./example
