//Base de palabras ingles/español
#include <stdio.h>
#include <conio.h>
#include <string.h>
#define N 50
#define fpurge fflush 

typedef struct{
    char esp[20];
    char eng[20];
    int state;
}word;

word words[N];

void delete(char w[]);
void enter(char esp[],char eng[]);
void inicializar();
void search(char x[],int op);

int main(){
    int n,n2;
    char es[20],en[20],repe[4];

    printf("Traductor de ingles/espa%col con almacenamiento TEMPORAL\n\n",164);

    inicializar();

    do{

    do{
        printf("Que desea hacer?: (1) para a%cadir palabra y (2) para buscar traducion\n",164);
        scanf("%d",&n);
    }while((n!=1)&&(n!=2));

    if(n==1){
        fpurge(stdin);
        printf("Agrege palabra en espa%col\n",164);
        fgets(es,20,stdin);
        delete(es);
        printf("Agregue traduccion a ingles\n");
        fpurge(stdin);
        fgets(en,20,stdin);
        delete(en);

        enter(es,en);
    }else{
        do{
            printf("Quiere buscar de ingles-espa%col(0) o de espa%col-ingles(1)\n",164,164);
            scanf("%d",&n2);
        }while((n2!=0)&&(n2!=1));

        printf("Introduzca la palabra a traducir\n");
        fpurge(stdin);
        fgets(es,20,stdin);
        delete(es);

        search(es,n2);
    }

    printf("Desea volver a usar? (si) o (no)\n");
    fpurge(stdin);
    fgets(repe,4,stdin);
    delete(repe);
    putchar('\n');

    }while(strcmp(repe,"si")==0);

    getch();
    return 0;
}

void delete(char w[]){
    int size;

    size=strlen(w);

    w[size-1]='\0';
}

void enter(char esp[],char eng[]){
    int i;
    int band=0;

    for(i=0;i<N;i++){
        if(words[i].state==0){
            strcpy(words[i].esp,esp);
            strcpy(words[i].eng,eng);
            words[i].state=1;
            band=1;
            break;
        }
    }

    if(band==0){
        printf("Esta llena la memoria\n");
    }
}

void inicializar(){
    int i;

    for(i=0;i<N;i++){
        words[i].state=0;
    }
}

void search(char x[],int op){
    int i,band=0;

    if(op==1){
        for(i=0;i<N;i++){
            if(strcmp(words[i].esp,x)==0){
                printf("La traduccion de %s es %s \n",x,words[i].eng);
                band=1;
                break;
            }
        }
    }else{
        for(i=0;i<N;i++){
            if(strcmp(words[i].eng,x)==0){
                printf("La traduccion de %s es %s \n",x,words[i].esp);
                band=1;
                break;
            }
        }
    }

    if(band==0){
        printf("No se encontro la traduccion en la memoria\n");
    }
}