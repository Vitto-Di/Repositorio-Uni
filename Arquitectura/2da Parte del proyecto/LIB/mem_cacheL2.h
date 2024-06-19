#define Blocks 16

class memory_full2{      //Simula el comportamiento de una memoria de 4 bloques y asociatividad completa
    private:
        int bloque[Blocks];
        cola _cola;     //Historial de Accesos a la memoria
    public:
        memory_full2();
        int acceso(int);
        int memory_get(int);  //Getter
};

memory_full2::memory_full2(){
    for(int i=0;i<Blocks;i++) *(bloque+i) = -1;
}

int memory_full2::acceso(int dir){
    int i,acierto = 0,listo = 0;

    _cola.refresh(dir); // Almacena historial de accesos en la cola

    for(i=0;i<Blocks;i++){
        if(bloque[i] == dir){    //Busca coincidencia
            acierto = 1;break;
        }
    }

    if( !acierto ){

        for(i=0;i<Blocks;i++){
            if( bloque[i] == -1 ){ //Bloque libre
                bloque[i] = dir;
                listo = 1;break;
            } 
        }

        if( !listo ){
            int acceso_menos_reciente;

            acceso_menos_reciente = _cola.desencolar(); //Politica LRU

            for(i=0;i<Blocks;i++){
                if( bloque[i] == acceso_menos_reciente ){  //Aplicacion LRU
                    bloque[i] = dir;break;
                }
            }
        }

    }

    return acierto;
}

int memory_full2::memory_get(int pos){
    return (bloque[pos]);
}