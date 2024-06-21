#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "comentarios.h"

// Variable global para mantener el contador de IDs
int idComentarioCounter = 0;

// Funci�n para inicializar un nuevo comentario
stComentario agregarComentario() {
    stComentario nuevoComentario;
    nuevoComentario.idComentario = ++idComentarioCounter; // Incrementar y asignar el nuevo ID

    printf("Ingrese el ID del libro: ");
    scanf("%d", &nuevoComentario.idLibro);
    getchar(); // Limpiar el buffer del teclado

    /*
    printf("Ingrese el ID del usuario: ");
    scanf("%d", &nuevoComentario.idUsuario);
    getchar(); // Limpiar el buffer del teclado
    */

    printf("Ingrese el nombre del usuario: ");
    scanf("%s", &nuevoComentario.nombreUsuario);
    getchar();

    printf("Ingrese la descripcion del comentario: ");
    fgets(nuevoComentario.descripcion, sizeof(nuevoComentario.descripcion), stdin);
    // Eliminar el salto de l�nea al final de la cadena, si fue capturado por fgets
    if (nuevoComentario.descripcion[strlen(nuevoComentario.descripcion) - 1] == '\n') {
        nuevoComentario.descripcion[strlen(nuevoComentario.descripcion) - 1] = '\0';
    }

    do {
        printf("Ingrese la valoracion del libro (0-5): ");
        scanf("%d", &nuevoComentario.puntaje);
        getchar(); // Limpiar el buffer del teclado
    } while (nuevoComentario.puntaje < 0 || nuevoComentario.puntaje > 5);

    printf("Ingrese la fecha del comentario (DD-MM-AAAA): ");
    fgets(nuevoComentario.fechaComentario, 20, stdin);
    nuevoComentario.fechaComentario[strcspn(nuevoComentario.fechaComentario, "\n")] = '\0'; // Eliminar el salto de l�nea

    nuevoComentario.eliminado = 0; // El comentario se marca como activo


    return nuevoComentario;
}

// Funci�n para mostrar la informaci�n de un comentario
void mostrarComentario(stComentario comentario) {

        printf("\n------------------------------------------------\n");
        printf("\nID Comentario: %d\n", comentario.idComentario);
        printf("ID Libro: %d\n", comentario.idLibro);
        //printf("ID Usuario: %d\n", comentario.idUsuario);
        printf("Nombre de usuario: %s\n", comentario.nombreUsuario);
        printf("Descripcion: %s\n", comentario.descripcion);
        printf("Valoracion: %d\n", comentario.puntaje);
        printf("Fecha Comentario: %s\n", comentario.fechaComentario);
        printf("\n-------------------------------------------------\n");

}

void mostrarComentarios(stComentario comentario[], int cantidad) {
    for (int i = 0; i < cantidad; i++) {
        mostrarComentario(comentario[i]);
    }
}

int cargarComentario(const char *filename, stComentario comentario[], int maxComentario) {
    int cantidad = 0;
    FILE *file = fopen(filename, "r+b");
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

