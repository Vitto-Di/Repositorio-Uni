#define NR_BLOCKS 8

typedef struct nodo{    //Estructura de nodo tradiccional
    int valor;
    struct nodo *sig;
}nodo;

class cola{             //Cola especial para almacenar datos
    private:
        nodo *inicio;
        nodo *final;
        int tam;
    public:
        cola();
        void encolar(int);
        int desencolar();
        void vaciar(int);
        void refresh(int);  //Borra todas las anteriores apariciones del elemento antes de ser encolado
        
};

cola::cola(){
    tam = 0;
}

void cola::encolar(int elem){

    if( tam == 0 ){
        nodo *prim;

        prim = new nodo;
        prim->valor = elem;
        prim->sig = NULL;

        inicio = prim;
        final = inicio;
    }else{
        nodo *nuevo;

        nuevo = new nodo;
        nuevo->valor = elem;
        nuevo->sig = NULL;
        final->sig = nuevo;
        final = nuevo;
    }

    tam++;
}

int cola::desencolar(){
    nodo *aux;
    int save=-1;

    if(tam > 0){
        save = inicio->valor;

        aux = inicio;
        inicio = inicio->sig;
        delete aux;
        tam--;
    }

    return save;
}

void cola::vaciar(int elem){
    nodo *aux;
    nodo *aux_ant;

    aux = inicio;
    aux_ant = aux;

    for(;(aux != NULL)&&(tam > 1);){

        if( aux->valor == elem ){
            if(aux == inicio){
                aux = aux->sig;
                inicio = aux;
                delete aux_ant;
            }else{
                if(aux == final) final = aux_ant;
                aux_ant->sig = aux->sig;
                delete aux;
                aux = aux_ant;
            }
            tam--;
        }
        aux_ant = aux;
        aux = aux->sig;
    }

    if( tam == 1){
        if( inicio->valor == elem ){
            delete inicio;
            tam--;
        }
    }
}

void cola::refresh(int elem){

    cola::vaciar(elem);
    cola::encolar(elem);
}

class memory_full{      //Simula el comportamiento de una memoria de 4 bloques y asociatividad completa
    private:
        int bloque[NR_BLOCKS];
        cola _cola;     //Historial de Accesos a la memoria
    public:
        memory_full();
        int acceso(int);
        int memory_get(int);  //Getter
};

memory_full::memory_full(){
    for(int i=0;i<NR_BLOCKS;i++) *(bloque+i) = -1;
}

int memory_full::acceso(int dir){
    int i,acierto = 0,listo = 0;

    _cola.refresh(dir); // Almacena historial de accesos en la cola

    for(i=0;i<NR_BLOCKS;i++){
        if(bloque[i] == dir){    //Busca coincidencia
            acierto = 1;break;
        }
    }

    if( !acierto ){

        for(i=0;i<NR_BLOCKS;i++){
            if( bloque[i] == -1 ){ //Bloque libre
                bloque[i] = dir;
                listo = 1;break;
            } 
        }

        if( !listo ){
            int acceso_menos_reciente;

            acceso_menos_reciente = _cola.desencolar(); //Politica LRU

            for(i=0;i<NR_BLOCKS;i++){
                if( bloque[i] == acceso_menos_reciente ){  //Aplicacion LRU
                    bloque[i] = dir;break;
                }
            }
        }

    }

    return acierto;
}

int memory_full::memory_get(int pos){
    return (bloque[pos]);
}
