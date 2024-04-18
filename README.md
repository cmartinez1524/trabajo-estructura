
# trabajo-estructura

Para ejecutar el main primero debemos compilar (en la carpeta raíz)
gcc tdas/*.c main.c -Wno-unused-result -o main
Y luego ejecutar:
./main

Un detalle es que el ultimo de la lista enlazada es el primero en ser atendido no al reves osea si aplico el comando de list.first estamos accediendo al ultimo en realidad

Se incluyen las bibliotecas necesarias y se define la estructura paciente, que representa la información de un paciente, incluyendo su nombre, edad, síntoma y prioridad.

Se definen funciones auxiliares limpiarPantalla y presioneTeclaParaContinuar para mejorar la presentación y la interacción con el usuario.

La función mostrarMenuPrincipal muestra el menú de opciones disponibles en el sistema.

registrar_paciente permite al usuario registrar un nuevo paciente, ingresando su nombre, edad, síntoma y asignando automáticamente una prioridad predeterminada.

asignar_prioridad permite al usuario asignar una prioridad específica a un paciente seleccionado de la lista.

La función ordenar_por_prioridad se encarga de ordenar la lista de pacientes por prioridad utilizando el algoritmo de bubble sort. Esto garantiza que los pacientes con prioridad más alta se atiendan primero.

mostrar_lista_pacientes muestra la lista de pacientes en espera, mostrando su nombre, edad y prioridad.

atender_siguiente_paciente atiende al siguiente paciente en la lista de espera, mostrando su información y liberando la memoria correspondiente.

mostrar_pacientes_por_prioridad permite al usuario ver todos los pacientes que tienen una prioridad específica.

En la función main, se crea una lista de pacientes y se ejecuta un bucle para mostrar el menú principal, leer la opción del usuario y ejecutar la acción correspondiente según la opción seleccionada.

El programa continúa ejecutándose hasta que el usuario elige salir (opción 6), momento en el que se liberan los recursos y el programa finaliza.

