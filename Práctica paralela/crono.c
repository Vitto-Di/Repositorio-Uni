//Test 2 cronometro
#include <stdio.h>
#include <conio.h>
#include <windows.h>

int main(){
    int hh,mm,ss,x=1000;
    printf("Cronometro de 24 hrs.\n");
    for(hh=0;hh<24;hh++){
        for(mm=0;mm<60;mm++){
            for(ss=0;ss<60;ss++){
                printf("  %02d:%02d:%02d\r",hh,mm,ss);
                Sleep(x);
            }
        }
    }



    getch();
    return 0;
}