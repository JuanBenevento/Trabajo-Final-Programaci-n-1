#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "comentarios.h"
#define MAX_COMENTARIO 500
// Variable global para mantener el contador de IDs
int idComentarioCounter = 0;

// Función para inicializar un nuevo comentario
stComentario agregarComentario() {
    stComentario nuevoComentario;
    nuevoComentario.idComentario = ++idComentarioCounter; // Incrementar y asignar el nuevo ID

    printf("Ingrese el ID del libro: ");
    scanf("%d", &nuevoComentario.idLibro);
    getchar(); // Limpiar el buffer del teclado


    do {
        ingresarContraseniaCamuflada(nuevoComentario.password);
        if (!validarPassword(nuevoComentario.password)){
            printf("Contrasenia no valida.");
        }
    } while (!validarPassword(nuevoComentario.password)); // Limpiar el buffer del teclado


    printf("Ingrese el nombre del usuario: ");
    scanf("%s", &nuevoComentario.nombreUsuario);


    printf("Ingrese la descripcion del comentario: ");
    fflush(stdin);
    fgets(nuevoComentario.descripcion, sizeof(nuevoComentario.descripcion), stdin);
    if (nuevoComentario.descripcion[strlen(nuevoComentario.descripcion) - 1] == '\n') {
        nuevoComentario.descripcion[strlen(nuevoComentario.descripcion) - 1] = '\0';
    }


    do {
        printf("Ingrese la valoracion del libro (0-5): ");
        scanf("%d", &nuevoComentario.puntaje);
        getchar(); // Limpiar el buffer del teclado
    } while (nuevoComentario.puntaje < 0 || nuevoComentario.puntaje > 5);

    pedirFecha(nuevoComentario.fechaComentario);

    nuevoComentario.eliminado = 0; // El comentario se marca como activo


    return nuevoComentario;
}

// Funcion para validar la fecha
int esFechaValida(const char *fecha) {
    int dia, mes, anio;

    // Verificar el formato
    if (sscanf(fecha, "%2d-%2d-%4d", &dia, &mes, &anio) != 3) {
        return 0;
    }

    // Verificar los rangos de dia, mes y anio
    if (dia < 1 || dia > 31 || mes < 1 || mes > 12 || anio < 1800 || anio > 3000) {
        return 0;
    }

    // Verificar dias validos segun el mes
    if (mes == 2) { // Febrero
        // Comprobar si es un anio bisiesto
        int esBisiesto = (anio % 4 == 0 && anio % 100 != 0) || (anio % 400 == 0);
        if ((esBisiesto && dia > 29) || (!esBisiesto && dia > 28)) {
            return 0;
        }
    } else if (mes == 4 || mes == 6 || mes == 9 || mes == 11) { // Abril, Junio, Septiembre, Noviembre
        if (dia > 30) {
            return 0;
        }
    }

    return 1;
}

void pedirFecha(char *fecha) {
    int fechaValida = 0;

    while (!fechaValida) {
        printf("Ingrese la fecha del comentario (DD-MM-AAAA): ");
        fflush(stdin);
        fgets(fecha, 11, stdin);
        fecha[strcspn(fecha, "\n")] = 0; // Eliminar el salto de línea

        if (esFechaValida(fecha)) {
            fechaValida = 1;
        } else {
            printf("Fecha invalida. Por favor, intente nuevamente.\n");
        }
    }
}
// Funcion para ingresar la contrasenia camuflada con asteriscos
void ingresarContraseniaCamuflada(char *password) {
    int idx = 0;
    char ch;
    printf("Ingrese su contrasenia: ");
    while ((ch = getch()) != '\r') { // '\r' es el codigo de Enter
        if (ch == '\b') { // Manejar el retroceso
            if (idx > 0) {
                printf("\b \b");
                idx--;
            }
        } else {
            password[idx++] = ch;
            printf("*");
        }
    }
    password[idx] = '\0'; // Terminar la cadena con el caracter nulo
    printf("\n");
}

void mostrarComentario(stComentario comentario) {

        printf("\n.................................................\n");
        printf("\nID Comentario: %d\n", comentario.idComentario);
        //printf("ID Libro: %d\n", comentario.idLibro);
        //printf("contrasenia: %s\n", comentario.password);
        printf("Nombre de usuario: %s\n", comentario.nombreUsuario);
        printf("Descripcion: %s\n", comentario.descripcion);
        printf("Valoracion: %d\n", comentario.puntaje);
        printf("Fecha Comentario: %s\n", comentario.fechaComentario);
        printf("\n.................................................\n");

}

void mostrarComentarios(stComentario comentario[], int cantidad) {
    for (int i = 0; i < cantidad; i++) {
        mostrarComentario(comentario[i]);
    }
}

int cargarComentario(const char *filename, stComentario comentario[], int maxComentario) {
    int cantidad = 0;
    FILE *file = fopen(filename, "rb");
    if (file != NULL) {
        while (fread(&comentario[cantidad], sizeof(stComentario), 1, file) > 0 && cantidad < maxComentario) {
            if (comentario[cantidad].idComentario > idComentarioCounter) {
                idComentarioCounter = comentario[cantidad].idComentario;
            }
            cantidad++;
        }
        fclose(file);
    }
    return cantidad;
}

void guardarComentario(const char *filename, stComentario comentario[], int cantidad) {
    FILE *file = fopen(filename, "wb");
    if (file != NULL) {
        fwrite(comentario, sizeof(stComentario), cantidad, file);
        fclose(file);
    } else {
        printf("Error al abrir el archivo.\n");
    }
}

void agregarComentarioLista(stComentario comentario[], int *cantidad, stComentario nuevoComentario) {
    comentario[*cantidad] = nuevoComentario;
    (*cantidad)++;
}
