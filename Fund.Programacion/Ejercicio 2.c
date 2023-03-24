/*Volumen de un cubo*/
#include <stdio.h>
#include <conio.h>

int main (){
    float a;
    printf("Ingrese arista del cubo para calcular el volumen ");
    scanf("%g",&a);
    a=a*a*a;
    printf("El volumen es: %g.\n",a);

    getch ();
    return 0;
}