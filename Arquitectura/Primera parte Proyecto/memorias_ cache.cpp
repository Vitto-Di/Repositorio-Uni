#include <iostream>
#include <fstream>

using namespace std;

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


class memory_2way{       //Simula el comportamiento de una memoria de 2 vias y 4 bloques
    private:            //Atributos
        int bloque[4];
        int access_rec0,access_rec1;

    public:             //Métodos

        memory_2way(); //Constructor
        int acceso(int dir);
        void mostrar();
        int memory_get(int);
};

memory_2way::memory_2way(){
    int i;

    for(i=0;i<4;i++) *(bloque+i) = -1; 
}

int memory_2way::acceso(int dir){
    int i,listo=0,conjunto,acierto = 0;

    conjunto = dir % 2;

    if(conjunto == 0){ // bloque 0,1

        for(i=0;i<2;i++){
            if(bloque[i] == dir){
                acierto = 1;
                access_rec0 = dir;break;
            }
        }

        if(!acierto){

            for(i=0;i<2;i++){  // Busca espacio libre
                if(bloque[i] == -1){
                    bloque[i] = dir;
                    access_rec0 = dir;
                    listo = 1;break;
                }
            }

            if(!listo){ //Espacios llenos

                for(i=0;i<2;i++){
                    if(bloque[i] != access_rec0){
                        bloque[i] = dir;
                        access_rec0 = dir;
                        break;
                    }
                }
            }

        }


    }else{  //Bloque 2,3

        for(i=2;i<4;i++){
            if(bloque[i] == dir){
                acierto = 1;
                access_rec1 = dir;break;
            } 
        }

        if(!acierto){

            for(i=2;i<4;i++){  // Busca espacio libre
                if(bloque[i] == -1){
                    bloque[i] = dir;
                    access_rec1 = dir;
                    listo = 1;break;
                }
            }

            if(!listo){ //Espacios llenos

                for(i=2;i<4;i++){
                    if(bloque[i] != access_rec1){
                        bloque[i] = dir;
                        access_rec1 = dir;
                        break;
                    }
                }
            }        

        }

    }

    return acierto; 

}

void memory_2way::mostrar(){
    int i;

    for(i=0;i<4;i++) cout<<*(bloque+i)<<" ";
    cout<<endl;
}

int memory_2way::memory_get(int pos){ //Getter de la memoria

    return (bloque[pos]);
}

class memory_full{      //Simula el comportamiento de una memoria de 4 bloques y asociatividad completa
    private:
        int bloque[4];
        cola _cola;     //Historial de Accesos a la memoria
    public:
        memory_full();
        int acceso(int);
        int memory_get(int);  //Getter
};

memory_full::memory_full(){
    for(int i=0;i<4;i++) *(bloque+i) = -1;
}

