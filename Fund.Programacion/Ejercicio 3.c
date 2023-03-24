/*Calculo azucar y cafe*/
#include <stdio.h>
#include <conio.h>
#define suggar 3
#define coffe 0.72

int main (){
    float a,kilo_sugg,kilo_coff,sobrante;
    printf("Inserte cantidad en dolares: ");
    scanf("%g",&a);
    kilo_sugg=(a/2)/suggar;
    kilo_coff=(a/3)/coffe;
    sobrante=(a/2)/3;
    printf("Se pueden comprar %g",kilo_sugg);
    printf("kg de azucar\n");
    printf("y %g",kilo_coff);
    printf("kg de cafe\n");
    printf("sobra %g",sobrante);
    printf(" dolares");

    getch ();
    return 0;
}