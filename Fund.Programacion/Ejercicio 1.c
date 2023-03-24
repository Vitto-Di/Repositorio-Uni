/*Promedio 3 examenes*/
#include <stdio.h>
#include <conio.h>
#define cons 3

int main (){
    float a,b,c,d;
    printf("Ingrese 3 notas para promediar ");
    scanf("%f %f %f",&a,&b,&c);
    d=(a+b+c)/cons;
    printf("El promedio es: %f.\n",d);
    getch();
    return 0;
}