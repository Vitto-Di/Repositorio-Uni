//Numero malvado
#include <stdio.h>
#include <conio.h>

int conv_bin();

int conv_bin(int a){
    int bin=0,base=1;

    while(a!=0){
        bin=bin+(a%2)*base;
        a/=2;
        base*=10;
    }

    return bin;
}

int main(){
    int n,m,s,num;

    printf("Verificador de ciertos numeros particulares \n\n");

    do{
        m=0;
        printf("Ingrese numero para comprobar malevolencia\n");
        do{
            scanf("%d",&n);
        }while(n<0);
        num=n;

        n=conv_bin(n);

        do{
        m=m+(n%10);
        n=n/10;
        }while(n!=0);

        if(m%2==0){
            printf("El numero %d es un malvado innato\n",num);
        }else{
             printf("Libre de malevolencia\n");
        }

        printf("Ingrese '1' para comprobar otro infame numero:\n");
        scanf("%d",&s);

    }while(s==1);
    
    getch();
    return 0;
}