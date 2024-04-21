#include "tdas/list.h" // Incluye la definición de la lista enlazada
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estructura para representar a un paciente
typedef struct {
    char nombre[50];
    int edad;
    char sintoma[100];
    int prioridad;
    int id;
} paciente;

// Limpia la pantalla
void limpiarPantalla() { 
    system("clear"); 
}

// Espera a que el usuario presione una tecla antes de continuar
void presioneTeclaParaContinuar() {
    puts("\nPresione cualquier tecla para continuar...");
    getchar(); // Consume el '\n' del buffer de entrada
    getchar(); // Espera a que el usuario presione una tecla
}

// Menú principal del sistema
void mostrarMenuPrincipal() {
    limpiarPantalla();
    puts("========================================");
    puts("    Sistema de Gestión Hospitalaria");
    puts("========================================");
    puts("1) Registrar paciente");
    puts("2) Asignar prioridad a paciente");
    puts("3) Mostrar lista de espera");
    puts("4) Atender al siguiente paciente");
    puts("5) Mostrar pacientes por prioridad");
    puts("6) Salir");
}

// Registra un nuevo paciente
void registrar_paciente(List *lista, size_t *contador) {
    paciente *nuevo = (paciente *)malloc(sizeof(paciente)); 
    if (nuevo == NULL) {
        puts("Error al asignar memoria. Intente nuevamente.");
        return;
    }

    limpiarPantalla();
    printf("Ingrese el nombre del paciente: ");
    scanf(" %[^\n]", nuevo->nombre);

    limpiarPantalla();
    printf("Ingrese la edad del paciente: ");
    scanf("%d", &nuevo->edad);

    limpiarPantalla();
    printf("Ingrese el/los síntoma(s) del paciente: ");
    scanf(" %[^\n]", nuevo->sintoma);

    nuevo->prioridad = 1; // Prioridad por defecto
    nuevo->id = *contador; 
    (*contador)++; 
    list_pushBack(lista, nuevo);

    puts("\nPaciente registrado exitosamente!");
}

// Muestra la lista de pacientes en espera
void mostrar_lista_pacientes(List *lista) {
    limpiarPantalla();
    puts("========================================");
    puts("    Lista de Pacientes en Espera");
    puts("========================================");
    if (list_first(lista) == NULL) {
        puts("No hay pacientes en la lista de espera.");
    } else {
        for (paciente *paciente = list_first(lista); paciente != NULL; paciente = list_next(lista)) {
            printf("%s, Edad: %d, Síntomas: %s\n", paciente->nombre, paciente->edad, paciente->sintoma);
        }
    }
    puts("========================================");
}

// Compara la prioridad entre dos pacientes
int compararPrioridad(void *data1, void *data2) {
    paciente *ptr1 = (paciente *)data1;
    paciente *ptr2 = (paciente *)data2;

    if (ptr1->prioridad > ptr2->prioridad) {
        return 1;
    } else if (ptr1->prioridad < ptr2->prioridad) {
        return 0;
    } else {
        return (ptr1->id < ptr2->id) ? 1 : 0;
    }
}

// Busca un paciente por nombre y le asigna prioridad
void buscar_paciente(List *lista, const char *nombre) {
    int encontrado = 0;
    for (paciente *paciente = list_first(lista); paciente != NULL; paciente = list_next(lista)) {
        if (strcmp(paciente->nombre, nombre) == 0) {
            printf("Ingrese la prioridad del paciente (1-3): ");
            scanf("%d", &paciente->prioridad);
            list_popCurrent(lista); // Elimina el paciente de la lista actual
            list_sortedInsert(lista, paciente, compararPrioridad); // Inserta el paciente en la lista ordenada
            encontrado = 1;
            puts("Prioridad asignada correctamente.");
            break;
        }
    }

    if (!encontrado) {
        puts("Paciente no encontrado.");
    }
}

// Asigna prioridad a un paciente existente
void registrar_prioridad(List *lista) {
    limpiarPantalla();
    printf("Ingrese el nombre del paciente: ");
    char nombre[50];
    scanf(" %[^\n]", nombre);

    buscar_paciente(lista, nombre);
}

// Atender al siguiente paciente en la lista
void atender_paciente(List *lista) {
    limpiarPantalla();

    if (list_first(lista) == NULL) {
        puts("No hay pacientes en la lista de espera.");
    } else {
        paciente *paciente = list_popFront(lista);
        printf("Nombre: %s\n", paciente->nombre);
        printf("Edad: %d\n", paciente->edad);
        printf("Síntomas: %s\n", paciente->sintoma);

        free(paciente); // Libera la memoria después de atender al paciente
        puts("Paciente atendido.");
    }
}

// Muestra la lista de pacientes con una prioridad específica
void mostrar_lista_prioridad(List *lista) {
    limpiarPantalla();

    printf("Ingrese la prioridad a mostrar (1-3): ");
    int prioridad;
    scanf("%d", &prioridad);

    puts("========================================");
    puts("    Lista de Pacientes por Prioridad");
    puts("========================================");

    int contador = 0;
    for (paciente *paciente = list_first(lista); paciente != NULL; paciente = list_next(lista)) {
        if (paciente->prioridad == prioridad) {
            printf("%s, Edad: %d, Síntomas: %s\n", paciente->nombre, paciente->edad, paciente->sintoma);
            contador++;
        }
    }

    if (contador == 0) {
        puts("No hay pacientes con esta prioridad.");
    }
}

// Función principal del programa
int main() {
    char opcion;
    size_t contador = 0;
    List *pacientes = list_create(); // Lista para gestionar a los pacientes

    do {
        mostrarMenuPrincipal(); // Muestra el menú principal del sistema
        printf("Ingrese su opción: ");
        scanf(" %c", &opcion);

        switch (opcion) {
            case '1': // Registrar paciente
                registrar_paciente(pacientes, &contador);
                break;
            case '2': // Asignar prioridad a paciente
                registrar_prioridad(pacientes);
                break;
            case '3': // Mostrar lista de espera
                mostrar_lista_pacientes(pacientes);
                break;
            case '4': // Atender al siguiente paciente
                atender_paciente(pacientes);
                break;
            case '5': // Mostrar pacientes por prioridad
                mostrar_lista_prioridad(pacientes);
                break;
            case '6': // Salir del sistema
                limpiarPantalla();
                puts("Saliendo del sistema de gestión hospitalaria...");
                break;
            default: // Opción no válida
                puts("Opción no válida. Por favor, intente de nuevo.");
        }

        presioneTeclaParaContinuar(); // Espera a que el usuario presione una tecla antes de continuar

    } while (opcion != '6'); // Repite hasta que el usuario decida salir

    // Libera recursos antes de salir
    list_clean(pacientes);

    return 0; // Finaliza el programa
}