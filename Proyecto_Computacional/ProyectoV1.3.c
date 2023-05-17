#include <stdio.h>
#include <ctype.h>
#include <stdio_ext.h>
#include <stdlib.h>
#include <string.h>
//Definicion de constantes
#define H 7
#define V 50
#define N 30
//Definicion variables globales.
int buf;
static int cant_t;//cantidad de trabajadores de "trabajadores.in"

typedef struct{//estructura global con datos del fichero principal(Todos los datos)
    int ci;
    char nombre[N];
    char apellido[N];
    char departamento[N];
    char cargo[N];
    char fecha[10];
    int sueldo;
}workers;

workers *worker;//Declaracion de vector dinamico de estructuras

//Declaración de prototipos:
char salid(char s);
char salif(char s);
void buscar_depa(char dep[]);
void buscar_cargo(char v[]);
void llenar();
void layout(char m[H][V]);
void mostrar_layout(char m[H][V]);
char salir(char s);
void menu();
int CharCheck(char a, int dig, int b);
int modificar();
void cicheck(char a[],int* band,int* s);
void punterofichero(int a,FILE* b);
void escritorarchivo(int i,FILE* p);
int strcheck(char a[]);
void Ingresar();
int cicheck2(int a);
void vaciar(char a[]);
int veri(int ci);

