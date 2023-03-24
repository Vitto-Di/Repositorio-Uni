//Conversor dolares a euros
#include <stdio.h>
#include <conio.h>

int main(){
    int d;
    float e;

    printf("Ingrese una cantidad entera de dolares.\n");
    scanf("%d",&d);

    e=(d*166.386);

    printf("El equivalente en euros de %d dolares es %0.3f\n",d,e);

    getch();
    return 0;
}