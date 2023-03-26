//Comprobar si dos numeros son amigos
#include <stdio.h>
#include <conio.h>

int main(){
    int a,b,c,i=1,d=0;

    printf("Ingrese dos numeros\n");
    scanf("%d %d",&a,&b);

    do{
        c=a%i;
        if(c==0){
            d=d+i;
        }
        i++;
    }while(i<a);

    if(d==b){
        i=1;
        d=0;
        do{
            c=b%i;
            if(c==0){
                d+=i;
            }
            i++;
        }while(i<b);
    }


    if(d==a){
        printf("Los numeros son amigos.\n");
    }else{
        printf("Los numeros no son amigos.\n");
    }

    getch();
    return 0;
}