int main(){
    //Inicializar estructuras    
    FILE *fichero;
    char aux[120];
    int i;

    fichero=fopen("Trabajadores.in","r");

    if(fichero==NULL){
        printf("No se pudo abrir fichero\n");
        return 0;
    }else{
        for(i=0;!feof(fichero);i++){
            fgets(aux,120,fichero);
        }
        cant_t=i;

        fclose(fichero);

        worker=(workers*)malloc(cant_t*sizeof(workers));

        llenar();
    }
//Fin de asignaciones de estructuras
    char vista[H][V]; //Matriz usada para decorar.
    char sal,op;
    int chk,opINT,temp;
    layout(vista); //llenado de la matriz de decoracion (la que dice MENU).
    while(1){ //El while jamas terminará, Solo saldrá con un break o un return.
        chk=1; //se pone 1 para los casos del if.
        opINT=0;
        do{
            buf=0;
            system("clear"); //Limpiado de la terminal.
            mostrar_layout(vista); //Muestra la matriz antes llenada.
            menu(); //Muestra las opciones del menú.
            if(chk){
                printf("Elija su opción: "); //Se pide opción.
                scanf("%c",&op);
                chk=0; //Se vuelve 0, para que al repetir no se cumpla condicion.
                temp=CharCheck(op,1,1); //Funcion para chequear caracteres
                if(temp){
                    opINT=op-'0'; //convierte el caracter en entero.
                }
                else{
                    continue;
                }
            }
            else{ //Aqui hace lo mismo que arriba pero con el mensaje de error.
                printf("Opción ingresada inválida. Intentelo de nuevo: ");
                scanf("%c",&op);
                temp=CharCheck(op,1,1);
                if(temp){
                    opINT=op-'0';
                }
                else{
                    continue;
                }
            }
        }while((opINT<1)||(opINT>5)); //Se repetirá mientras el usuario ponga erroneos resulados
        switch(opINT){ //Depende del valor anterior, escoge la opcion. NOTA: La unica forma de salir de el programa es con el comando SALIR
            case 1:
                Ingresar();
                break;
            case 2:
                sal=salid(sal);
                break;
            case 3:
                modificar();
                break;
            case 4:
                sal=salif(sal);
                break;
            case 5:
                sal=salir(sal); //Llama a la funcion salir, que retorna caracter
                if(sal=='S'){ //Si el usuario escogió S (si), sale de el programa
                    return 0;
                }
                break;
        }
    }
}
/*FUNCIONES POR CONTIN*/
void layout(char m[H][V]){ //Funcion de llenado de matriz de decoración (MENU)
    int i,j;
    char *ptm=&m[3][(V/2)-5];
    for(i=0;i<H;i++){
        for(j=0;j<V;j++){
            if((i==0)||(i==(H-1))){
                m[i][j]='#';
            }
            else if ((j==0)||(j==(V-1))){
                m[i][j]='#';
            }
            else{
                m[i][j]=' ';
            }
        }
    }
    memcpy(ptm,"SYSTEM MENU",11);
}
void mostrar_layout(char m[H][V]){ //Función de mostrado de matriz, solo la muestra
    int i,j;
    for(i=0;i<H;i++){
        for(j=0;j<V;j++){
            printf("%c",m[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}
char salir(char s){ //Función de salir
    int aux;
    system("clear"); //Limpia terminal
    printf("\n\t Estas seguro que quiere salir? (S/N): "); //Pregunta al usuario y toma valor
    scanf("%c",&s);
    aux=CharCheck(s,1,2);
    s=toupper(s); //Pone en mayusculas el valor tomado
    while(((s!='S')&&(s!='N'))||(aux==0)){
        system("clear");
        printf("\n\tValor ingresado inválido, vuelva a intentarlo.\n\tEstas seguro que quiere salir? (S/N): ");
        scanf("%c",&s);
        aux=CharCheck(s,1,2);
        s=toupper(s);
    }
    return s;
}
void menu(){ //Funcion de imprimir Menu
    printf("¡Bienvenido al sistema de Control de personal!\n\n");
    printf("Elija que desea hacer:\n");
    printf("\t(1) - Ingresar nuevos trabajadores.\n");
    printf("\t(2) - Consultar empleados.\n");
    printf("\t(3) - Modificar empleados.\n");
    printf("\t(4) - Eliminar de Nomina y despedir empleado.\n");
    printf("\t(5) - Salir.\n\n");
}
int CharCheck(char a, int dig, int b){ //Funcion para chequear un caracter
    buf=0;
    if(isspace(a)||iscntrl(a)){ //Si es un espacio o un caracter de control
        __fpurge(stdin);
        return 0;
    }
    else{
        while(getchar()!='\n'){buf++;}; //Limpia el buffer y lo cuenta
        if(buf>(dig-1)){ //Depende de la cantidad de digitos especificada, continua o no.
            return 0;
        }
        else if(b==1){ //Si Se escoge '1' (digito), se comprueba en un caracter digito.
            if(!isdigit(a)){
                return 0;
            }
            else{
                return 1;
            }
        }
        else if(b==2){ //Si se escoge '2' (alfabetico), se comprueba en un caracter alfabetico.
            if(!isalpha(a)){
                return 0;
            }
            else{
                return 1;
            }
        }
    }
}
int modificar(){
    char ci[11],s,nomb[N];
    unsigned int ciINT,op;
    int sal=0,check=1,aux,i,numb,dep,car,dd,mm,aa;
    FILE *p;
    do{
        do{
            system("clear");
            printf("\n\tModificador de Trabajadores.\n\n");
            if(check==0){
                printf("ERROR: Intentelo de nuevo, por favor: \n\n");
            }
            printf("Ingrese la cédula (para volver al menu, ingrese 0): ");
            fgets(ci,10,stdin);
            __fpurge(stdin);
            cicheck(ci,&check,&sal);
            if(sal){
                return 0;
            }
        }while(check==0);
        ciINT=atoi(ci);
        system("clear");
        for(i=0;(i<cant_t)&&(check);i++){
            if(ciINT==worker[i].ci){
                check=0;
                numb=i;
                printf("\n\tEl trabajador a Modificar es el siguiente: \n");
                printf("\n\tEl trabajador se llama %s %s\n",worker[i].nombre,worker[i].apellido);
                printf("\tTrabaja en el departamento de %s con el cargo de %s\n",worker[i].departamento,worker[i].cargo);
                printf("\tTiene %d de sueldo devengado\n",worker[i].sueldo);
                printf("\tIngreso en la fecha %s \n",worker[i].fecha);
            }
        }
        i--;
        if(check==0){
            printf("\nEliga lo que desea modificar: \n");
            printf("\n\t(1) Nombre\n\t(2) Apellido\n\t(3) Departamento\n\t(4) Cargo\n\t(5) Fecha de Ingreso\n\t(6) Sueldo\n");
            printf("\nElije: ");
            scanf("%u",&op);
            __fpurge(stdin);
            while((op<1)||(op>6)){
                printf("ERROR: Intentelo de nuevo.\n");
                printf("Elije: ");
                scanf("%u",&op);
                __fpurge(stdin);
            }
            p=fopen("Trabajadores.in","r+");
            if(p==NULL){
                printf("ERROR: No se pudo abrir el fichero.\n");
                return 0;
            }
            check=1;
            switch(op){
                case 1:
                    do{
                        system("clear");
                        if(check==0){
                            printf("ERROR: Nombre ingresado inválido o muy largo.\n\n");
                        }
                        printf("Ingrese el Nuevo nombre de el trabajador: ");
                        fgets(worker[i].nombre,N,stdin);
                        __fpurge(stdin);
                        check=strcheck(worker[i].nombre);
                    }while(check==0);
                    check=1;
                    escritorarchivo(i,p);
                    printf("\nEl Trabajador se llama ahora %s\n",worker[numb].nombre);
                    break;
                case 2:
                    do{
                        system("clear");
                        if(check==0){
                            printf("ERROR: Apellido ingresado inválido o muy largo.\n\n");
                        }
                        printf("Ingrese el Nuevo apellido de el trabajador: ");
                        fgets(worker[i].apellido,N,stdin);
                        __fpurge(stdin);
                        check=strcheck(worker[i].apellido);
                    }while(check==0);
                    check=1;
                    escritorarchivo(i,p);
                    printf("\nEl Trabajador se apellida ahora %s\n",worker[numb].apellido);
                    break;
                case 3:
                    do{
                        system("clear");
                        if(check==0){
                            printf("ERROR: Elemento ingresado inválido o muy largo.\n\n");
                        }
                        printf("(1) RRHH\n(2) Consultoría\n(3) Diseño\n(4) Producción\n(5) Calidad\n(6) Distribución\n\n");
                        printf("Ingrese el Número correspondiente al Nuevo Departamento de el trabajador: ");
                        scanf("%d",&dep);
                        __fpurge(stdin);
                        check=0;
                    }while((dep<1)||(dep>6));
                    check=1;
                    switch(dep){
                        case 1:
                            strcpy(worker[i].departamento,"RRHH");
                            break;
                        case 2:
                            strcpy(worker[i].departamento,"Consultoria");
                            break;
                        case 3:
                            strcpy(worker[i].departamento,"Diseño");
                            break;
                        case 4:
                            strcpy(worker[i].departamento,"Produccion");
                            break;
                        case 5:
                            strcpy(worker[i].departamento,"Calidad");
                            break;
                        case 6:
                            strcpy(worker[i].departamento,"Distribucion");
                            break;
                    }
                    escritorarchivo(i,p);
                    printf("\nEl Trabajador Pertenece ahora al departamento %s\n",worker[numb].departamento);
                    break;
                case 4:
                    do{
                        system("clear");
                        if(check==0){
                            printf("ERROR: Elemento ingresado inválido o muy largo.\n\n");
                        }
                        printf("(1) Gerente\n(2) Supervisor\n(3) Analista\n(4) Diseñador\n(5) Desarrollador\n(6) Auditor\n\n");
                        printf("Ingrese el Número correspondiente al Nuevo cargo de el trabajador: ");
                        scanf("%d",&car);
                        __fpurge(stdin);
                        check=0;
                    }while((car<1)||(car>6));
                    check=1;
                    switch(car){
                        case 1:
                            strcpy(worker[i].cargo,"Gerente");
                           break;
                        case 2:
                            strcpy(worker[i].cargo,"Supervisor");
                            break;
                        case 3:
                            strcpy(worker[i].cargo,"Analista");
                            break;
                        case 4:
                            strcpy(worker[i].cargo,"Diseñador");
                            break;
                        case 5:
                            strcpy(worker[i].cargo,"Desarrollador");
                            break;
                        case 6:
                            strcpy(worker[i].cargo,"Auditor");
                            break;
                    }
                    escritorarchivo(i,p);
                    printf("\nEl Trabajador tiene ahora el cargo de %s\n",worker[numb].cargo);
                    break;
                case 5:
                    do{
                        system("clear");
                        if(check==0){
                            printf("ERROR: Fecha ingresada inválida.\n\n");
                        }
                        printf("-- Ingrese la nueva fecha de ingreso de el trabajador (dia/mes/año)--\n\n");
                        printf("\tIngrese dia:");
                        scanf("%d",&dd);
                        __fpurge(stdin);
                        printf("\tIngrese mes:");
                        scanf("%d",&mm);
                        __fpurge(stdin);
                        printf("\tIngrese año:");
                        scanf("%d",&aa);
                        __fpurge(stdin);
                        check=0;
                    }while((dd<1||dd>31)||(mm<1||mm>12)||(aa<1900||aa>3000));
                    check=1;
                    sprintf(worker[i].fecha,"%d/%d/%d",dd,mm,aa);
                    escritorarchivo(i,p);
                    printf("\nAhora la fecha de ingreso del trabajador es %s\n",worker[numb].fecha);
                    break;
                case 6:
                    do{
                        system("clear");
                        if(check==0){
                            printf("ERROR: No puede haber salario negativo ó 0.\n\n");
                        }
                        check=1;
                        printf("Ingrese el nuevo salario de el trabajador: ");
                        scanf("%d",&worker[i].sueldo);
                        __fpurge(stdin);
                        if(worker[i].sueldo<1){
                            check=0;
                        }
                    }while(check==0);
                    check=1;
                    escritorarchivo(i,p);
                    printf("\nEl Trabajador ingresado ahora suelda $%d\n",worker[numb].sueldo);
                    break;
            }
            fclose(p);
        }
        else{
            system("clear");
            printf("\nLa CI indicada no está asociada a ningun trabajador de la empresa!\n");
        }
        printf("\n\tOperacion terminada\n");
        printf("\nQuiere volver a modificar a otro trabajador? (S/N): ");
        scanf("%c",&s);
        s=toupper(s);
        aux=CharCheck(s,1,2);
        while(((s!='S')&&(s!='N'))||(aux==0)){
            system("clear");
            printf("\n\tValor ingresado inválido, vuelva a intentarlo.\n\tQuiere volver a modificar a otro trabajador? (S/N): ");
            scanf("%c",&s);
            aux=CharCheck(s,1,2);
            s=toupper(s);
        }
    }while(s=='S');
    return 0;
}
void cicheck(char a[],int* band,int* s){ //Funcion para chequear que una cédula sea válida (para este caso, la cantidad de digitos fija es 7)
    int i,tam;
    *band=1;
    tam=strlen(a);
    if((tam==8)||(tam==9)){
        a[tam-1]='\0';
        for(i=0;i<(tam-1);i++){
            if(!isdigit(a[i])){
                *band=0;
            }
        }
    }
    else if(tam==2){
        if(isdigit(a[0])){
            if(atoi(a)){
                *band=0;
            }
            else{
                *s=1;
            }
        }
        else{
            *band=0;
        }
    }
    else{
        *band=0;
    }
}
void punterofichero(int a,FILE* b){ //Mueve el puntero del fichero a la posicion deseada
    int band=1,i;
    char aux[100];
    for(i=0;i<a;i++){
        fgets(aux,100,b);
    }
}
int strcheck(char a[]){ //Chequea un string (para nombre y apellidos)
    int i;
    if(strlen(a)<N-1){
        for(i=0;i<(strlen(a));i++){
            if(a[i]=='\n'){
                if(strlen(a)==1){
                    return 0;
                }
                a[i]='\0';
            }
            else if(a[i]==' '){
                return 0;
            }
            else{
                if(!isalpha(a[i])){
                    return 0;
                }
            }
        }
        return 1;
    }
    else{
        return 0;
    }
}
void escritorarchivo(int i,FILE* p){ //Escribe sobre el archivo desde el punto 'i'.
    punterofichero(i,p);
    for(;i<cant_t;i++){
        if(worker[i].ci!=0){
            fprintf(p,"%d %s %s %s %s %s %d",worker[i].ci,worker[i].nombre,worker[i].apellido,worker[i].departamento,worker[i].cargo,worker[i].fecha,worker[i].sueldo);
            if(i<cant_t-1){
                fprintf(p,"\n");
            }
        }
    }
}
int cicheck2(int a){ //Comprueba longitud de un entero (debe ser 7 o 8 para la cédula)
    int tam=0;
    do{
        tam++;
        a/=10;
    }while(a!=0);
    if((tam==7)||(tam==8)){
        return 1;
    }
    else{
        return 0;
    }
}
void vaciar(char a[]){ //Elimina de una cadena de caracteres el caracter '\n'
    int i;
    for(i=0;i<strlen(a);i++){
        if(a[i]=='\n'){
            a[i]='\0';
        }
    }
}
//funciones por anthony
char salid(char s){
    system("clear");
    int op;
    int i,ci,band=0,dp;  

    printf("\n\tDesea consultar por:\n\n");
    printf("\n\t(1)CI (2)Departamento (3)Cargo (4)Trabajador con mayor y menor sueldo\n");
    printf("\n\t: ");
    do{
        scanf("%d",&op);//Elige opcion del switch
    }while(op<1||op>4);

    switch(op){
        case 1:
        printf("\n\tIngrese CI del trabajador: ");
        do{
            scanf("%d",&ci);
        }while(ci<1);
        for(i=0;i<cant_t&&band==0;i++){//Busca la cedula, se detiene al encontrarla(band=1) o al alcanzar el maximo de trabajadores(cant_t)
            if(worker[i].ci==ci){
                printf("\n\tEl trabajador se llama %s %s\n",worker[i].nombre,worker[i].apellido);
                printf("\n\tTrabaja en el departamento de %s con el cargo de %s\n",worker[i].departamento,worker[i].cargo);
                printf("\n\tTiene %d de sueldo devengado\n",worker[i].sueldo);
                printf("\n\tIngreso en la fecha %s \n",worker[i].fecha); 
                band=1;
            }
        }
        if(band==0){//Si esto se cumple, evidentemente es porque no se encontro la CI
            printf("\n\tLa CI indicada no esta asociada a ningun trabajador de la empresa\n");
        }
        break;
        case 2:
        printf("\n\t(1)RRHH (2)Consultoria (3)Diseño (4)Produccion (5)Calidad (6)Distribucion\n");
        printf("\n\tIngrese Nr del Departamento: ");
        do{
            scanf("%d",&dp);
        }while(dp<1||dp>6);
        switch(dp){//Se llama a una funcion encargada de buscar el departamento ESCOJIDO
            case 1:
            buscar_depa("RRHH");
            break;
            case 2:
            buscar_depa("Consultoria");
            break;
            case 3:
            buscar_depa("Diseño");
            break;
            case 4:
            buscar_depa("Produccion");
            break;
            case 5:
            buscar_depa("Calidad");
            break;
            case 6:
            buscar_depa("Distribucion");
            break;
            default:
            break;
        }
        break;
        case 3:
        int cg;
        printf("\n\t(1)Gerente (2)Supervisor (3)Analista (4)Diseñador (5)Desarrollador (6)Auditor\n");
        printf("\n\tIntroduzca Nr del cargo a consultar: ");
        do{
            scanf("%d",&cg);
        }while(cg<1||cg>6);
        switch(cg){//Se llama a una funcion para buscar el cargo ingresado
            case 1:
            buscar_cargo("Gerente");break;
            case 2:
            buscar_cargo("Supervisor");break;
            case 3:
            buscar_cargo("Analista");break;
            case 4:
            buscar_cargo("Diseñador");break;
            case 5:
            buscar_cargo("Desarrollador");break;
            case 6:
            buscar_cargo("Auditor");break;
            default:
            break;
        }
        break;
        case 4://Calcula el mayor y menor sueldo, muestra si es compartido por varios
            int mayor_sueldo=0,menor_sueldo=0,i;
            for(i=0;i<cant_t;i++){
                if(i==0){//Inicializa el sueldo minimo con cualquier valor diferente de 0
                    register int k=0;//Variable para mover el indice
                    do{
                        menor_sueldo=worker[i+k].sueldo;//Se asigna sueldo minimo ACTUAL
                        k++;//Se incrementa para ir al siguiente trabajador
                    }while((menor_sueldo==0)&&((i+k)<cant_t));//Si el sueldo asignado es igual a 0 se repite (0 indica que el trabajador fue "eliminado")
                }
                if(worker[i].sueldo==0){continue;}//Se salta la iteracion para no tomar en cuenta los trabajadores eliminados (sueldo=0)

                if(worker[i].sueldo>mayor_sueldo){//Asignacion de mayor sueldo
                    mayor_sueldo=worker[i].sueldo;
                }
                if(worker[i].sueldo<menor_sueldo){//Asignacion de menor sueldo
                    menor_sueldo=worker[i].sueldo;
                }
            }
            for(i=0;i<cant_t;i++){//Busca y muestra por pantalla todos los trabajadores que coincidan con el mayor sueldo registrado
                if(worker[i].sueldo==mayor_sueldo){
                    printf("\n\tEl trabajador con mayor sueldo (%d) es: \n",mayor_sueldo);
                    printf("\n\tEl trabajador se llama %s %s\n",worker[i].nombre,worker[i].apellido);
                    printf("\n\tTiene la CI %d\n",worker[i].ci);
                    printf("\n\tTrabaja en el departamento de %s con el cargo de %s\n",worker[i].departamento,worker[i].cargo);
                    printf("\n\tIngreso en la fecha %s \n",worker[i].fecha);    
                }
            }
            printf("\n\n");
            for(i=0;i<cant_t;i++){//Lo mismo de arriba pero con el menor sueldo
                if(worker[i].sueldo==menor_sueldo){//defecto por worker extra==0
                    printf("\n\tEl trabajador con menor sueldo (%d) es: \n",menor_sueldo);
                    printf("\n\tEl trabajador se llama %s %s\n",worker[i].nombre,worker[i].apellido);
                    printf("\n\tTiene la CI %d\n",worker[i].ci);
                    printf("\n\tTrabaja en el departamento de %s con el cargo de %s\n",worker[i].departamento,worker[i].cargo);
                    printf("\n\tIngreso en la fecha %s \n",worker[i].fecha);    
                }
            }
        break;
        default:
        break; 
    }

    
    printf("\n\tOperacion terminada ");
    printf("\n\n\tIngrese (s) para volver al menu: ");
    do{
        __fpurge(stdin);
        scanf("%c",&s);
    }while((s!='s')&&(s!='S'));//Para volver al menu se ingresa s o S
    __fpurge(stdin);
    return s;
}

void llenar(){
    int i;
    FILE *f;

    f=fopen("Trabajadores.in","r");

    for(i=0;i<cant_t;i++){//Llena todas las estructuras anteriormente creadas con los datos del fichero
        fscanf(f,"%d",&worker[i].ci);
        fscanf(f,"%s",worker[i].nombre);
        fscanf(f,"%s",worker[i].apellido);
        fscanf(f,"%s",worker[i].departamento);
        fscanf(f,"%s",worker[i].cargo);
        fscanf(f,"%s",worker[i].fecha);
        fscanf(f,"%d",&worker[i].sueldo);
    }

    fclose(f);
}
void buscar_cargo(char v[]){//recibe el cargo a buscar
    int i,cantt2=0,total_sueldo2=0,band=0;
    FILE *cargo;

    cargo=fopen("Cargo.txt","w");//Se abre fichero donde guardar los ocupantes del cargo

    for(i=0;i<cant_t;i++){//Busca coincidencias
        if(strcmp(worker[i].cargo,v)==0){//Cargo igual al que se busca
            cantt2++;//Contador de cantidad de ocupantes del cargo
            total_sueldo2+=worker[i].sueldo;//Suma total de todos los ocupantes
            fprintf(cargo,"%d %s %s %s %s %s %d\n",worker[i].ci,worker[i].nombre,worker[i].apellido,worker[i].departamento,worker[i].cargo,worker[i].fecha,worker[i].sueldo);
            band=1;//Verificador de éxito
        }
    }
    if(cantt2==1){//Singular y plural segun el resultado
        printf("\n\tHay %d trabajador con el cargo\n",cantt2);
    }else{
        printf("\n\tHay %d trabajadores con el cargo\n",cantt2);
    }
    printf("\n\tCon un %d en total de sueldos devengados",total_sueldo2);
    printf("\n\tArchivo \"Cargo.txt\" generado\n");
    if(band==0){
        printf("\n\tNo hay trabajadores con ese cargo\n");
    }

    fclose(cargo);
}
char salif(char s){
    system("clear");
    int i,ci,band=0;
    char veri[3];
    printf("\n\tIntroduzca CI del trabajador que desea desincorporar\n\t:");
    do{
        scanf("%d",&ci);
    }while(ci<1);
    for(i=0;(i<cant_t)&&(band==0);i++){//Se busca CI
        if(ci==worker[i].ci){//Compara y para de iterar al hallar la CI
            band=1;
            printf("\n\tEl trabajador a eliminar es el siguiente: \n");
            printf("\n\tEl trabajador se llama %s %s\n",worker[i].nombre,worker[i].apellido);
            printf("\n\tTrabaja en el departamento de %s con el cargo de %s\n",worker[i].departamento,worker[i].cargo);
            printf("\n\tTiene %d de sueldo devengado\n",worker[i].sueldo);
            printf("\n\tIngreso en la fecha %s \n",worker[i].fecha);
        }
    }
    if(band){//Si se encontro pregunta si esta seguro de eliminar
        printf("\n\tEsta seguro de eliminar al trabajador anteriormente mostrado? (Si/No): \n\t");
        do{
            fgets(veri,3,stdin);//Lee desicion
        }while(((strcmp(veri,"si")!=0)&&(strcmp(veri,"no")!=0))&&((strcmp(veri,"Si")!=0)&&(strcmp(veri,"No")!=0)));
        if((strcmp(veri,"si")==0)||(strcmp(veri,"Si")==0)){//Comprueba
            FILE *f;
            FILE *ex;
            char motivo[10];
            int op,dd,mm,aa;
            ex=fopen("extrabajadores.txt","a");//Abre fichero de extrabajadores
            f=fopen("Trabajadores.in","w");//Abre fichero base
            fflush(f);//Limpia el fichero base
            printf("\n\t1:Traslado 2:Renuncia 3:Despido 4:Otro\n");
            printf("\n\tIngrese Nr del motivo\n\t:");
            do{
                scanf("%d",&op);
            }while((op<1)||(op>4));
            switch(op){//Asigna motivo escojido
                case 1:strcpy(motivo,"Traslado");break;
                case 2:strcpy(motivo,"Renuncia");break;
                case 3:strcpy(motivo,"Despido");break;
                case 4:strcpy(motivo,"Otro");break;
            }
            printf("\n\tIntroduzca fecha (dia/mes/año)\n");
            do{//Fechas
                printf("\tIngrese dia\n\t:");
                scanf("%d",&dd);
                printf("\tIngrese mes\n\t:");
                scanf("%d",&mm);
                printf("\tIngrese año\n\t:");
                scanf("%d",&aa);
            }while((dd<1||dd>31)||(mm<1||mm>12)||(aa<2000||aa>3000));
            for(i=0;i<cant_t;i++){//Se mueve por todas las estructuras
                if((ci!=worker[i].ci)&&(worker[i].ci!=0)){//Imprime todas en el fichero base menos la que se acaba de eliminar
                    if(i<(cant_t-1)){
                        fprintf(f,"%d %s %s %s %s %s %d\n",worker[i].ci,worker[i].nombre,worker[i].apellido,worker[i].departamento,worker[i].cargo,worker[i].fecha,worker[i].sueldo);
                    }
                    else{//Para no imprimir un salto de linea al final
                        fprintf(f,"%d %s %s %s %s %s %d",worker[i].ci,worker[i].nombre,worker[i].apellido,worker[i].departamento,worker[i].cargo,worker[i].fecha,worker[i].sueldo);
                    }
                }else{//Imprime y "elimina" de las estructuras el trabajador (se elimina en su totalidad al cerrar el programa)
                    if(worker[i].ci!=0){
                        fprintf(ex,"%d %s %s %s %s %s %d %s %d/%d/%d\n",worker[i].ci,worker[i].nombre,worker[i].apellido,worker[i].departamento,worker[i].cargo,worker[i].fecha,worker[i].sueldo,motivo,dd,mm,aa);
                        worker[i].ci=0;
                        strcpy(worker[i].cargo,"\0");
                        strcpy(worker[i].departamento,"\0");
                        worker[i].sueldo=0;
                    }
                }
            }
            fclose(f);
            fclose(ex);
            printf("\n\tArchivo \"extrabajadores.txt\" creado/modificado\n");
        }else{//Se elijió no hacer nada
            printf("\n\tNo se hará ningún cambio\n");
        }
    }else{//No se encontro la CI
        printf("\n\tLa CI indicada no está asociada a ningun trabajador de la empresa\n");
    }
    printf("\n\tOperacion terminada\n");
    printf("\n\tIngrese (s) para volver al menu: ");
    do{
        __fpurge(stdin);
        scanf("%c",&s);
    }while((s!='s')&&(s!='S'));//Al menu
    __fpurge(stdin);
    return s;
}
void buscar_depa(char dep[]){//Busca el departamento que recibe como string
    int i;
    int cantt=0,total_sueldo=0;
    FILE *depa;
    depa=fopen("departamento.txt","w");//Abre archivo de departamento para mostrar los miembros

    for(i=0;i<cant_t;i++){
        if(strcmp(worker[i].departamento,dep)==0){//Imprime las coincidencias en el fichero depa
            cantt++;//Cuenta
            total_sueldo+=worker[i].sueldo;//Suma del total acumulado
            fprintf(depa,"%d %s %s %s %s %s %d\n",worker[i].ci,worker[i].nombre,worker[i].apellido,worker[i].departamento,worker[i].cargo,worker[i].fecha,worker[i].sueldo);                
        }
    }
    if(cantt>1){//Plural y singular por estetica
        printf("\n\tHay %d trabajadores en el departamento\n",cantt);
    }else{
        if(cantt==0){//Si no hubo ningun trabajador
            printf("\n\tNo Hay trabajadores en el departamento\n");
        }else{
            printf("\n\tHay %d trabajador en el departamento\n",cantt);
        }
    }
    printf("\n\tCon un %d en total de sueldos devengados",total_sueldo);
    printf("\n\tArchivo \"Departamento.txt\" generado\n");

    fclose(depa);
}
//fin func.
//Funciones Piero
//Funcion para integrar nuevos trabajadores.
void Ingresar(){
    FILE *fichero;
    int t, i, d, c, a, check, dd, mm, aa;
    system("clear");
    a=cant_t;
    fichero = fopen("Trabajadores.in", "a");
    if(fichero == NULL){
    printf("No se pudo abrir el archivo. \n");
    exit(1);
    }
    printf("\n\tCuantos trabajadores desea ingresar? \n\t:");  //Numero de trabajadore a ingresar.
    do{
        scanf("%i", &t);
    }while(t<1);//validacion
    cant_t+=t;
    worker=(workers*)realloc(worker,cant_t*sizeof(workers));
    printf("\n");
    check=1;
    int aux_1;
    for(i = a; i < cant_t; i++){
        do{
            if(check==0){
                printf("\nERROR: Documento inválido (Debe tener 7 o 8 dígitos y NO ser negativo)\n\n");
            }
            printf("Ingrese documento de identidad de trabajador %i \n", i+1);  //Numero de cedula de identidad del trabajador.
            do{
                scanf("%i", &aux_1);
            }while(veri(aux_1)==1);
            worker[i].ci=aux_1;
            __fpurge(stdin);
            check=cicheck2(worker[i].ci);
        }while(check==0);
        check=1;
        printf("\n");
        do{
            if(check==0){
                printf("ERROR: Elemento inválido\n\n");
            }
            printf("Nombre de trabajador %i \n", i+1);  //Nombre del trabajador.
            __fpurge(stdin);
            fgets(worker[i].nombre,N,stdin);
            check=strcheck(worker[i].nombre);
        }while(check==0);
        check=1;
        printf("\n");
        do{
            if(check==0){
                printf("\nERROR: Elemento inválido\n\n");
            }
            printf("Apellido de trabajador %i \n", i+1);  //Apellido del trabajador.
            __fpurge(stdin);
            fgets(worker[i].apellido,N,stdin);
            check=strcheck(worker[i].apellido);
        }while(check==0);
        check=1;
        printf("\n");
        do{
            printf("Indique el numero de identificacion del departamento asignado para trabajador %i \n", i+1); //Departamento.
            printf("1--RRHH / 2--Consultoria / 3--Diseño / 4--Produccion / 5--Calidad / 6--Distribucion \n");
            scanf("%i", &d);
            switch(d){
                case 1:
                strcpy(worker[i].departamento, "RRHH");
                printf("RRHH es el departamento asignado para trabajador %i \n\n", i+1);
                break;
                case 2:
                strcpy(worker[i].departamento, "Consultoria");
                printf("Consultoria es el departamento asignado para trabajador %i \n\n", i+1);
                break;
                case 3:
                strcpy(worker[i].departamento, "Diseño");
                printf("Diseño es el departamento asignado para trabajador %i \n\n", i+1);
                break;
                case 4:
                strcpy(worker[i].departamento, "Produccion");
                printf("Produccion es el departamento asignado para trabajador %i \n\n", i+1);
                break;
                case 5:
                strcpy(worker[i].departamento, "Calidad");
                printf("Calidad es el departamento asignado para trabajador %i \n\n", i+1);
                break;
                case 6:
                strcpy(worker[i].departamento, "Distribucion");
                printf("Distribucion es el departamento asignado para trabajador %i \n\n", i+1);
                break;
                default:
                printf("ERROR: El numero indicado NO esta asignado a ningun departamento \n");
                printf("Vuelva a intentarlo \n\n");
                break;
            }
        }while(d < 1 || d > 6);
        printf("\n");
        do{
            printf("Indique el numero de identificacion del cargo asignado para trabajador %i \n", i+1);  //Cargo.
            printf("1--Gerente / 2--Supervisor / 3--Analista / 4--Diseñador / 5--Desarrollador / 6--Auditor \n");
            scanf("%i", &c);
            switch(c){
                case 1:
                strcpy(worker[i].cargo, "Gerente");
                printf("Gerente es el cargo asignado para trabajador %i \n\n", i+1);
                break;
                case 2:
                strcpy(worker[i].cargo, "Supervisor");
                printf("Supervisor es el cargo asignado para trabajador %i \n\n", i+1);
                break;
                case 3:
                strcpy(worker[i].cargo, "Analista");
                printf("Analista es el cargo asignado para trabajador %i \n\n", i+1);
                break;
                case 4:
                strcpy(worker[i].cargo, "Diseñador");
                printf("Diseñador es el cargo asignado para trabajador %i \n\n", i+1);
                break;
                case 5:
                strcpy(worker[i].cargo, "Desarrollador");
                printf("Desarrollador es el cargo asignado para trabajador %i \n\n", i+1);
                break;
                case 6:
                strcpy(worker[i].cargo, "Auditor");
                printf("Auditor es el cargo asignado para trabajador %i \n\n", i+1);
                break;
                default:
                printf("ERROR: El numero indicado NO esta asignado a ningun cargo \n");
                printf("Vuelva a intentarlo \n\n");
                break;
            }
        }while(c < 1 || c > 6);
        printf("\n");
        do{
            if(check==0){
                printf("\nERROR: Elemento negativo o 0\n\n");
            }
            printf("Indique el sueldo ($) que devenga trabajador %i \n", i+1);  //Sueldo en $ del trabajador.
            scanf("%d", &worker[i].sueldo);
            check=0;
        }while(worker[i].sueldo<1);
        check=1;
        printf("\n");
        printf("Indique la fecha (dd/mm/aaaa) de ingreso de trabajador %i \n", i+1);  //Fecha de ingreso.
        __fpurge(stdin);
        do{
            if(check==0){
                printf("ERROR: Fecha ingresada inválida.\n\n");
            }
            printf("-- Ingrese la nueva fecha de ingreso de el trabajador (dia/mes/año)--\n\n");
            printf("\tIngrese dia:");
            scanf("%d",&dd);
            __fpurge(stdin);
            printf("\tIngrese mes:");
            scanf("%d",&mm);
            __fpurge(stdin);
            printf("\tIngrese año:");
            scanf("%d",&aa);
            __fpurge(stdin);
            check=0;
        }while((dd<1||dd>31)||(mm<1||mm>12)||(aa<1900||aa>3000));
        check=1;
        sprintf(worker[i].fecha,"%d/%d/%d",dd,mm,aa);
        fprintf(fichero,"\n%d %s %s %s %s %s %d",worker[i].ci,worker[i].nombre,worker[i].apellido,worker[i].departamento,worker[i].cargo,worker[i].fecha,worker[i].sueldo);
        printf("\n");
    }    
    fclose(fichero);
}
int veri(int ci){//Verifica que la CI ingresada no esté ya registrada
    int i,band=0;

    for(i=0;i<cant_t;i++){
        if(ci==worker[i].ci){
            band=1;
        }
    }
    if(band==1){
        printf("La Cedula que ingreso ya se encuentra registrada, intente de nuevo\n");
    }

    return band;
}
