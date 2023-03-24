/*Segundos pasados*/
#include <stdio.h>
#include <conio.h>

int main (){
    int hh,mm,ss,sss;
    printf("ingrese hora en formato HH,MM,SS :");
    scanf("%d %d %d",&hh,&mm,&ss);
    sss=(hh*3600)+(mm*60)+(ss);
    printf("Han pasado %d",sss);
    printf("segs desde las 12 AM");

    getch ();
    return 0;
}