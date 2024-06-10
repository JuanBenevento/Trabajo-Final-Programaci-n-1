#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

#include "usuario.h"
#include "libros.h"
#include "comentarios.h"
#include "domicilio.h"

#define MAX_LIBROS 200
#define LIBROS_FILE "libros.dat" // Definicion de LIBROS_FILE
#define MAX_COMENTARIO 200
#define COMENTARIO_FILE "comentario.dat"

void registrarUsuario(const char *filename, int *idUsuario);
int iniciarSesion(const char *filename, stUsuario *usuarioLogueado);
void modificarInformacionPersonal(const char *filename, stUsuario *usuarioLogueado);
void desloguearse(stUsuario *usuarioLogueado);
void darDeBajaUsuario(const char *filename);
void eliminarLibroDefinitivamente(stLibro libros[], int *cantidad, int idLibro, const char *librosFilename);
void mostrarLibrosConCometarios (stLibro libros[], int cantidadLib, stComentario comentario[], int cantidadCom);

int main() {
    int option;
    int idUsuario = 1;  // Iniciar el ID de usuario con 1 (puedes cargar el último ID usado desde el archivo)
    stUsuario usuarioLogueado;
    stLibro libros[MAX_LIBROS];
    stComentario comentario[MAX_COMENTARIO];
    int cantidadComentario = 0;
    int cantidadLibros = 0;

    // Cargar los libros desde el archivo
    cantidadLibros = cargarLibros(LIBROS_FILE, libros, MAX_LIBROS);
    cantidadComentario = cargarComentario(COMENTARIO_FILE, comentario, MAX_COMENTARIO);


    do {
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
                    int opcion;
                do {
                        printf("\n***********************************************");
                        printf("\n");
                        printf("\n1- Agregar Libro.");
                        printf("\n2- Mostrar Libros.");
                        printf("\n3- Mostrar Libros por Categoria.");
                        printf("\n4- Mostrar Libros por Autor.");
                        printf("\n5- Buscar Libros por Titulo.");
                        printf("\n6- Modificar Informacion Personal.");
                        printf("\n7- Desloguearse.");
                        if (usuarioLogueado.esAdmin) {
                            printf("\n8- Ver Todos los Usuarios.");
                            printf("\n9- Dar de Baja Usuario.");
                            printf("\n10- Dar de Baja Libro.");
                            printf("\n11- Eliminar Libro Definitivamente.");
                        }
                        printf("\n0- Salir");
                        printf("\n");
                        printf("\n***********************************************");
                        printf("\nIngrese una opcion: ");
                        fflush(stdin);
                        scanf("%d", &opcion);
                        getchar(); // para consumir el salto de línea después de scanf

                        switch (opcion) {
                            case 1: {
                                stLibro nuevoLibro = agregarLibro();
                                agregarLibroLista(libros, &cantidadLibros, nuevoLibro);
                                guardarLibros(LIBROS_FILE, libros, cantidadLibros); // Usar LIBROS_FILE
                                break;
                            }
                            case 2:
                                mostrarLibrosConCometarios(libros, cantidadLibros, comentario, cantidadComentario);
                                int elegir;
                                do{
                                        printf("\n***********************************************");
                                        printf("\n");
                                        printf("\n1- Comentar libro");
                                        printf("\n0- Salir");
                                        printf("\n");
                                        printf("\n***********************************************");
                                        printf("\nIngrese una opcion: ");
                                        fflush(stdin);
                                        scanf("%d", &elegir);
                                        getchar();

                                    switch(elegir){
                                        case 1:;
                                            stComentario nuevoComentario = agregarComentario();
                                            agregarComentarioLista(comentario, &cantidadComentario, nuevoComentario);
                                            guardarComentario(COMENTARIO_FILE, comentario, cantidadComentario);
                                            guardarLibros(LIBROS_FILE, libros, cantidadLibros);
                                            break;
                                    }
                                }while (elegir != 0);
                                break;
                            case 3: {
                                char categoria[50];
                                printf("Ingrese la categoria: ");
                                fgets(categoria, 50, stdin);
                                categoria[strcspn(categoria, "\n")] = '\0';
                                mostrarLibrosPorCategoria(libros, cantidadLibros, categoria);
                                break;
                            }
                            case 4: {
                                char autor[50];
                                printf("Ingrese el autor: ");
                                fgets(autor, 50, stdin);
                                autor[strcspn(autor, "\n")] = '\0';
                                mostrarLibrosPorAutor(libros, cantidadLibros, autor);
                                break;
                            }
                            case 5: {
                                char titulo[100];
                                printf("\nBuscar respetando mayusculas y minusculas del titulo.\n");
                                printf("Ingrese el titulo: ");
                                fgets(titulo, 100, stdin);
                                titulo[strcspn(titulo, "\n")] = '\0';
                                buscarLibrosPorTitulo(libros, cantidadLibros, titulo);
                                break;
                            }
                            case 6:
                                modificarInformacionPersonal("usuarios.dat", &usuarioLogueado);
                                break;
                            case 7:
                                if (usuarioLogueado.esAdmin) {
                                    mostrarTodosUsuarios("usuarios.dat");
                                }
                                break;
                            case 8:
                                if (usuarioLogueado.esAdmin) {
                                    darDeBajaUsuario("usuarios.dat");
                                }
                                break;
                            case 9:
                                if (usuarioLogueado.esAdmin) {
                                    int idLibro;
                                    printf("Ingrese el ID del libro a dar de baja: ");
                                    scanf("%d", &idLibro);
                                    eliminarLibro(libros, &cantidadLibros, idLibro);
                                    guardarLibros(LIBROS_FILE, libros, cantidadLibros); // Usar LIBROS_FILE
                                }
                                break;
                            case 10:
                                if (usuarioLogueado.esAdmin) {
                                    int idLibro;
                                    printf("Ingrese el ID del libro a eliminar definitivamente: ");
                                    scanf("%d", &idLibro);
                                    eliminarLibroDefinitivamente(libros, &cantidadLibros, idLibro, LIBROS_FILE);
                                }
                                break;
                            default:
                                if (opcion != 0) {
                                    printf("\nOpcion no valida.\n");
                                }
                                break;
                        }
                    } while (opcion != 0 && usuarioLogueado.idUsuario != 0);

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
    } while (option != 0);

    return 0;
}

