
# trabajo-estructura

Para ejecutar el main primero debemos compilar (en la carpeta raíz)

**gcc tdas/*.c main.c -Wno-unused-result -o main**

Y luego ejecutar:

**./main**

Funcionalidades Disponibles:

Registrar Paciente (Opción 1):
Permite registrar un nuevo paciente ingresando su nombre, edad y síntomas.

Asignar Prioridad a Paciente (Opción 2):
Permite asignar una prioridad (1-3) a un paciente registrado.

Mostrar Lista de Espera (Opción 3):
Muestra la lista de todos los pacientes registrados, junto con su nombre, edad y síntomas.

Atender al Siguiente Paciente (Opción 4):
Atiende al próximo paciente en la lista de espera, mostrando su nombre, edad y síntomas.

Mostrar Pacientes por Prioridad (Opción 5):
Permite al usuario especificar una prioridad (1-3) y muestra todos los pacientes con esa prioridad.

Salir del Programa (Opción 6):
Permite salir del sistema de gestión hospitalaria.