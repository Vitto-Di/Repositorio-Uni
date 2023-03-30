//2do ejercicio, no me quedo claro pero eso nunca me detuvo
#include <stdio.h>
#include <conio.h>

int main(){
    int n,i=0;

    printf("Se leera y escribira la secuencia hasta que los dos ultimos numeros sean divisibles entre 5\n");
    printf("Ingrese numero de la secuencia mayor a uno\n");
    do{
        do{
            scanf("%d",&n);
        }while(n<2);

        if((n%5)==0){
            i++;
        }else{
            if(i>0){
                i--;
            }
        }
        printf("%d       :",n);
    }while(i!=2);

    printf("Finalizo\n");



    getch();
    return 0;
}