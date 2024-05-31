#include "domicilio.h"


stDomicilio cargaUnDomicilio(){

    stDomicilio domicilio;

    char aux [100];

    printf("\n Ingrese la calle:  ");
    fflush(stdin);
    scanf("%s",aux);
    strcpy(domicilio.calle,aux);

    printf("\n Ingrese la altura: ");
    scanf("%d",&domicilio.altura);

    printf("\n Ingrese el codigo postal: ");
    scanf("%d",&domicilio.cp);

    printf("\n Ingrese la ciudad:  ");
    fflush(stdin);
    scanf("%s",aux);
    strcpy(domicilio.ciudad,aux);

    printf("\n Ingrese la provincia:  ");
    fflush(stdin);
    scanf("%s",aux);
    strcpy(domicilio.localidad,aux);

    printf("\n Ingrese el pais:  ");
    fflush(stdin);
    scanf("%s",aux);
    strcpy(domicilio.pais,aux);

    return domicilio;

}

void mostrarUnDomicilio(stDomicilio domicilio){

    printf("\n**********************************************");
    printf("\n");
    printf("\nCalle:..................%c", domicilio.calle);
    printf("\nAltura:.................%d", domicilio.altura);
    printf("\nCodigo Postal:..........%d", domicilio.cp);
    printf("\nCiudad:.................%c", domicilio.ciudad);
    printf("\nProvincia:..............%c", domicilio.localidad);
    printf("\nPais:...................%c", domicilio.pais);
    printf("\n");
    printf("\n**********************************************");

}
