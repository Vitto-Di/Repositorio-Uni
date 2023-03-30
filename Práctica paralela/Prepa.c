//Ejercicio Num 1
#include <stdio.h>
#include <conio.h>

int factorial();
int potencia();

int potencia(int a,int p){
    int i,aux;
    aux=a;

    for(i=1;i<p;i++){
        a*=aux;
    }

    return a;
} 

int factorial(int a){
    int i,aux;
    aux=a;

    for(i=1;i<aux;i++){
        a*=i;
    }

    return a;
}

int main(){
    int n,k;
    float acum=0;
    printf("Ingrese n para calcular sumatoria particular\n");
    do{
        scanf("%d",&n);
    }while(n<2);

    for(k=2;k<=n;k++){

        acum+=((factorial(k))*3*(k+1))/(potencia(k-1,3));
    }
    acum*=5;

    printf("El resultado de la sumatoria es %0.2f\n",acum);










    getch();
    return 0;
}