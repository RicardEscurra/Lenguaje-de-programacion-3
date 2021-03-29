#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#define MAX 100

void handler(int sig){ //handler
    printf("Signal number is %d \n", sig);
}

int main(int argc, char **argv){
    FILE* pFile;
    srand(time(NULL));
    
    
    //variables
    char procesoId[MAX], senal[MAX], seg[MAX];
    int Id=0, segundos=0, senales=0;
    
    //inicializamos vectores
    for(int i=0; i<MAX-1; i++){
        procesoId[i]=' ';
        senal[i]=' ';
        seg[MAX]=' ';
    }
    procesoId[MAX-1]='\0';
    senal[MAX-1]='\0';
    seg[MAX-1]='\0';
    
    //abrimos el archivo y parte principal
    
    for(int i=0; i<5; i++){
        pid_t pid = fork();
        
        if(pid == 0){
            //valores
            Id = getpid();
            segundos = rand() %11 +1;
            //senales = rand () %64 +1;
            senales = 29;
            sprintf(senal, "%d", senales);
            sprintf(seg, "%d", segundos);
            sprintf(procesoId, "%d", Id);
 
            //cargar datos en un archivo
            pFile = fopen("archivo.txt", "a+");
            fprintf(pFile,"%s %s %s\n",procesoId, senal, seg);    
            fclose(pFile);
            
            //visualizacion
            printf("id del proceso hijo: %d\n",Id);
            signal(SIGIO, &handler);
            
        }
        else if (pid > 0)wait(NULL);
        
    }
    pause();
    fclose(pFile);

    return 0;
}
