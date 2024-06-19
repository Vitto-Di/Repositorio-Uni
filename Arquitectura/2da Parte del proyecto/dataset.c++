// Alumno de Arquitectura y Diseño del computador Anthony Quero Di Nora

#include <iostream>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/mman.h>

#include "LIB/mem_cache.h"
#include "LIB/mem_cacheL2.h"

#define FILE_NAME ("rockyou.txt")
#define HIT 1

using namespace std;

int main(){
    int fd;
    char *addr;
    struct stat statbf;
    memory_full cacheL1;  // Cache completamente asociativa de 8 bloques ( 1 palabra por bloque)
    memory_full2 cacheL2; // 16 bloques

    fd = open( FILE_NAME , O_RDONLY ); // Obtiene el file descriptor del fichero 

    if( fd == -1 ){
        cout << "No se pudo devolver el descriptor de archivo"<<endl;
        exit(1);
    }

    if( fstat( fd , &statbf ) == -1 ){  // Almacena datos de la estructura en statbf
        cout << "Error al intentar obtener informacion de la estructura de datos."<<endl;
        exit(1);
    }

    addr = (char*) mmap( NULL , statbf.st_size, PROT_READ, MAP_PRIVATE, fd, 0);  // Mapea fichero en memoria

    if( addr == MAP_FAILED ){
        cout << "Hubo un error al mapear el fichero en memoria"<<endl; exit(1);
    }

    unsigned int hits = 0;
    double tasa_a = 0.0;

    system("clear");

    for( size_t i = 0 ; i < statbf.st_size ; i++ ){  // Recorre byte por byte (Caracter por caracter)
        int aux;
        double pc; // Para mostrar porcentaje actual del proceso

        aux = cacheL1.acceso( *(addr + i) ); // Acceso a la cache con la dir. de byte actual
        if ( aux == HIT ) 
            hits++;
        else{
            aux = cacheL2.acceso( *(addr + i) );  // Acceso a L2 si L1 no es exitosa
            if ( aux == HIT ) hits++; 
        }

        pc = ( (double)i/statbf.st_size ) * 100;
        cout << "\rProcesando %"<< pc <<"         ";
    }
    cout << "Press enter"<<endl;
    cin.ignore();  // Press enter
    system("clear");

    tasa_a = (double)hits/statbf.st_size ;
    tasa_a*=100;

    //cout << hits << endl;
    cout << "La tasa de aciertos es de %" << tasa_a << endl;

    close(fd);  // Cierra File descriptor

    return 0;
}