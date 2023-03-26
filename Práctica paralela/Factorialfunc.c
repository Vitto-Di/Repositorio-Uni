//Test func factorial
#include <stdio.h>
#include <conio.h>

int fact();

int fact(int a){
    int i=1,fact;

    fact=a;
    do{
        fact*=i;
        i++;    
    }while(i<a);

    return fact;
}

int main(){
    int n,sal;

    printf("Ingrese un numero\n");

    do{
    scanf("%d",&n);
    }while(n<0);

    sal=fact(n);

    printf("El factorial de %d es %d.\n",n,sal);

    getch();
    return 0;
}