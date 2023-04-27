//Sumas de dos matrices recibidas por teclado, con uso de funciones 27/04/23
#include <stdio.h>
#include <conio.h>

#define E 3

void intro_matri(int m[][E]);
void suma_matri(int m[][E],int m2[][E]);
void print_matri(int m[][E]);

int main(){
    int matri[E][E],matri2[E][E];

    printf("Suma de dos matrices cuadradas de enteros\n\n");

    printf("Ingrese valores para la 1ra matriz\n");

    intro_matri(matri);

    printf("\nIngrese valores para la 2da matriz\n");
    
    intro_matri(matri2);

    suma_matri(matri,matri2);

    printf("\nLa matriz resultante es la siguiente:\n");

    print_matri(matri2);


    getch();
    return 0;
}

void intro_matri(int m[][E]){
    auto int i,j;

    for(i=0;i<E;i++){
        for(j=0;j<E;j++){
            printf("Introduzca valor entero en la posicion [%d][%d]\n",i+1,j+1);
            scanf("%d",&m[i][j]);
        }
    }
}

void suma_matri(int m[][E],int m2[][E]){
    int i,j;

    for(i=0;i<E;i++){
        for(j=0;j<E;j++){
            m2[i][j]=m[i][j]+m2[i][j];
        }
    }
}

void print_matri(int m[][E]){
    int i,j;

    for(i=0;i<E;i++){
        for(j=0;j<E;j++){
            printf("[%d] ",m[i][j]);
        }
        putchar('\n');
    }
}