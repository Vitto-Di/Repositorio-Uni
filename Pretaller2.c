//Citas clinicas ABC
#include <stdio.h>
#include <conio.h>

int main(){
    int n,i,edad,ci,dd,mm,aa,cont_m=0,cont_f=0,mayor_edad=0,menor_edad=0,desc_15=0,desc_30=0;
    char sexo;
    printf("Registro de citas medicas para clinica ABC.\n\n");
    printf("ingrese cantidad de pacientes a registrar:\n");

    do{
        scanf("%d",&n);
    }while(n<0);

    for(i=1;i<=n;i++){

        do{
            fflush(stdin);
            printf("Ingrese sexo(M o F),edad y cedula de identidad respectivamente del paciente %d:\n",i);
            scanf("%c %d %d",&sexo,&edad,&ci);
        }while(((sexo!='F')&&(sexo!='M'))||((edad<1)||(ci<1)));

        do{
            printf("Introduzca fecha de nacimiento en formato dd mm aa:\n");
            scanf("%d %d %d",&dd,&mm,&aa);
            fflush(stdin);
        }while(((dd<0)||(mm<0)||(aa<1900))||((dd>31)||(mm>12)||(aa>2023)));

        if(sexo=='M'){
            cont_m++;
        }else{
            cont_f++;
        }

        if(edad>=18){
            mayor_edad++;
        }else{
            menor_edad++;
        }

        if((ci%2==0)&&(sexo=='F')){
            desc_15++;
        }
        if((sexo=='M')&&(edad>60)){
            desc_30++;
        }

    }

    printf("La cantidad de pacientes masculinos es %d y la de femeninos %d\n",cont_m,cont_f);
    printf("La Cantidad de pacientes mayores de edad es %d y de menores %d\n",mayor_edad,menor_edad);
    printf("Numero de feminas con descuento del 15%: es %d\n",desc_15);
    printf("Numero de hombres con descuento del 30%: es %d\n",desc_30);

    getch();
    return 0;
}