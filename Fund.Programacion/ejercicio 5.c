/*Cambio variables*/
#include <stdio.h>
#include <conio.h>

int main (){
    int v1,v2,aux;
    printf("ingrese dos numeros enteros para intercambio :");
    scanf("%d %d",&v1,&v2);
    printf("v1 vale: %d, v2 vale: %d.\n",v1,v2);
    aux=v1;
    v1=v2;
    v2=aux;
    printf("Ahora v1 vale: %d y v2 vale: %d",v1,v2);

    getch();
    return 0;

}