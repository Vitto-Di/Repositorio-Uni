//Serie de fibbonaci
#include <stdio.h>
#include <conio.h>

int main(){
    int n,a=1,b=0,f,c;

    printf("Ingrese primeros n numeros a calcular:\n");
    scanf("%d",&n);

    for(c=0;c<n;c++){
        f=a+b;
        printf("El numero %d es %d.\n",c+1,f);
        b=a;
        a=f;
    }



    getch();
    return 0;
}