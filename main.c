#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

#include "usuario.h"
#include "libros.h"
#include "comentarios.h"
#include "domicilio.h"

// Prototipos de funciones
void registrarUsuario(const char *filename, int *idUsuario);
int iniciarSesion(const char *filename, stUsuario *usuarioLogueado);

int main() {
    int option;
    int idUsuario = 1;  // Iniciar el ID de usuario con 1 (puedes cargar el último ID usado desde el archivo)
    stUsuario usuarioLogueado;

    printf("TP Final Programacion 1 - Propuesta de la catedra");
    printf("\n***********************************************");
    printf("\n");
    printf("\n1- Iniciar sesion");
    printf("\n2- Registrarme");
    printf("\n0- Salir");
    printf("\n");
    printf("\n***********************************************");
    printf("\nIngrese una opcion: ");
    fflush(stdin);
    scanf("%d", &option);

    switch (option) {
        case 1:
            if (iniciarSesion("usuarios.dat", &usuarioLogueado)) {
                printf("\nInicio de sesion exitoso.\n");
                // Aquí puedes continuar con el menú de funcionalidades para el usuario logueado
            } else {
                printf("\nError en el inicio de sesion.\n");
            }
            break;
        case 2:
            registrarUsuario("usuarios.dat", &idUsuario);
            break;
        case 0:
            printf("\nSaliendo del programa...\n");
            break;
        default:
            printf("\nOpcion no valida.\n");
            break;
    }

    return 0;
}

// Función para registrar un usuario y guardarlo en un archivo binario
void registrarUsuario(const char *filename, int *idUsuario) {
    stUsuario usuario = cargarUnUsuario(*idUsuario);
    (*idUsuario)++;

    FILE *file = fopen(filename, "ab");
    if (file != NULL) {
        fwrite(&usuario, sizeof(stUsuario), 1, file);
        fclose(file);
        printf("\nUsuario registrado exitosamente.\n");
    } else {
        printf("\nError al abrir el archivo.\n");
    }

    // Mostrar el usuario registrado
    mostrarUnUsuario(usuario);
}

// Función para iniciar sesión
int iniciarSesion(const char *filename, stUsuario *usuarioLogueado) {
    char email[100];
    char password[20];
    stUsuario usuario;

    printf("\nIngrese su email: ");
    fflush(stdin);
    scanf("%s", email);
    printf("\nIngrese su contrasena: ");
    fflush(stdin);
    scanf("%s", password);

    FILE *file = fopen(filename, "rb");
    if (file != NULL) {
        while (fread(&usuario, sizeof(stUsuario), 1, file) > 0) {
            if (usuario.eliminado == 0 && strcmp(usuario.email, email) == 0 && strcmp(usuario.password, password) == 0) {
                *usuarioLogueado = usuario;
                fclose(file);
                return 1;
            }
        }
        fclose(file);
    } else {
        printf("\nError al abrir el archivo.\n");
    }

    return 0;
}