int memory_full::acceso(int dir){
    int i,acierto = 0,listo = 0;

    _cola.refresh(dir); // Almacena historial de accesos en la cola

    for(i=0;i<4;i++){
        if(bloque[i] == dir){    //Busca coincidencia
            acierto = 1;break;
        }
    }

    if( !acierto ){

        for(i=0;i<4;i++){
            if( bloque[i] == -1 ){ //Bloque libre
                bloque[i] = dir;
                listo = 1;break;
            } 
        }

        if( !listo ){
            int acceso_menos_reciente;

            acceso_menos_reciente = _cola.desencolar(); //Politica LRU

            for(i=0;i<4;i++){
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

void ini_mat(int mat [][6],int filas);  //Inicializa matriz para evitar errores
void corresp_directa(int mat [][6],int dir[],int filas);
void asociativa_conj(int dir[],int filas);
void Asociativa_completa(int dir[],int filas);

int main(){
    ifstream arch_in;       //Archivo de entrada
    int direcciones[100];   //Conjunto de direcciones leidas
    string name;                

    system("clear");

    cout<<"Ingrese nombre del archivo de entrada: ";
    getline(cin,name);

    arch_in.open(name.c_str(),ios::in);

    if( arch_in.fail() ){
        cout<<"No se ha encontrado"<<endl;
        exit(1);
    }

    int i = -1;
    while( !arch_in.eof() ){  //Lee direcciones hasta el EOF
        i++;
        arch_in>>*(direcciones+i);
    }

    int matriz[i][6];

    ini_mat(matriz,i);

    arch_in.close();  //Cierra archivo


    //Se llaman a los 3 métodos
    corresp_directa(matriz,direcciones,i);
    asociativa_conj(direcciones,i);
    Asociativa_completa(direcciones,i);

    cout<<"Se ha leido correctamente "<<i<<" direcciones y se ha generado un archivo de salida"<<endl;
    cout<<"\"salida.out\""<<endl;


    return 0;
}

void ini_mat(int mat [][6],int filas){
    int i,j;

    for(i=0;i<filas;i++){
        for(j=0;j<6;j++){
            mat[i][j] = -1;
        }
    }
}

void corresp_directa(int mat [][6],int dir[],int filas){
    int i,j,bloque;
    int aux;

    for(i=0;i < filas;i++){
        bloque = (dir[i] % 4) + 2; //Se obtiene la dir. del bloque correspondiente y se desplaza para adaptarse al arreglo
        mat[i][0] = dir[i];

        if( mat[i][bloque] == dir[i])
            mat[i][1] = 1;
        else
            mat[i][1] = 0;
        

        aux = dir[i];

        for(j=i;j<filas;j++)
            mat[j][bloque] = aux;
    }


    ofstream arch_out;  //Se crea archivo de salida

    arch_out.open("salida.out",ios::out);

    if( arch_out.fail() ) cout<<"Ha fallado"<<endl, exit(1);

    arch_out<<"### Correspondencia Directa ###"<<endl;

    arch_out<<"                       |         |Contenido de los bloques de cache"<<endl;
    arch_out<<"  Dir. del bloque      | Acierto |       despúes de cada acceso "<<endl;
    arch_out<<" de memoria accedido   | ó Fallo |    0      1       2       3    "<<endl;

    for(i=0;i<filas;i++){
        arch_out<<"\t\t  "<<mat[i][0]<<"\t\t";
        
        if(mat[i][1] == 1)
            arch_out<<"\t\t  Acierto    ";
        else 
            arch_out<<"\t\t  Fallo\t     ";

        for(j=2;j<6;j++){
            if(mat[i][j] != -1){
                arch_out<<"M["<<mat[i][j]<<"]\t";
            }else{
                arch_out<<"\t    ";
            }
        }

        arch_out<<endl;
    }

    arch_out.close();  //Se cierra
}

void asociativa_conj(int dir[],int filas){
    memory_2way mem_2way;
    int i,j,aux;
    ofstream arch_out;

    arch_out.open("salida.out",ios::app);

    if( arch_out.fail() ) cout<<"Ha fallado"<<endl, exit(1);

    arch_out<<"\n### Asociativa por conjuntos (2 vías) ###"<<endl;
    arch_out<<"                       |         |Contenido de los bloques de cache"<<endl;
    arch_out<<"  Dir. del bloque      | Acierto |       despúes de cada acceso "<<endl;
    arch_out<<" de memoria accedido   | ó Fallo |conjunto 0|conjunto 0|conjunto 1|conjunto 1|"<<endl;

    for(i=0;i<filas;i++){

        arch_out<<"\t \t  "<<dir[i]<<"\t \t \t \t  ";

        ( mem_2way.acceso(dir[i]) )?(arch_out<<"Acierto    "):(arch_out<<"Fallo      ");

        for(j=0;j<4;j++){
            aux = mem_2way.memory_get(j);

            if(aux == -1)
                arch_out<<"M[ ]       ";
            else
                arch_out<<"M["<<aux<<"]       ";
            
        }
        arch_out<<endl;
    }

    arch_out.close();
}

void Asociativa_completa(int dir[],int filas){
    memory_full mem_acesso_completo;
    int i,j,aux;

    ofstream arch_out;

    arch_out.open("salida.out",ios::app);

    if( arch_out.fail() ) cout<<"Ha fallado"<<endl, exit(1);

    arch_out<<"\n### Completamente Asociativa ###"<<endl;
    arch_out<<"                       |         |Contenido de los bloques de cache"<<endl;
    arch_out<<"  Dir. del bloque      | Acierto |       despúes de cada acceso "<<endl;
    arch_out<<" de memoria accedido   | ó Fallo | Bloque 0 | Bloque 1 | Bloque 2 | Bloque 3 |"<<endl;

    for(i=0;i<filas;i++){

        arch_out<<"\t \t  "<<dir[i]<<"\t \t \t \t  ";

        ( mem_acesso_completo.acceso(dir[i]) )?(arch_out<<"Acierto    "):(arch_out<<"Fallo      ");

        for(j=0;j<4;j++){
            aux = mem_acesso_completo.memory_get(j);

            if(aux == -1)
                arch_out<<"M[ ]       ";
            else
                arch_out<<"M["<<aux<<"]       ";
            
        }
        arch_out<<endl;
    }

    arch_out.close();
}