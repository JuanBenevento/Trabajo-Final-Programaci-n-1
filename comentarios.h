#ifndef COMENTARIOS_H_INCLUDED
#define COMENTARIOS_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include "libros.h"

#define MAX_DESCRIPCION 1000

typedef struct {
    int idComentario;  // único, autoincremental
    int idLibro;
    char password[20];
    char nombreUsuario [50];
    char tituloComentario[100];
    char descripcion[MAX_DESCRIPCION];
    int puntaje; // de 0 a 5 "estrellas"
    char fechaComentario[20]; // o se puede hacer con dia, mes, anio
    int eliminado; // 0 si está activo - 1 si está eliminado
} stComentario;


stComentario agregarComentario();
void mostrarComentario(stComentario comentario);
void mostrarComentarios(stComentario comentario[], int cantidad);
int cargarComentario(const char *filename, stComentario comentario[], int maxComentario);
void guardarComentario(const char *filename, stComentario comentario[], int cantidad);
void agregarComentarioLista(stComentario comentario[], int *cantidad, stComentario nuevoComentario);


#endif // COMENTARIOS_H_INCLUDED
