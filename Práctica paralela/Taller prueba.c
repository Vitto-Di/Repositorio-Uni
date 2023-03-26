//BETA 2do taller de prueba
#include <stdio.h>
#include <conio.h>

int inversor();

void cont_3y5();

void cont_3y5(int a,int *c3,int *c5){
    int b;

    do{
        b=a%10;
        if(b==3){
            *c3=*c3+1;
        }
        if(b==5){
            *c5=*c5+1;
        }
        a/=10;
    }while(a!=0);
}

int inversor(int a){
    int b,inv=0;

    do{
        b=a%10;
        inv=inv+b;
        inv*=10;
        a=a/10;
    }while(a!=0);

    return inv/10;
}

int main(){
    int n,i,m,c3=0,c5=0;
    printf("Ingrese cantidad de numeros a analizar\n");

    do{
        scanf("%d",&n);
    }while(n<0);

    for(i=0;i<n;i++){
        
        printf("Ingrese numero %d a analizar\n",i+1);
        scanf("%d",&m);

        if(m>99){
            printf("El numero invertido de %d es %d\n",m,inversor(m));
        }

        cont_3y5(m,&c3,&c5);
    }

    printf("La Cantidad total de 3 ingresados es %d y la de 5 es %d.\n",c3,c5);

    getch();
    return 0;
}