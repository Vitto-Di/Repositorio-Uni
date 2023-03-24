//ejercicio 1
//Algoritmo que calcula cuantos n numeros son pares,impares,primos y cuentos ceros poseen en total
#include <stdio.h>
#include <conio.h>

int main(){
    int n,i,m,par=0,impar=0,num,cero=0,num2,prim=0,c,band=1;
    //Leer cantidad a comprobar
    do{
        printf("Introduzca cantidad de numeros a comprobar.\n");
        scanf("%d",&n);
    }while(n<0);
    //Procedimientos de comprobacion
    for(i=0;i<n;i++){
        printf("Inserte %d numero a comprobar: \n",i+1);
        scanf("%d",&m);
        //Paridad Numerica
        if(m%2==0){
            par++;
        }else{
            impar++;
        }
        //Auxiliares para contador de Ceros
        num=m;
        num2=m;
        //Contador de ceros
        if(num==0){
            cero++;
        }
        do{
            if(num2!=0){
                num=num%10;
                if(num==0){
                    cero++;
                }
            }
            num2=num2/10;
            num=num2;
        }while(num2!=0);
        //Verificador de Numeros primos
        if(m==2){
            prim++;
        }else{
            if(m>2){
             c=2;
             do{
                band=m%c;
                c++;
             }while((band!=0)&&(c<m));

             if(band!=0){
                prim++;
            }
            }
        }

    }
    //Imprimir resultados obtenidos
    printf("Hay %d numeros pares\n",par);
    printf("Hay %d numeros impares\n",impar);
    printf("hay %d ceros en total\n",cero);
    printf("hay %d numeros primos",prim);





    getch();
    return 0;
}