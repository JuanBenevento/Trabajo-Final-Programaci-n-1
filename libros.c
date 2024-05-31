#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libros.h"
//S e crea una variable para crear el contador de ID.
int idLibroCounter = 0;

stLibro agregarLibro() {
    stLibro nuevoLibro;

    nuevoLibro.idLibro = ++idLibroCounter;//Funcion incrementa el contador de ID.

    printf("Ingrese el título del libro: ");
    fgets(nuevoLibro.titulo, 100, stdin);
    nuevoLibro.titulo[strcspn(nuevoLibro.titulo, "\n")] = '\0';

    printf("Ingrese la editorial: ");
    fgets(nuevoLibro.editorial, 50, stdin);
    nuevoLibro.editorial[strcspn(nuevoLibro.editorial, "\n")] = '\0';

    printf("Ingrese el autor: ");
    fgets(nuevoLibro.autor, 50, stdin);
    nuevoLibro.autor[strcspn(nuevoLibro.autor, "\n")] = '\0';

    printf("Ingrese la categoría: ");
    fgets(nuevoLibro.categoria, 50, stdin);
    nuevoLibro.categoria[strcspn(nuevoLibro.categoria, "\n")] = '\0';

    nuevoLibro.valoracion = 0.0;
    nuevoLibro.eliminado = 0;

    return nuevoLibro;
}

void mostrarLibro(stLibro libro) {
    if (libro.eliminado == 0) {
        printf("ID: %d\n", libro.idLibro);
        printf("Título: %s\n", libro.titulo);
        printf("Editorial: %s\n", libro.editorial);
        printf("Autor: %s\n", libro.autor);
        printf("Categoría: %s\n", libro.categoria);
        printf("Valoración: %.2f\n", libro.valoracion);
    }
}
