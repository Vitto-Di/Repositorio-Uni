//Algoritmo verificador de paridad numerica
#include <stdio.h>
#include <conio.h>

void main (){
    int n;
    printf("Ingrese numero para comprobar paridad: ");
    do    
    {
        scanf ("%d",&n);
        if (n<0){
            printf("Numero invalido\n");
        }
    } while (n<0);
    
    if (n%2==0){
        printf("El numero es par");
    }
    else{
        printf("El numero es impar");
    }
    getch ();
}