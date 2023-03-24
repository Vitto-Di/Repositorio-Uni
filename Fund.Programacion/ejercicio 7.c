//Paridad numerica
#include <stdio.h>
#include <conio.h>

int main(){
    int n;

    do{
        printf("Ingrese un numero entero para comprobar paridad\n");
        scanf("%d",&n);
    }while(n<0);

    if(n%2==0){
        printf("el numero es par");
    }else{
        printf("El numero es impar");
    }

    getch();
    return 0;
}