// Funcion para registrar un usuario y guardarlo en un archivo binario
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

// Funcion para iniciar sesion
int iniciarSesion(const char *filename, stUsuario *usuarioLogueado) {
    char email[100];
    char password[20];
    stUsuario usuario;

    printf("\nIngrese su email: ");
    fflush(stdin);
    scanf("%s", email);
    printf("\nIngrese su contrasenia: ");
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

// Funcion para modificar la informacion personal del usuario logueado
void modificarInformacionPersonal(const char *filename, stUsuario *usuarioLogueado) {
    printf("\nIngrese su nuevo email: ");
    fflush(stdin);
    gets(usuarioLogueado->email);

    printf("Ingrese su nueva contrasenia: ");
    fflush(stdin);
    gets(usuarioLogueado->password);

    printf("Ingrese su nuevo nombre: ");
    fflush(stdin);
    gets(usuarioLogueado->username);

    printf("Ingrese su nuevo genero (M/F): ");
    fflush(stdin);
    gets(usuarioLogueado->genero);

    printf("Ingrese su nueva fecha de nacimiento: ");
    fflush(stdin);
    gets(usuarioLogueado->fechaNacimiento);

    printf("Ingrese su nuevo DNI: ");
    fflush(stdin);
    gets(usuarioLogueado->dni);

    // Guardar cambios en el archivo
    FILE *file = fopen(filename, "r+b");
    if (file != NULL) {
        stUsuario usuario;
        while (fread(&usuario, sizeof(stUsuario), 1, file) > 0) {
            if (usuario.idUsuario == usuarioLogueado->idUsuario) {
                fseek(file, -sizeof(stUsuario), SEEK_CUR);
                fwrite(usuarioLogueado, sizeof(stUsuario), 1, file);
                break;
            }
        }
        fclose(file);
        printf("\nInformacion modificada exitosamente.\n");
    } else {
        printf("\nError al abrir el archivo.\n");
    }
}

// Funcion para desloguearse
void desloguearse(stUsuario *usuarioLogueado) {
    usuarioLogueado->idUsuario = 0;
    strcpy(usuarioLogueado->email, "");
    strcpy(usuarioLogueado->password, "");
    usuarioLogueado->esAdmin = 0;
    usuarioLogueado->eliminado = 0;
    printf("\nDeslogueo exitoso.\n");
}

// Funcion para dar de baja un usuario
void darDeBajaUsuario(const char *filename) {
    char email[100];
    printf("\nIngrese el email del usuario a dar de baja: ");
    fflush(stdin);
    gets(email);

    FILE *file = fopen(filename, "rb+");
    if (file != NULL) {
        stUsuario usuario;
        while (fread(&usuario, sizeof(stUsuario), 1, file) > 0) {
            if (usuario.eliminado == 0 && strcmp(usuario.email, email) == 0) {
                usuario.eliminado = 1;
                fseek(file, -sizeof(stUsuario), SEEK_CUR);
                fwrite(&usuario, sizeof(stUsuario), 1, file);
                printf("\nUsuario dado de baja exitosamente.\n");
                break;
            }
        }
        fclose(file);
    } else {
        printf("\nError al abrir el archivo.\n");
    }
}

void eliminarLibroDefinitivamente(stLibro libros[], int *cantidad, int idLibro, const char *librosFilename) {
    for (int i = 0; i < *cantidad; i++) {
        if (libros[i].idLibro == idLibro) {
            for (int j = i; j < *cantidad - 1; j++) {
                libros[j] = libros[j + 1];
            }
            (*cantidad)--;
            break;
        }
    }
    guardarLibros(librosFilename, libros, *cantidad); // Actualizar el archivo después de la eliminación
}

void mostrarLibrosConCometarios (stLibro libros[], int cantidadLib, stComentario comentario[], int cantidadCom){

    for (int i = 0; i < cantidadLib; i++) {
        mostrarLibro(libros[i]);
        for ( int j =0; j < cantidadCom; j++){
            mostrarComentario(comentario[j]);
        }
    }

}
