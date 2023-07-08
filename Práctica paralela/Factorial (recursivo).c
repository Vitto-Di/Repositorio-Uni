//Factorial recursivo con validación de letras "indeseadas"
#include <stdio.h>
#include <stdio_ext.h>
#include <stdlib.h>
#include <string.h>

int fact(int a);
void clear();

int main(){
    int n;
    int aux;

    printf("Introduzca el valor deseado\n");

    do{
        aux = scanf("%d",&n);
        __fpurge(stdin);
        system("clear");
        printf("Introduzca el valor deseado\n");
    }while(aux !=1);

    n=fact(n);

    printf("%d\n",n);

    return 0;
}

int fact(int a){

    if(a<=1){
        return a;
    }else{
        a*=fact(a-1);
    }
}

void clear(){
    int aux;
    while(aux = getchar() !='\n');
}