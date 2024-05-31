#ifndef USUARIO_H_INCLUDED
#define USUARIO_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include "domicilio.h"

typedef struct {
    int idUsuario;
    char email[100];
    char password[20];
    char username[20];
    int esAdmin; // 1 = si  0 = no
    char genero;
    char fechaNacimiento[20]; // o se puede hacer con dia, mes, anio
    int librosFavoritos[50]; // se van a guardar los id de los libros favs
    char dni[10];
    stDomicilio domicilio;
    int eliminado; // 0 si está activo - 1 si está eliminado
} stUsuario;

stUsuario cargarUnUsuario(int idUsuario);
void mostrarUnUsuario(stUsuario usuario);
void agregarLibroFavorito(stUsuario* usuario, int idLibro);
void eliminarLibroFavorito(stUsuario* usuario, int idLibro);
void eliminarUsuario(stUsuario* usuario);


#endif // USUARIO_H_INCLUDED
