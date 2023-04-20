//Seleccion de operadores con dos numeros
#include <stdio.h>
#include <conio.h>

float divi(int a,int b){
    float c;

    c=(float)a/b;

    return c;
}
int multi(int a,int b){
    int i,acum=0;

    for(i=0;i<b;i++){
        acum+=a;
    }

    return acum;
}

int resta(int a,int b){
    a-=b;

    return a;
}

int suma(int a,int b){
    int c;

    c=a+b;

    return c;
}

int main(){
    int n,m,band;
    char e;
    float resu;

    printf("Calculadora de un solo uso.\n\n");

    do{
        printf("Escoja una operacion: Suma(a), resta(b), multi(c), divi(d).\n\n");
        scanf("%c",&e);
    }while((e!='a')&&(e!='b')&&(e!='c')&&(e!='d'));

    do{
        band=0;
        printf("Ingrese dos numeros para operar\n");
        scanf("%d %d",&n,&m);

        switch(e){
            case 'a':resu=suma(n,m);break;
            case 'b':resu=resta(n,m);break;
            case 'c':resu=multi(n,m);break;
            case 'd':if(m!=0){
                resu=divi(n,m);
            }else{
                printf("La division entre cero no esta definida, ");
                band=1;
        };break;
            default:printf("Deberia ser imposible que usted este leyendo esto\n");
        }
    }while(band==1);

    printf("El resultado de %d operado con %d es: %g\n",n,m,resu);

    getch();
    return 0;
}
