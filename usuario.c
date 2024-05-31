#include "usuario.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "usuario.h"

// Funci�n para cargar un usuario
stUsuario cargarUnUsuario(int idUsuario) {
    stUsuario usuario;
    usuario.idUsuario = idUsuario;

    char aux[100];
    printf("\n***********************************************");
    printf("\n");
    printf("\nIngrese el email: ");
    fflush(stdin);
    scanf("%s", usuario.email);

    printf("\nIngrese la contrase�a: ");
    fflush(stdin);
    scanf("%s", usuario.password);

    printf("\nIngrese el nombre de usuario: ");
    fflush(stdin);
    scanf("%s", usuario.username);

    printf("\nIngrese el g�nero (M/F): ");
    fflush(stdin);
    scanf(" %c", &usuario.genero);

    printf("\nIngrese la fecha de nacimiento (DD-MM-AAAA): ");
    fflush(stdin);
    scanf("%s", usuario.fechaNacimiento);

    printf("\nIngrese el DNI: ");
    fflush(stdin);
    scanf("%s", usuario.dni);

    usuario.domicilio = cargaUnDomicilio();

    printf("\nIngrese si es administrador (1 = S�, 0 = No): ");
    scanf("%d", &usuario.esAdmin);
    printf("\n");
    printf("\n***********************************************");

    usuario.eliminado = 0;

    // Inicializar libros favoritos con -1 (indicando vac�o)
    for (int i = 0; i < 50; i++) {
        usuario.librosFavoritos[i] = -1;
    }

    return usuario;
}

// Funci�n para mostrar un usuario
void mostrarUnUsuario(stUsuario usuario) {
    if (usuario.eliminado == 0) {
        printf("\n**********************************************");
        printf("\nID Usuario:....................%d", usuario.idUsuario);
        printf("\nEmail:.........................%s", usuario.email);
        printf("\nNombre de Usuario:.............%s", usuario.username);
        printf("\nG�nero:........................%c", usuario.genero);
        printf("\nFecha de Nacimiento:...........%s", usuario.fechaNacimiento);
        printf("\nDNI:...........................%s", usuario.dni);
        mostrarUnDomicilio(usuario.domicilio);
        printf("\nAdministrador:.................%s", usuario.esAdmin ? "S�" : "No");
        printf("\nLibros Favoritos:..............");

        int i;
        for (i = 0; i < 50; i++) {
            if (usuario.librosFavoritos[i] != -1) {
                printf("%d ", usuario.librosFavoritos[i]);
            } else {
                break;
            }
        }
        if (i == 0) {
            printf("Ninguno");
        }

        printf("\n**********************************************\n");
    }
}

// Funci�n para agregar un libro favorito a un usuario
void agregarLibroFavorito(stUsuario* usuario, int idLibro) {
    for (int i = 0; i < 50; i++) {
        if (usuario->librosFavoritos[i] == -1) {
            usuario->librosFavoritos[i] = idLibro;
            break;
        }
    }
}

// Funci�n para eliminar un libro favorito de un usuario
void eliminarLibroFavorito(stUsuario* usuario, int idLibro) {
    for (int i = 0; i < 50; i++) {
        if (usuario->librosFavoritos[i] == idLibro) {
            usuario->librosFavoritos[i] = -1;
            break;
        }
    }
}

// Funci�n para marcar un usuario como eliminado
void eliminarUsuario(stUsuario* usuario) {
    usuario->eliminado = 1;
}



