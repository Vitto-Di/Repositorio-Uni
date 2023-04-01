//Algoritmo automatizador de tarjetas de boxeo
#include <stdio.h>
#include <conio.h>
#define bolsa 100000

void func(int *n,int *m,int *c1,int *c2,int *b){
    int a;

    printf("\nIngrese ganador del asalto %d (boxeador 1 o 2)\n",*b);
    do{
        scanf("%d",&a);
    }while((a!=1)&&(a!=2));

    if(a==1){
        *n=*n+10;
        *m=*m+9;
        *c1=*c1+1;
    }else{
        *n=*n+9;
        *m=*m+10;
        *c2=*c2+1;
    }
}

int main(){
    int white1=0,white2=0,blue1=0,blue2=0,pink1=0,pink2=0,i,falta1,falta2,contw1=0,contw2=0;
    int contb1=0,contb2=0,contp1=0,contp2=0,w,b,p;
    float band=0,band2=0;

    printf("Sistematica de tarjetas\n\n");

    for(i=1;i<=12;i++){

        falta1=0;
        falta2=0;

        printf("Si el boxeador nr 1 cometio alguna falta coloque 1:\n");
        scanf("%d",&falta1);

        printf("Si el boxeador nr 2 cometio alguna falta coloque 1:\n");
        scanf("%d",&falta2);


         printf("Tarjeta White");
         func(&white1,&white2,&contw1,&contw2,&i);

         printf("Tarjeta Blue");
         func(&blue1,&blue2,&contb1,&contb2,&i);

         printf("Tarjeta Pink");
         func(&pink1,&pink2,&contp1,&contp2,&i);

         if(falta1==1){
            white1-=2;
            blue1-=2;
            pink1-=2;
         }

         if(falta2==1){
            white2-=2;
            blue2-=2;
            pink2-=2;
         }

    }

    if((white1>white2)&&(blue1>blue2)&&(pink1>pink2)){
        printf("El boxeador nr1 gano por desicion unanime \n");
        band=0.10;
    }
    if((white2>white1)&&(blue2>blue1)&&(pink2>pink1)){
        printf("El boxeador nr2 gano por desicion unanime \n");
        band2=0.10;
    }

    if(white1<white2){
        if(blue1>blue2){
            if(pink1>pink2){
                printf("El boxeador nr1 gano por desicion dividida\n");
                band=0.5;
            }else{
                printf("El boxeador nr2 gano por desicion dividida\n");
                band2=0.5;
            }
        }else{
            if(pink1>pink2){
                printf("El boxeador nr 2 gano por desicion dividida\n");
                band2=0.5;
            }
        }
    }else{
        if(blue2>blue1){
            if(pink2>pink1){
                printf("El boxeador nr 2 gano por desicion dividida\n");
                band2=0.5;
            }else{
                printf("El boxeador nr 1 gano por desicion dividida\n");
                band=0.5;
            }
        }else{
            if(pink1<pink2){
                printf("El boxeador nr1 gano por desicion dividida\n");
                band=0.5;
            }
        }
        }

    if((white1==white2)||(blue1==blue2)||(pink1==pink2)){
        if((blue1>blue2)&&(pink1>pink2)){
            printf("El boxeador nr 1 gano por mayoria\n");
            band=0.15;
        }
        if((white1>white2)&&(pink1>pink2)){
            printf("El boxeador nr 1 gano por mayoria\n");
            band=0.15;
        }
        if((blue1>blue2)&&(white1>blue2)){
            printf("El boxeador nr 1 gano por mayoria\n");
            band=0.15;
        }
        
        if((blue1<blue2)&&(pink1<pink2)){
            printf("El boxeador nr 2 gano por mayoria\n");
            band2=0.15;
        }
        if((white1<white2)&&(pink1<pink2)){
            printf("El boxeador nr 2 gano por mayoria\n");
            band2=0.15;
        }
        if((blue1<blue2)&&(white1<blue2)){
            printf("El boxeador nr 2 gano por mayoria\n");
            band2=0.15;
        }
        
        
    }

    printf("El boxeador nr 1 en las siguientes tarjetas tiene el puntaje:\n");
    printf("En la tarjeta blanca:%d, en la tarjeta azul %d y en la tarjeta rosa %d\n",white1,blue1,pink1);

    printf("El boxeador nr 2 en las siguientes tarjetas tiene el puntaje:\n");
    printf("En la tarjeta blanca:%d, en la tarjeta azul %d y en la tarjeta rosa %d\n",white2,blue2,pink2);

    printf("La cantidad de rounds ganados y perdidos se denotan en las siguientes tarjetas respectivamente:\n\n");
    printf("Primer boxeador\n");
    printf("Blanca %d %d, Azul %d %d, Rosa %d %d \n",contw1,12-contw1,contb1,12-contb1,contp1,12-contp1);

    printf("Segundo boxeador\n");
    printf("Blanca %d %d, Azul %d %d, Rosa %d %d \n\n",contw2,12-contw2,contb2,12-contb2,contp2,12-contp2);

    printf("Tarjetas mayor y menor\n");
    if(white1>=white2){
        w=white1;
    }else{
        w=white2;
    }

    if(blue1>=blue2){
        b=blue1;
    }else{
        b=blue2;
    }

    if(pink1>=pink2){
        p=pink1;
    }else{
        p=pink2;
    }

    if(w>b){
        if(w>p){
            printf("La tarjeta blanca es la mayor\n");
            if(b<p){
                printf("La tarjeta menor es la azul\n");
            }else{
                printf("La tarjeta menor es la rosa\n");
            }
        }else{
            printf("La tarjeta rosa es la mayor\n");
            printf("La tarjeta azul es la menor\n");
        }
    }else{
        if(p<w){
            printf("La tarjeta azul es la mayor\n");
            printf("La tarjeta menor es la rosa\n");

        }else{
            if((w!=p)&&(w!=b)){
                printf("La tarjeta blanca es la menor\n");
            }
        }
    }

    if(band!=0){
        printf("\nEl boxeador nr1 se lleva %g dolares\n",bolsa+(bolsa*band));
    }else{
        printf("\nEl boxeador nr1 se lleva %g dolares\n",bolsa-(bolsa*0.40));
    }

    if(band2!=0){
        printf("\nEl boxeador nr2 se lleva %g dolares\n",bolsa+(bolsa*band2));
    }else{
        printf("\nEl boxeador nr2 se lleva %g dolares\n",bolsa-(bolsa*0.40));
    }

    getch();
    return 0;
    }
    







