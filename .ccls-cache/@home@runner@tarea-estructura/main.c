#include "tdas/list.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char nombre[50];
    int edad;
    char sintoma[100];
    int prioridad; //prioridad del 1 = baja, 2 = media, 3 = alta

} paciente;

void ordenar_por_prioridad(List *pacientes) 
{
    int n = list_size(pacientes);
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            paciente *paciente_actual = (paciente *)list_get(pacientes, j);
            paciente *paciente_siguiente = (paciente *)list_get(pacientes, j + 1);
            if (paciente_actual->prioridad > paciente_siguiente->prioridad) {
                // Intercambiar los pacientes
                paciente temp = *paciente_actual;
                *paciente_actual = *paciente_siguiente;
                *paciente_siguiente = temp;

            }
        }
    }
}

// Función para limpiar la pantalla
void limpiarPantalla() 
{ 
  system("clear");
}

void presioneTeclaParaContinuar() 
{
  puts("Presione una tecla para continuar...");
  getchar(); // Consume el '\n' del buffer de entrada
  getchar(); // Espera a que el usuario presione una tecla
}


// Menú principal
void mostrarMenuPrincipal() {
  limpiarPantalla();
  puts("========================================");
  puts("     Sistema de Gestión Hospitalaria");
  puts("========================================");

  puts("1) Registrar paciente");
  puts("2) Asignar prioridad a paciente");
  puts("3) Mostrar lista de espera");
  puts("4) Atender al siguiente paciente");
  puts("5) Mostrar pacientes por prioridad");
  puts("6) Salir");
}

void registrar_paciente(List *pacientes) {
    printf("Registrar nuevo paciente\n");

    // Crear un nuevo paciente
    paciente *nuevo = (paciente *) malloc(sizeof(paciente));
    if (nuevo == NULL) {
        printf("Error: no se pudo asignar memoria para el nuevo paciente\n");
        return;
    }

    // Solicitar información del paciente al usuario
    printf("Ingrese el nombre del paciente: ");
    scanf("%s", nuevo->nombre);
    printf("Ingrese la edad del paciente: ");
    scanf("%d", &nuevo->edad);
    printf("Ingrese el sintoma del paciente: ");
    scanf("%s", nuevo->sintoma);
    // Asignar prioridad al paciente predeterminada en 1
    nuevo->prioridad = 1;
    printf("Prioridad del paciente: %d\n", nuevo->prioridad);
    // Insertar el nuevo paciente en la lista de pacientes
    list_pushFront(pacientes, nuevo);
    printf("Paciente registrado con éxito\n");
}

void asignar_prioridad(List *pacientes)
{
    printf("Asignar prioridad a paciente\n");
    // Mostrar la lista de pacientes  
    printf("Lista de pacientes por orden de llegada:\n");
    int indice = 1;
    // Mostrar elementos (recorrido desde el principio)
    for (paciente *paciente = list_first(pacientes); paciente != NULL; paciente = list_next(pacientes))
    {
      printf("Nombre: %s, Edad: %d,Sintoma: %s,  Prioridad: %d \n", paciente->nombre, paciente->edad, paciente->sintoma, paciente->prioridad);
        indice++;
    }

    printf("\n");
    // Solicitar al usuario que seleccione un paciente
    printf("Seleccione el índice del paciente que desea asignar prioridad: ");
    scanf("%d", &indice);
    // Verificar si el índice es válido
    if (indice < 1 || indice > list_size(pacientes))
    {
        printf("Error: índice inválido\n");
        return;
    }
    // Obtener el paciente seleccionado
    paciente *paciente_seleccionado = list_get(pacientes, indice - 1);
    // Solicitar al usuario que seleccione la prioridad del paciente
    printf("Seleccione la prioridad del paciente:\n");
    printf("1) Baja\n");
    printf("2) Media\n");
    printf("3) Alta\n");
    printf("Escriba la prioridad que desea asignar: ");
    scanf("%d", &paciente_seleccionado->prioridad);
    ordenar_por_prioridad(pacientes);
}

void mostrar_lista_pacientes(List *pacientes) {
    // Mostrar pacientes en la cola de espera
    printf("Pacientes en espera: \n");
    // Aquí implementarías la lógica para recorrer y mostrar los pacientes
    //pacientes = ordenar_por_prioridad(pacientes);
    for (paciente *paciente = list_first(pacientes); paciente != NULL; paciente = list_next(pacientes))
    {
        printf("Nombre: %s, Edad: %d,Sintoma: %s,  Prioridad: %d \n", paciente->nombre, paciente->edad, paciente->sintoma, paciente->prioridad);
    }
}

void atender_siguiente_paciente(List *pacientes) {
    if (list_size(pacientes) == 0) {
        printf("No hay pacientes en espera.\n");
        return;
    }

    paciente *siguiente = (paciente *)list_popBack(pacientes);
    printf("Atendiendo al siguiente paciente:\n");
  printf("Nombre: %s, Edad: %d,Sintoma: %s,  Prioridad: %d \n", siguiente->nombre, siguiente->edad, siguiente->sintoma, siguiente->prioridad);
    free(siguiente); // Liberar la memoria del paciente atendido
}

void mostrar_pacientes_por_prioridad(List *pacientes) 
{
    int dato;
    printf("Ingrese la prioridad que desea ver (1 = baja, 2 = media, 3 = alta): ");
    scanf("%d", &dato);
    printf("Pacientes con prioridad %d:\n", dato);
    for (int i = 0; i < list_size(pacientes); i++) {
        paciente *paciente = list_get(pacientes, i);
        if (paciente->prioridad == dato) {
            printf("Nombre: %s, Edad: %d, Prioridad: %d \n", paciente->nombre, paciente->edad, paciente->prioridad);
        }
    }
}

int main() {
    char opcion;
    List *pacientes = list_create(); // puedes usar una lista para gestionar los pacientes

    do {
        mostrarMenuPrincipal();
        printf("Ingrese su opción: ");
        scanf(" %c", &opcion); // Nota el espacio antes de %c para consumir el
                               // newline anterior

        switch (opcion) {
        case '1':
            registrar_paciente(pacientes);
            break;
        case '2':
            // Lógica para asignar prioridad
            asignar_prioridad(pacientes);
            break;
        case '3':
            mostrar_lista_pacientes(pacientes);
            break;
        case '4':
            atender_siguiente_paciente(pacientes);
            break;
        case '5':
        //Solicitar al usuario que ingrese la prioridad
            mostrar_pacientes_por_prioridad(pacientes);
            break;

        case '6':
            puts("Saliendo del sistema de gestión hospitalaria...");
            break;
        default:
            puts("Opción no válida. Por favor, intente de nuevo.");
        }
        presioneTeclaParaContinuar();

    } while (opcion != '6');

    // Liberar recursos, si es necesario
    list_clean(pacientes);

    return 0;
}