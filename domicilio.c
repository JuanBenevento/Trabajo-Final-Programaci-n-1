#include "domicilio.h"


stDomicilio cargaUnDomicilio(){

    stDomicilio domicilio;

    char aux [100];

    printf("\n Ingrese la calle:  ");
    fflush(stdin);
    gets(domicilio.calle);
//    scanf("%s",&aux);
//    strcpy(domicilio.calle,aux);

    printf("\n Ingrese la altura: ");
    scanf("%d",&domicilio.altura);

    printf("\n Ingrese el codigo postal: ");
    scanf("%d",&domicilio.cp);

    printf("\n Ingrese la ciudad:  ");
    fflush(stdin);
    scanf("%s",&aux);
    strcpy(domicilio.ciudad,aux);

    printf("\n Ingrese la provincia:  ");
    fflush(stdin);
    scanf("%s",&aux);
    strcpy(domicilio.localidad,aux);

    printf("\n Ingrese el pais:  ");
    fflush(stdin);
    scanf("%s",&aux);
    strcpy(domicilio.pais,aux);

    return domicilio;

}

void mostrarUnDomicilio(stDomicilio domicilio){

    printf("\n**********************************************");
    printf("\n");
    printf("\nCalle:..................%s", domicilio.calle);
    printf("\nAltura:.................%d", domicilio.altura);
    printf("\nCodigo Postal:..........%d", domicilio.cp);
    printf("\nCiudad:.................%s", domicilio.ciudad);  //
    printf("\nProvincia:..............%s", domicilio.localidad);//
    printf("\nPais:...................%s", domicilio.pais);   //Modificamos el tipo de dato a s ya que habiamos puesto c
    printf("\n");
    printf("\n**********************************************");

}
