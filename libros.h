#ifndef LIBROS_H_INCLUDED
#define LIBROS_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

 typedef struct {
    int idLibro; /// �nico, autoincremental
    char titulo[100];
    char editorial[50];
    char autor[50];
    char categoria[50];
    float valoracion;
    int eliminado; /// 0 si est� activo - 1 si est� eliminado
}stLibro;

stLibro agregarLibro();
void mostrarLibro(stLibro libro);


#endif // LIBROS_H_INCLUDED
