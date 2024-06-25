#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

#include "usuario.h"
#include "libros.h"
#include "comentarios.h"
#include "domicilio.h"

#define ID_FILE "last_id.txt"
#define MAX_LIBROS 200
#define LIBROS_FILE "libros.dat"
#define MAX_COMENTARIO 500
#define COMENTARIO_FILE "comentario.dat"
#define MAX_FAVORITOS 100
#define FAVORITOS_FILE "favoritos.dat"

typedef struct {
    int idUsuario;
    int idLibro;
} stFavorito;

int leerUltimoIdUsuario(const char *filename);
void guardarUltimoIdUsuario(const char *filename, int idUsuario);
void registrarUsuario(const char *filename, int *idUsuario);
int iniciarSesion(const char *filename, stUsuario *usuarioLogueado);
void modificarInformacionPersonal(const char *filename, stUsuario *usuarioLogueado);
void desloguearse(stUsuario *usuarioLogueado);
void darDeBajaUsuario(const char *filename);
void eliminarLibroDefinitivamente(stLibro libros[], int *cantidad, int idLibro, const char *librosFilename);
void mostrarLibrosConComentarios(stLibro libros[], int cantidadLib, stComentario comentarios[], int cantidadCom);
void modificarComentario(stComentario comentarios[], int cantidad, int idComentario, const char *comentarioFilename, const char *contrasenia);
void eliminarComentario(stComentario comentarios[], int *cantidad, int idComentario, const char *comentarioFilename, const char *contrasenia);
void calcularPromedioPuntajes(stComentario comentario[], int cantidadComentario, stLibro libros[], int cantidadLibros);
void mostrarLibrosFavoritos(const stFavorito favoritos[], int cantidadFavoritos, const stLibro libros[], int cantidadLibros, int idUsuario);
void agregarLibroAFavoritos(stFavorito favoritos[], int *cantidadFavoritos, int idUsuario, stLibro libro, int cantLibrosFav);
void eliminarLibroDeFavoritos(stFavorito favoritos[], int *cantidadFavoritos, int idUsuario, int idLibro);
void guardarFavoritos(const char *filename, stFavorito favoritos[], int cantidadFavoritos);
int cargarFavoritos(const char *filename, stFavorito favoritos[], int maxFavoritos);

void menuPrincipal(int *opcion);
void subMenuComentarios(stLibro libros[], int *cantidadLibros, stComentario comemtario[], int *cantidadComentario);
void submenuUsuario(stLibro libros[], int *cantidadLibros, stComentario comentario[], int *cantidadComentario, stFavorito favoritos[], int *cantidadFavoritos, stUsuario usuarioLogueado[]);

