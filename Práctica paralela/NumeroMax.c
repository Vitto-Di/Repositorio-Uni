//Numero Maximo y minimo de 3
#include <stdio.h>
#include <conio.h>

int main (){
    int a,b,c,r;
    do{
        printf("Ingrese 3 numeros para comparacion.\n");
        do{
    scanf("%d %d %d",&a,&b,&c);
    }while(((a)||(b)||(c))=="%d");
    if ((a>b)&&(a>c)){
        printf("%d es mayor.\n",a);
        if (c<b){
            printf("%d es menor",c);
        }
        else{
            printf("%d es menor",b);
        }
    }
    else{
        if ((b>a)&&(b>c)){
            printf("%d es mayor.\n",b);
            if (c<a){
                printf("%d es menor",c);    
            }
            else{
                printf("%d es menor",a);
            }
        }
        else{
            printf("%d es mayor\n",c);
            if(a<b){
            printf("%d es menor",a);
            }
            else
            printf("%d es menor",b);
        }    
    }
    printf("\nSi quiere volver a usar el programa escriba 1.\n");
    scanf("%d",&r);
    }while (r==1);

    getch ();
    return 0;
}
