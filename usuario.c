#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "usuario.h"

// Funcion para cargar un usuario
stUsuario cargarUnUsuario(int idUsuario) {
    stUsuario usuario;

    char aux[100];

    do {
        printf("Ingrese su email: ");
        fflush(stdin);
        gets(usuario.email);
        if (!validarEmail(usuario.email)){
            printf("Email no valido.");
        }
    } while (!validarEmail(usuario.email) || emailRegistrado("usuarios.dat", usuario.email));

    do {
        printf("Ingrese su contrasenia: ");
        fflush(stdin);
        gets(usuario.password);
        if (!validarPassword(usuario.password)){
            printf("Contrasenia no valida.");
        }
    } while (!validarPassword(usuario.password));

    printf("Ingrese el nombre de usuario: ");
    fflush(stdin);
    scanf("%s", usuario.username);

    printf("Ingrese el genero (M/F): ");
    fflush(stdin);
    scanf(" %c", &usuario.genero);

    printf("Ingrese la fecha de nacimiento (DD-MM-AAAA): ");
    fflush(stdin);
    scanf("%s", usuario.fechaNacimiento);

    printf("Ingrese el DNI: ");
    fflush(stdin);
    scanf("%s", usuario.dni);

    usuario.domicilio = cargaUnDomicilio();

    printf("Ingrese si es administrador (1 = Si, 0 = No): ");
    scanf("%d", &usuario.esAdmin);


    usuario.eliminado = 0;

    usuario.idUsuario = idUsuario; // Asignar el ID del usuario

    return usuario;
}

// Funcion para mostrar un usuario
void mostrarUnUsuario(stUsuario usuario) {
    if (usuario.eliminado == 0) {
        printf("\n**********************************************");
        printf("\nID Usuario:....................%d", usuario.idUsuario);
        printf("\nEmail:.........................%s", usuario.email);
        printf("\nNombre de Usuario:.............%s", usuario.username);
        printf("\nGenero:........................%c", usuario.genero);
        printf("\nFecha de Nacimiento:...........%s", usuario.fechaNacimiento);
        printf("\nDNI:...........................%s", usuario.dni);
        mostrarUnDomicilio(usuario.domicilio);
        printf("\nAdministrador:.................%s", usuario.esAdmin ? "Si" : "No");
        printf("\n**********************************************\n");
    }
}

int validarPassword(const char *password) {  //A esta funcion le podemos agregar un minimo de caracteres tambien
    int tieneMayuscula = 0;
    int tieneMinuscula = 0;
    for (int i = 0; password[i] != '\0'; i++) {
        if (isupper(password[i])) tieneMayuscula = 1;
        if (islower(password[i])) tieneMinuscula = 1;
    }
    return tieneMayuscula && tieneMinuscula;
}


// Funcion para marcar un usuario como eliminado
void eliminarUsuario(stUsuario* usuario) {
    usuario->eliminado = 1;
}

void mostrarTodosUsuarios(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (file != NULL) {
        stUsuario usuario;
        while (fread(&usuario, sizeof(stUsuario), 1, file) > 0) {
            mostrarUnUsuario(usuario);
        }
        fclose(file);
    } else {
        printf("Error al abrir el archivo.\n");
    }
}

int validarEmail(const char *email) {
    return strstr(email, "@") && strstr(email, ".com");
}


int emailRegistrado(const char *filename, const char *email) {
    FILE *file = fopen(filename, "rb");
    if (file != NULL) {
        stUsuario usuario;
        while (fread(&usuario, sizeof(stUsuario), 1, file) > 0) {
            if (usuario.eliminado == 0 && strcmp(usuario.email, email) == 0) {
                fclose(file);
                return 1;
            }
        }
        fclose(file);
    }
    return 0;
}
