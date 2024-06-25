#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libros.h"


// Variable global para llevar el conteo del ID de los libros
int idLibroCounter = 0;

stLibro agregarLibro() {
    stLibro nuevoLibro;

    nuevoLibro.idLibro = ++idLibroCounter;

    printf("Ingrese el titulo del libro: ");
    fflush(stdin);
    fgets(nuevoLibro.titulo, 100, stdin);
    nuevoLibro.titulo[strcspn(nuevoLibro.titulo, "\n")] = '\0';

    printf("Ingrese la editorial: ");
    fflush(stdin);
    fgets(nuevoLibro.editorial, 50, stdin);
    nuevoLibro.editorial[strcspn(nuevoLibro.editorial, "\n")] = '\0';

    printf("Ingrese el autor: ");
    fflush(stdin);
    fgets(nuevoLibro.autor, 50, stdin);
    nuevoLibro.autor[strcspn(nuevoLibro.autor, "\n")] = '\0';

    printf("Ingrese la categoria: ");
    fflush(stdin);
    fgets(nuevoLibro.categoria, 50, stdin);
    nuevoLibro.categoria[strcspn(nuevoLibro.categoria, "\n")] = '\0';

    nuevoLibro.valoracion = 0.0;
    nuevoLibro.eliminado = 0;

    return nuevoLibro;
}

void mostrarLibro(stLibro libro) {
    if (libro.eliminado == 0) {
        printf("\n|||||||||||||||||||||||||||||||||||||||||||\n");
        printf("ID: %d\n", libro.idLibro);
        printf("Titulo: %s\n", libro.titulo);
        printf("Editorial: %s\n", libro.editorial);
        printf("Autor: %s\n", libro.autor);
        printf("Categoria: %s\n", libro.categoria);
        printf("Valoracion: %.2f\n", libro.valoracion);
        printf("\n|||||||||||||||||||||||||||||||||||||||||||\n");
    }
}

void mostrarLibros(stLibro libros[], int cantidad) {
    for (int i = 0; i < cantidad; i++) {
        mostrarLibro(libros[i]);
    }
}

int cargarLibros(const char *filename, stLibro libros[], int maxLibros) {
    int cantidad = 0;
    FILE *file = fopen(filename, "rb");
    if (file != NULL) {
        while (fread(&libros[cantidad], sizeof(stLibro), 1, file) > 0 && cantidad < maxLibros) {
            if (libros[cantidad].idLibro > idLibroCounter) {
                idLibroCounter = libros[cantidad].idLibro;
            }
            cantidad++;
        }
        fclose(file);
    }
    return cantidad;
}

void guardarLibros(const char *filename, stLibro libros[], int cantidad) {
    FILE *file = fopen(filename, "wb");
    if (file != NULL) {
        fwrite(libros, sizeof(stLibro), cantidad, file);
        fclose(file);
    } else {
        printf("Error al abrir el archivo.\n");
    }
}

void agregarLibroLista(stLibro libros[], int *cantidad, stLibro nuevoLibro) {
    libros[*cantidad] = nuevoLibro;
    (*cantidad)++;
}

void eliminarLibro(stLibro libros[], int *cantidad, int idLibro) {
    for (int i = 0; i < *cantidad; i++) {
        if (libros[i].idLibro == idLibro) {
            libros[i].eliminado = 1;
            break;
        }
    }
}

void mostrarLibrosPorCategoria(stLibro libros[], int cantidad, char categoria[]) {
    for (int i = 0; i < cantidad; i++) {
        if (libros[i].eliminado == 0 && strcmp(libros[i].categoria, categoria) == 0) {
            mostrarLibro(libros[i]);
        }
    }
}

void mostrarLibrosPorAutor(stLibro libros[], int cantidad, char autor[]) {
    for (int i = 0; i < cantidad; i++) {
        if (libros[i].eliminado == 0 && strcmp(libros[i].autor, autor) == 0) {
            mostrarLibro(libros[i]);
        }
    }
}

void buscarLibrosPorTitulo(stLibro libros[], int cantidad, char titulo[]) {
    for (int i = 0; i < cantidad; i++) {
        if (libros[i].eliminado == 0 && strstr(libros[i].titulo, titulo) != NULL) {
            mostrarLibro(libros[i]);
        }
    }
}
