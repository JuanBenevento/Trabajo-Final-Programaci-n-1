#include "domicilio.h"


stDomicilio cargaUnDomicilio(){

    stDomicilio domicilio;

    char aux [1000];

    printf("Ingrese la calle:  ");
    fflush(stdin);
    gets(domicilio.calle);
//    scanf("%s",&aux);
//    strcpy(domicilio.calle,aux);

    printf("Ingrese la altura: ");
    scanf("%d",&domicilio.altura);

    printf("Ingrese el codigo postal: ");
    scanf("%d",&domicilio.cp);

    printf("Ingrese la ciudad:  ");
    fflush(stdin);
    gets(domicilio.ciudad);

    printf("Ingrese la provincia:  ");
    fflush(stdin);
    gets(domicilio.localidad);

    printf("Ingrese el pais:  ");
    fflush(stdin);
    gets(domicilio.pais);


    return domicilio;

}

void mostrarUnDomicilio(stDomicilio domicilio){


    printf("\nCalle:.........................%s", domicilio.calle);
    printf("\nAltura:........................%d", domicilio.altura);
    printf("\nCodigo Postal:.................%d", domicilio.cp);
    printf("\nCiudad:........................%s", domicilio.ciudad);  //
    printf("\nProvincia:.....................%s", domicilio.localidad);//
    printf("\nPais:..........................%s", domicilio.pais);   //Modificamos el tipo de dato a s ya que habiamos puesto c
    printf("\n");
    printf("\n**********************************************");

}

