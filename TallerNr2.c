//2do taller de programacion Anthony Quero
//Nota: Se agregaron las posiciones
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int cantt=0;

typedef struct{
    char nombre[15];
    int notas[3];
    float promedio;
}alumno;

alumno *alum;

void llenar();
void ini_prom();
void calcular_prom();
void bubble(float v[],int t);

int main(){
    FILE *f;
    char aux[20];
    int i,j,tam;

    f=fopen("notas_alumnos.txt","r");

    if(f==NULL){
        printf("No se pudo abrir el fichero\n");
        return 0;
    }else{
        while(!feof(f)){
            fgets(aux,20,f);
            cantt++;
        }
    }

    fclose(f);

    alum=(alumno*)malloc(cantt*sizeof(alumno));
    float pro[cantt];

    llenar();
    ini_prom();
    calcular_prom();

    for(i=0;i<cantt;i++){
        pro[i]=alum[i].promedio;
    }

    tam=sizeof(pro)/sizeof(float);

    bubble(pro,tam);

    j=0;
    int k=0;
    float au=0;
    FILE *s;
    s=fopen("resultados.txt","w");

    fprintf(s,"Resultados: \n");

    while(j<cantt){
        for(i=0;i<cantt;i++){
            if(alum[i].promedio==pro[j]){
                if(alum[i].promedio!=au){
                    au=alum[i].promedio;
                    k++;
                }
                printf("%d ",k);
                printf("%s ",alum[i].nombre);
                printf("%g",alum[i].promedio);
                printf("\n");

                fprintf(s,"En la posicion %d: ",k);
                fprintf(s,"%s ",alum[i].nombre);
                fprintf(s,"con el promedio de %g",alum[i].promedio);
                fprintf(s,"\n");
                j++;

            }
        }
    }

    fclose(s);

    return 0;
}

void llenar(){
    int i;
    FILE *f;

    f=fopen("notas_alumnos.txt","r");

    if(f==NULL){
        printf("Error\n");
    }else{
        for(i=0;i<cantt;i++){
            fscanf(f,"%s",alum[i].nombre);
            fscanf(f,"%d %d %d",&alum[i].notas[0],&alum[i].notas[1],&alum[i].notas[2]);
        }
    }

    fclose(f);
}

void ini_prom(){
    int i;

    for(i=0;i<cantt;i++){
        alum[i].promedio=0;
    }
}

void calcular_prom(){
    int i;

    for(i=0;i<cantt;i++){
        alum[i].promedio=(float)((alum[i].notas[0]+alum[i].notas[1]+alum[i].notas[2])/3);
    }
}

void bubble(float v[],int t){
    int i,j;
    float aux;

    for(i=0;i<t;i++){
        for(j=i+1;j<t;j++){
            if(v[i]<v[j]){
                aux=v[i];
                v[i]=v[j];
                v[j]=aux;
            }
        }
    }
}