int main() {
    int option;
    stUsuario usuarioLogueado;
    stLibro libros[MAX_LIBROS];
    stComentario comentario[MAX_COMENTARIO];
    stFavorito favoritos[MAX_FAVORITOS];
    int idUsuario = leerUltimoIdUsuario(ID_FILE);
    int cantidadComentario = 0;
    int cantidadLibros = 0;
    int cantidadFavoritos = 0;

    // Cargar los libros desde el archivo
    cantidadLibros = cargarLibros(LIBROS_FILE, libros, MAX_LIBROS);
    cantidadComentario = cargarComentario(COMENTARIO_FILE, comentario, MAX_COMENTARIO);
    cantidadFavoritos = cargarFavoritos(FAVORITOS_FILE, favoritos, MAX_FAVORITOS);
    // Calcular el promedio de puntajes de comentarios para los libros cargados


    do {
        menuPrincipal(&option);
        system("cls");

        switch (option) {
            case 1:
                if (iniciarSesion("usuarios.dat", &usuarioLogueado)) {
                    printf("\nInicio de sesion exitoso.\n");
                    int submenuOption;
                    do {
                        submenuUsuario(libros, &cantidadLibros, comentario, &cantidadComentario, favoritos, &cantidadFavoritos, &usuarioLogueado);
                    } while (submenuOption != 0 && usuarioLogueado.idUsuario != 0);
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

void menuPrincipal(int *opcion) {
    printf("TP Final Programacion 1 - Propuesta de la catedra\n");
    printf("***********************************************\n");
    printf("\n1- Iniciar sesion\n");
    printf("2- Registrarme\n");
    printf("0- Salir\n");
    printf("\n***********************************************\n");
    printf("\nIngrese una opcion: ");
    fflush(stdin);
    scanf("%d", opcion);
    system("cls");
}

void subMenuComentarios(stLibro libros[], int *cantidadLibros, stComentario comentario[], int *cantidadComentario){
    int elegir;
    do{
        printf("\n***********************************************");
        printf("\n");
        printf("\n1- Comentar libro");
        printf("\n2- Modificar comentario");
        printf("\n3- Eliminar comentario");
        printf("\n0- Salir");
        printf("\n");
        printf("\n***********************************************");
        printf("\nIngrese una opcion: ");
        fflush(stdin);
        scanf("%d", &elegir);

        switch(elegir){
            case 1:;
                stComentario nuevoComentario = agregarComentario();
                agregarComentarioLista(comentario, *cantidadComentario, nuevoComentario);
                guardarComentario(COMENTARIO_FILE, comentario, *cantidadComentario);
                guardarLibros(LIBROS_FILE, libros, *cantidadLibros);
                break;
            case 2: {
                 int idComentario;
                 char contr[20];
                 printf("Ingrese el ID del comentario a modificar: ");
                 fflush(stdin);
                 scanf("%d", &idComentario);
                 printf("Ingrese su contrasenia de usuario: ");
                 fflush(stdin);
                 scanf("%s", contr);
                 modificarComentario(comentario, *cantidadComentario, idComentario, COMENTARIO_FILE, contr);
                 break;
                 }
           case 3: {
                int idComentario;
                char contr[20];
                printf("Ingrese el ID del comentario a eliminar: ");
                fflush(stdin);
                scanf("%d", &idComentario);
                printf("Ingrese su contrasenia de usuario: ");
                fflush(stdin);
                scanf("%s", contr);
                eliminarComentario(comentario, *cantidadComentario, idComentario, COMENTARIO_FILE, contr);
                break;
                }

        }
    }while (elegir != 0);
}

void submenuUsuario(stLibro libros[], int *cantidadLibros, stComentario comentario[], int *cantidadComentario, stFavorito favoritos[], int *cantidadFavoritos, stUsuario usuarioLogueado[]) {
    int submenuOption;
    do {
        printf("\n**************************************************\n");
        printf("\n1- Agregar Libro.\n");
        printf("2- Mostrar Libros.\n");
        printf("3- Mostrar Libros por Categoria.\n");
        printf("4- Mostrar Libros por Autor.\n");
        printf("5- Buscar Libros por Titulo.\n");
        printf("6- Agregar libro a favoritos\n");
        printf("7- Eliminar libro de favoritos\n");
        printf("8- Mostrar lista de favoritos\n");
        printf("9- Modificar Informacion Personal.\n");
        if (usuarioLogueado->esAdmin) {
            printf("10- Ver Todos los Usuarios.\n");
            printf("11- Dar de Baja Usuario.\n");
            printf("12- Eliminar Libro.\n");
        }
        printf("\n0- Salir");
        printf("\n");
        printf("\n***************************************************\n");
        printf("\nIngrese una opcion: ");
        fflush(stdin);
        scanf("%d", &submenuOption);
        system("cls");

        switch (submenuOption) {
            case 1: {
                stLibro nuevoLibro = agregarLibro();
                agregarLibroLista(libros, cantidadLibros, nuevoLibro);
                guardarLibros(LIBROS_FILE, libros, *cantidadLibros);
                break;
            }
            case 2:
                calcularPromedioPuntajes(comentario, *cantidadComentario, libros, *cantidadLibros);
                mostrarLibrosConComentarios(libros, *cantidadLibros, comentario, *cantidadComentario);
                subMenuComentarios(libros, *cantidadLibros, comentario, *cantidadComentario);
                break;
            case 3: {
                char categoria[50];
                printf("Buscar respetando mayusculas y minusculas del titulo.\n");
                printf("Ingrese la categoria: ");
                fflush(stdin);
                fgets(categoria, 50, stdin);
                categoria[strcspn(categoria, "\n")] = '\0';
                mostrarLibrosPorCategoria(libros, *cantidadLibros, categoria);
                break;
            }
            case 4: {
                char autor[50];
                printf("Buscar respetando mayusculas y minusculas del titulo.\n");
                printf("Ingrese el autor: ");
                fflush(stdin);
                fgets(autor, 50, stdin);
                autor[strcspn(autor, "\n")] = '\0';
                mostrarLibrosPorAutor(libros, *cantidadLibros, autor);
                break;
            }
            case 5: {
                char titulo[100];
                printf("Buscar respetando mayusculas y minusculas del titulo.\n");
                printf("Ingrese el titulo: ");
                fflush(stdin);
                fgets(titulo, 100, stdin);
                titulo[strcspn(titulo, "\n")] = '\0';
                buscarLibrosPorTitulo(libros, *cantidadLibros, titulo);
                break;
            }
            case 6: {
                mostrarLibros(libros, *cantidadLibros);
                int idLibro;
                printf("Ingrese el ID del libro a agregar a favoritos: ");
                scanf("%d", &idLibro);
                stLibro libro;
                for (int i = 0; i < *cantidadLibros; i++) {
                    if (libros[i].idLibro == idLibro) {
                        libro = libros[i];
                        break;
                    }
                }
                agregarLibroAFavoritos(favoritos, cantidadFavoritos, usuarioLogueado->idUsuario, libro, usuarioLogueado->librosFavoritos);
                guardarFavoritos(FAVORITOS_FILE, favoritos, *cantidadFavoritos);
                break;
            }
            case 7: {
                mostrarLibros(libros, *cantidadLibros);
                int idLibro;
                printf("Ingrese el ID del libro a eliminar de favoritos: ");
                scanf("%d", &idLibro);
                eliminarLibroDeFavoritos(favoritos, cantidadFavoritos, usuarioLogueado->idUsuario, idLibro);
                guardarFavoritos(FAVORITOS_FILE, favoritos, *cantidadFavoritos);
                break;
            }
            case 8:
                mostrarLibrosFavoritos(favoritos, *cantidadFavoritos, libros, *cantidadLibros, usuarioLogueado->idUsuario);
                break;
            case 9:
                modificarInformacionPersonal("usuarios.dat", usuarioLogueado);
                break;
            case 10:
                mostrarTodosUsuarios("usuarios.dat");
                break;
            case 11:
                darDeBajaUsuario("usuarios.dat");
                break;
            case 12:;
                int idLibro;
                printf("Ingrese el ID del libro a eliminar definitivamente: ");
                scanf("%d", &idLibro);
                eliminarLibroDefinitivamente(libros, *cantidadLibros, &idLibro, LIBROS_FILE);

                break;
            default:
                printf("\nOpcion no valida.\n");
                break;
        }
    } while (submenuOption != 0);
}

int leerUltimoIdUsuario(const char *filename) {
    FILE *file = fopen(filename, "r");
    int idUsuario = 1; // Valor por defecto si el archivo no existe

    if (file != NULL) {
        fscanf(file, "%d", &idUsuario);
        fclose(file);
    }

    return idUsuario;
}

void guardarUltimoIdUsuario(const char *filename, int idUsuario) {
    FILE *file = fopen(filename, "w");

    if (file != NULL) {
        fprintf(file, "%d", idUsuario);
        fclose(file);
    } else {
        printf("Error al abrir el archivo para guardar el último ID de usuario.\n");
    }
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

    // Guardar el nuevo ultimo ID de usuario
    guardarUltimoIdUsuario(ID_FILE, *idUsuario);
}


// Funcion para iniciar sesion
int iniciarSesion(const char *filename, stUsuario *usuarioLogueado) {
    char email[100];
    char password[20];
    stUsuario usuario;

    printf("Ingrese su email: ");
    fflush(stdin);
    scanf("%s", email);
    printf("Ingrese su contrasenia: ");
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

   do {
        printf("Ingrese su nuevo email: ");
        fflush(stdin);
        gets(usuarioLogueado->email);
        if (!validarEmail(usuarioLogueado->email)){
            printf("Email no valido.");
        }
    } while (!validarEmail(usuarioLogueado->email) || emailRegistrado("usuarios.dat", usuarioLogueado->email));

    do {
        printf("Ingrese su nueva contrasenia: ");
        fflush(stdin);
        gets(usuarioLogueado->password);
        if (!validarPassword(usuarioLogueado->password)){
            printf("Contrasenia no valida.");
        }
    } while (!validarPassword(usuarioLogueado->password));

    printf("Ingrese su nuevo nombre: ");
    fflush(stdin);
    gets(usuarioLogueado->username);

    printf("Ingrese su nuevo genero (M/F): ");
    fflush(stdin);
    scanf(" %c", &usuarioLogueado->genero);

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

void mostrarLibrosConComentarios(stLibro libros[], int cantidadLib, stComentario comentarios[], int cantidadCom) {
    for (int i = 0; i < cantidadLib; i++) {
        mostrarLibro(libros[i]);
        for (int j = 0; j < cantidadCom; j++) {
            if (comentarios[j].idLibro == libros[i].idLibro) {
                mostrarComentario(comentarios[j]);
            }
        }
    }
}

void modificarComentario(stComentario comentarios[], int cantidad, int idComentario, const char *comentarioFilename, const char *contrasenia) {
    int encontrado = 0;
    for (int i = 0; i < cantidad; i++) {
        if (comentarios[i].idComentario == idComentario && strcmp(comentarios[i].password, contrasenia) == 0) {
            encontrado = 1;

            printf("Ingrese la nueva descripcion del comentario: ");
            fflush(stdin);
            fgets(comentarios[i].descripcion, sizeof(comentarios[i].descripcion), stdin);
            if (comentarios[i].descripcion[strlen(comentarios[i].descripcion) - 1] == '\n') {
                comentarios[i].descripcion[strlen(comentarios[i].descripcion) - 1] = '\0';
            }

            do {
                printf("Ingrese la nueva valoracion del libro (0-5): ");
                scanf("%d", &comentarios[i].puntaje);
                getchar();
            } while (comentarios[i].puntaje < 0 || comentarios[i].puntaje > 5);

            guardarComentario(comentarioFilename, comentarios, cantidad);
            printf("Comentario modificado exitosamente.\n");
            break;
        }
    }
    if (!encontrado) {
        printf("Comentario no encontrado o contrasenia incorrecta.\n");
    }
}

void eliminarComentario(stComentario comentarios[], int *cantidad, int idComentario, const char *comentarioFilename, const char *contrasenia) {
    int encontrado = 0;
    for (int i = 0; i < *cantidad; i++) {
        if (comentarios[i].idComentario == idComentario && strcmp(comentarios[i].password, contrasenia) == 0) {
            encontrado = 1;
            for (int j = i; j < *cantidad - 1; j++) {
                comentarios[j] = comentarios[j + 1];
            }
            (*cantidad)--;
            guardarComentario(comentarioFilename, comentarios, *cantidad);
            printf("Comentario eliminado exitosamente.\n");
            break;
        }
    }
    if (!encontrado) {
        printf("Comentario no encontrado o contrasenia incorrecta.\n");
    }
}
    // Código para guardar los comentarios actualizados en el archivo, si es necesario


void calcularPromedioPuntajes(stComentario comentario[], int cantidadComentario, stLibro libros[], int cantidadLibros) {
    // Iterar sobre todos los libros
    for (int i = 0; i < cantidadLibros; i++) {
        if (cantidadComentario > 0) {
            float sumaPuntajes = 0.0;
            int contador = 0;

            // Iterar sobre todos los comentarios
            for (int j = 0; j < cantidadComentario; j++) {
                if (comentario[j].idLibro == libros[i].idLibro && comentario[j].puntaje > 0) {
                    sumaPuntajes += comentario[j].puntaje;
                    contador++;
                }
            }

            // Calcular el promedio si hay comentarios evaluados
            if (contador > 0) {
                libros[i].valoracion = sumaPuntajes / contador;
            }
        }
    }
}

void mostrarLibrosFavoritos(const stFavorito favoritos[], int cantidadFavoritos, const stLibro libros[], int cantidadLibros, int idUsuario) {
    printf("Lista de libros favoritos:\n");
    for (int i = 0; i < cantidadFavoritos; i++) {
        if (favoritos[i].idUsuario == idUsuario) {
            for (int j = 0; j < cantidadLibros; j++) {
                if (libros[j].idLibro == favoritos[i].idLibro) {
                    mostrarLibro(libros[j]);
                    break;
                }
            }
        }
    }
}

void agregarLibroAFavoritos(stFavorito favoritos[], int *cantidadFavoritos, int idUsuario, stLibro libro, int cantLibrosFav) {
    favoritos[*cantidadFavoritos].idUsuario = idUsuario;
    favoritos[*cantidadFavoritos].idLibro = libro.idLibro;
    (*cantidadFavoritos)++;
    cantLibrosFav = cantidadFavoritos;
}

void eliminarLibroDeFavoritos(stFavorito favoritos[], int *cantidadFavoritos, int idUsuario, int idLibro) {
    for (int i = 0; i < *cantidadFavoritos; i++) {
        if (favoritos[i].idUsuario == idUsuario && favoritos[i].idLibro == idLibro) {
            for (int j = i; j < *cantidadFavoritos - 1; j++) {
                favoritos[j] = favoritos[j + 1];
            }
            (*cantidadFavoritos)--;
            break;
        }
    }
}

void guardarFavoritos(const char *filename, stFavorito favoritos[], int cantidadFavoritos) {
    FILE *file = fopen(filename, "wb");
    if (file != NULL) {
        fwrite(favoritos, sizeof(stFavorito), cantidadFavoritos, file);
        fclose(file);
    } else {
        printf("Error al abrir el archivo de favoritos.\n");
    }
}

int cargarFavoritos(const char *filename, stFavorito favoritos[], int maxFavoritos) {
    int cantidad = 0;
    FILE *file = fopen(filename, "rb");
    if (file != NULL) {
        while (fread(&favoritos[cantidad], sizeof(stFavorito), 1, file) > 0 && cantidad < maxFavoritos) {
            cantidad++;
        }
        fclose(file);
    }
    return cantidad;
}
