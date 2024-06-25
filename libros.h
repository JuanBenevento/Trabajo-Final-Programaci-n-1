#ifndef LIBROS_H_INCLUDED
#define LIBROS_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

#include "comentarios.h"

 typedef struct {
    int idLibro; /// único, autoincremental
    char titulo[100];
    char editorial[50];
    char autor[50];
    char categoria[50];
    float valoracion;
    int eliminado; /// 0 si está activo - 1 si está eliminado
}stLibro;

stLibro agregarLibro();
void mostrarLibro(stLibro libro);
void mostrarLibros(stLibro libros[], int cantidad);
int cargarLibros(const char *filename, stLibro libros[], int maxLibros);
void guardarLibros(const char *filename, stLibro libros[], int cantidad);
void agregarLibroLista(stLibro libros[], int *cantidad, stLibro nuevoLibro);
void eliminarLibro(stLibro libros[], int *cantidad, int idLibro);
void mostrarLibrosPorCategoria(stLibro libros[], int cantidad, char categoria[]);
void mostrarLibrosPorAutor(stLibro libros[], int cantidad, char autor[]);
void buscarLibrosPorTitulo(stLibro libros[], int cantidad, char titulo[]);


#endif // LIBROS_H_INCLUDED


