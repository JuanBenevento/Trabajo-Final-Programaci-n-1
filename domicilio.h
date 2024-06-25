#ifndef DOMICILIO_H_INCLUDED
#define DOMICILIO_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

typedef struct{
    char calle[50];
    int altura;
    int cp;
    char ciudad[100];
    char localidad[50];
    char pais[100];
} stDomicilio;

stDomicilio cargaUnDomicilio();
void mostrarUnDomicilio(stDomicilio domicilio);

#endif // DOMICILIO

