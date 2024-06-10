#ifndef COMENTARIOS_H_INCLUDED
#define COMENTARIOS_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

typedef struct {
    int idComentario;  // único, autoincremental
    int idLibro;
    int idUsuario;
    char tituloComentario[100];
    char descripcion[500];
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
void eliminarComentario(stComentario *comentario);



#endif // COMENTARIOS_H_INCLUDED
