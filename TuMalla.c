//Taller práctica empresa TuMalla.com
#include <stdio.h>
#include <conio.h>

int main(){

    int cant_mallasb=0,cant_mallast=0,total_clientdescuento=0,total_compras=0,metros_malla,tiempo,i=1;
    float costo_compra=0,ingreso=0,descuento=0;
    char band,tipo;

    printf("Empresa TuMalla.com\n\n");

    printf("Compra de mallas deportivas\n");

    do{

        descuento=0;

        do{
            printf("Introduzca metros a comprar\n");
            scanf("%d",&metros_malla);
            fflush(stdin);
        }while(metros_malla<1);

        do{
            printf("Ingrese tipo de malla a comprar (b para beisbol y t para tenis)\n");
            scanf("%c",&tipo);
            fflush(stdin);
        }while((tipo!='t')&&(tipo!='b'));

        do{
            printf("Ingrese tiempo (en anos) que lleva comprando\n");
            scanf("%d",&tiempo);
        }while(tiempo<1);

        if(tipo=='b'){
            costo_compra=50*metros_malla;
            if(tiempo>5){
                descuento=costo_compra*0.08;
                costo_compra=costo_compra-descuento;
            }
            cant_mallasb++;

        }else{
            costo_compra=80*metros_malla;
            if(tiempo>5){
                descuento=costo_compra*0.06;
                costo_compra=costo_compra-descuento;
            }
            cant_mallast++;
        }

        if(tiempo>15){
            costo_compra=costo_compra-costo_compra*0.30;
            descuento+=costo_compra*0.30;
        }

        ingreso+=costo_compra;
        if(descuento>0){
            total_clientdescuento++;
        }
        total_compras++;

        printf("El costo de la compra del cliente nr %d es:\n",i);
        printf("%g dolares con descuento aplicado\n",costo_compra);
        printf("El descuento es de %g dolares\n",descuento);
        
        printf("\nIngrese 's' para nuevo cliente\n");

        fflush(stdin);

        scanf("%c",&band);
        fflush(stdin);
    
        i++;
      
    }while(band=='s');

    printf("La impresa recibe %g dolares de ingresos\n",ingreso);
    printf("Se vendieron %d mallas de tenis y %d de beisbol\n",cant_mallast,cant_mallasb);

    if(cant_mallasb>cant_mallast){
        printf("Se vendieron mas mallas de baseball\n");
    }else{
        if(cant_mallast>cant_mallasb){
            printf("Se vendieron mas mallas de tenis\n");
        }else{
            printf("Se vendieron la misma cantidad de mallas\n");
        }
    }

    printf("Hubo %d clientes que tuvieron descuento\n",total_clientdescuento);
    printf("Se realizaron %d ventas en el dia de hoy\n",total_compras);

    getch();
    return 0;
}