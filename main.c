#include "tdas/list.h" // Incluye la definición de la lista enlazada
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char nombre[50];
    int edad;
    char sintoma[100];
    int prioridad;
    int id;
} paciente; // Definición de la estructura paciente

// Función para limpiar la pantalla
void limpiarPantalla() { 
    system("clear"); // Limpia la pantalla
}

// Función para esperar a que el usuario presione una tecla antes de continuar
void presioneTeclaParaContinuar() {
    puts("Presione una tecla para continuar...");
    getchar(); // Consume el '\n' del buffer de entrada
    getchar(); // Espera a que el usuario presione una tecla
}

// Menú principal
void mostrarMenuPrincipal() {
    limpiarPantalla();
    puts("========================================");
    puts("     Sistema de Gestión de Hospitales");
    puts("========================================");

    puts("1) Registrar paciente");
    puts("2) Asignar prioridad a paciente");
    puts("3) Mostrar lista de espera");
    puts("4) Atender al siguiente paciente");
    puts("5) Mostrar pacientes por prioridad");
    puts("6) Salir");
}

// Función para registrar un nuevo paciente
void registrar_paciente(List *lista, size_t contador) {
    paciente *nuevo = (paciente *)malloc(sizeof(paciente)); // Asigna memoria para el nuevo paciente
    if (nuevo == NULL)
        return; // Retorna si no se pudo asignar memoria

    limpiarPantalla();
    printf("Ingrese el nombre del paciente: ");
    scanf(" %[^\n]", nuevo->nombre); // Lee el nombre del paciente

    limpiarPantalla();
    printf("Ingrese la edad del paciente: ");
    scanf("%d", &nuevo->edad); // Lee la edad del paciente

    limpiarPantalla();
    printf("Ingrese el/los síntoma(s) del paciente: ");
    scanf(" %[^\n]", nuevo->sintoma); // Lee los síntomas del paciente

    nuevo->prioridad = 1; // Asigna prioridad por defecto
    nuevo->id = contador; // Asigna un identificador único
    contador++; // Incrementa el contador de pacientes
    list_pushBack(lista, nuevo); // Agrega el paciente a la lista
}

// Función para mostrar la lista de pacientes en espera
void mostrar_lista_pacientes(List *lista) {
    limpiarPantalla();
    puts("========================================");
    puts("NOMBRE - EDAD - SÍNTOMAS");
    puts("========================================");
    // Itera sobre la lista de pacientes y los muestra en la pantalla
    for (paciente *paciente = list_first(lista); paciente != NULL; paciente = list_next(lista)) {
        printf("  %s  -  %d  -  %s  \n", paciente->nombre, paciente->edad, paciente->sintoma);
    }
    puts("========================================");
}

// Función para comparar la prioridad de dos pacientes
int compararPrioridad(void *data1, void *data2) {
    paciente *ptr1 = (paciente *)data1;
    paciente *ptr2 = (paciente *)data2;
    if (ptr1->prioridad > ptr2->prioridad) {
        return 1;
    } else if (ptr1->prioridad < ptr2->prioridad) {
        return 0;
    } else {
        // Si las prioridades son iguales, compara por ID
        if (ptr1->id < ptr2->id) {
            return 1;
        } else {
            return 0;
        }
    }
}

// Función para buscar un paciente por nombre y asignarle una prioridad
void buscar_paciente(List *lista, char *nombre) {
    limpiarPantalla();
    int contador = 0;
    // Itera sobre la lista de pacientes
    for (paciente *paciente = list_first(lista); paciente != NULL; paciente = list_next(lista)) {
        if (strcmp(paciente->nombre, nombre) == 0) { // Compara los nombres de los pacientes
            contador++;
            printf("Ingrese la prioridad del paciente (1-3): ");
            scanf("%d", &paciente->prioridad); // Lee la prioridad ingresada por el usuario
            list_popCurrent(lista); // Elimina el paciente de la lista
            list_sortedInsert(lista, paciente, compararPrioridad); // Inserta el paciente en la lista ordenada por prioridad
            break;
        }
    }
    if (contador == 0) {
        puts("Paciente no encontrado"); // Muestra un mensaje si el paciente no se encuentra en la lista
    }
}

// Función para registrar la prioridad de un paciente existente
void registrar_prioridad(List *lista) {
    limpiarPantalla();
    printf("Ingrese el nombre del paciente: ");
    char nombre[50];
    scanf(" %[^\n]", nombre); // Lee el nombre del paciente ingresado por el usuario
    buscar_paciente(lista, nombre); // Busca al paciente y asigna la prioridad
}

// Función para atender al próximo paciente en la lista
void atender_paciente(List *lista) {
    limpiarPantalla();
    if (list_first(lista) == NULL) {
        puts("No hay pacientes en la lista"); // Muestra un mensaje si no hay pacientes en la lista
    } else {
        paciente *paciente = list_popFront(lista); // Extrae al próximo paciente de la lista
        printf("Nombre: %s\n", paciente->nombre);
        printf("Edad: %d\n", paciente->edad);
        printf("Síntomas: %s\n", paciente->sintoma);
        free(paciente); // Libera la memoria del paciente atendido
    }
}

// Función para mostrar la lista de pacientes con una prioridad específica
void mostrar_lista_prioridad(List *lista) {
    limpiarPantalla();
    int contador = 0;
    int prioridadVer;
    printf("Ingrese la prioridad a mostrar (1-3): ");
    scanf("%d", &prioridadVer); // Lee la prioridad ingresada por el usuario
    limpiarPantalla();

    puts("========================================");
    puts("NOMBRE - EDAD - SÍNTOMAS");
    puts("========================================");

    // Itera sobre la lista de pacientes
    for (paciente *paciente = list_first(lista); paciente != NULL; paciente = list_next(lista)) {
        if (paciente->prioridad == prioridadVer) { // Compara la prioridad del paciente con la prioridad especificada
            contador++;
            printf("  %s  -  %d  -  %s  \n", paciente->nombre, paciente->edad, paciente->sintoma);
        }
    }
    if (contador == 0) {
        limpiarPantalla();
        puts("No hay pacientes con esa prioridad"); // Muestra un mensaje si no hay pacientes con la prioridad especificada
    }
}

int main() {
    char opcion;
    size_t contador = 0;
    List *pacientes = list_create(); // Crea una lista para gestionar los pacientes

    do {
        mostrarMenuPrincipal(); // Muestra el menú principal
        printf("Ingrese su opción: ");
        scanf(" %c", &opcion); // Lee la opción ingresada por el usuario

        switch (opcion) {
            case '1':
                registrar_paciente(pacientes, contador); // Registra un nuevo paciente
                break;
            case '2':
                registrar_prioridad(pacientes); // Asigna prioridad a un paciente existente
                break;
            case '3':
                mostrar_lista_pacientes(pacientes); // Muestra la lista de pacientes en espera
                break;
            case '4':
                atender_paciente(pacientes); // Atiende al próximo paciente en la lista
                break;
            case '5':
                mostrar_lista_prioridad(pacientes); // Muestra pacientes por prioridad
                break;
            case '6':
                limpiarPantalla();
                puts("Saliendo del sistema de gestión hospitalaria...");
                break;
            default:
                puts("Opción no válida. Por favor, intente de nuevo."); // Muestra un mensaje si la opción ingresada no es válida
        }
        presioneTeclaParaContinuar(); // Espera a que el usuario presione una tecla antes de continuar

    } while (opcion != '6');

    // Liberar recursos, si es necesario
    list_clean(pacientes);

    return 0;
}
