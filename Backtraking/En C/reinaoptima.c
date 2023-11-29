#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define N 6

int valor_abs(int n);
bool sig_alt(int vect[], int pos, int fil);
bool n_reinas(int sol[], int colum);
void mostrar_solucion(int sol[]);

int main(){
    int v[N], i ;

    for(i=0;i<N;i++)
        v[i] = 9;
    
    n_reinas(v,0);


    return 0;
}

int valor_abs(int n){

    if(n < 0) n *=-1; 
    return n;
}

bool sig_alt(int vect[], int pos, int fil){

    int i;

    for(i=0;i<N;i++){

        if(vect[i] == fil) return false;

        if( valor_abs(pos-i) == valor_abs(fil-vect[i])) return false;
    }

    return true;
}

bool n_reinas(int sol[], int colum){

    int i = 0,j;
    bool es_valida = false;

    while( (i < N)&&(!es_valida) ){

        es_valida = sig_alt(sol,colum,i);

        if(es_valida){
            sol[colum] = i;
            colum++;

            if(colum == N){

                mostrar_solucion(sol);
            
                return true;
            }else{
                if(!n_reinas(sol,colum)){
                    colum--;
                    sol[colum] = 9;
                    es_valida = false;
                }
            }
        }
        i++;
    }

    return false;
}

void mostrar_solucion(int sol[]){
    int mat[N][N];
                int j,k;

                for(j=0;j<N;j++)
                    for(k=0;k<N;k++) mat[j][k] = 0;

                for(j=0;j<N;j++) mat[sol[j]][j] = 1;

                for(j=0;j<N;j++){
                    for(k=0;k<N;k++){
                        if(mat[j][k] != 0) printf("[%d] ",mat[j][k]);
                        else printf("[ ] ");
                    }
                    putchar('\n');
                }

}

