
#include "list.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char nombre[50];
    int edad;
    char sintoma[100];
    int prioridad; //prioridad del 1 = baja, 2 = media, 3 = alta
    
} paciente;


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
      list_pushBack(pacientes, nuevo);
  }

  void asignar_prioridad(List *pacientes)
{
    printf("Asignar prioridad a paciente\n");
    // Mostrar la lista de pacientes  
    printf("Lista de pacientes por orden de llegada:\n");
    int indice = 1;
    // Mostrar elementos (recorrido desde el principio)
    for (paciente *paciente = list_first(pacientes); paciente != NULL; paciente = list_next(pacientes))
      //osdasdasdasasdasdasdasd
      {
        printf("Nombre: %s, Edad: %d, Prioridad: %d, indice: %d \n", paciente->nombre, paciente->edad, paciente->prioridad, indice);
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
    printf("Seleccione una opción: ");
    scanf("%d", &paciente_seleccionado->prioridad);
    
}

void mostrar_lista_pacientes(List *pacientes) {
  // Mostrar pacientes en la cola de espera
  printf("Pacientes en espera: \n");
  // Aquí implementarías la lógica para recorrer y mostrar los pacientes
  //pacientes = ordenar_por_prioridad(pacientes);
  for (paciente *paciente = list_first(pacientes); paciente != NULL; paciente = list_next(pacientes))
  {
    printf("Nombre: %s, Edad: %d, Prioridad: %d \n", paciente->nombre, paciente->edad, paciente->prioridad);
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
      // Lógica para atender al siguiente paciente
      break;
    case '5':
      // Lógica para mostrar pacientes por prioridad
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
