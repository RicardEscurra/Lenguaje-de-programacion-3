#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

#define MAX 100

int main (int argc, char **argv){
    //variables
    FILE *pFile;
    char procesoId[MAX], senal[MAX], seg[MAX];
    int status=MAX;
    

    //inicializamos vectores
    for(int i=0; i<MAX-1; i++){
        procesoId[i]=' ';
        senal[i]=' ';
        seg[MAX]=' ';
    }
    procesoId[MAX-1]='\0';
    senal[MAX-1]='\0';
    seg[MAX-1]='\0';
   
    //abrimos archivo
    pFile = fopen ("archivo.txt","rt");
    if (pFile == NULL){
        perror("Error al abrir el archivo");
        return -1;
    }
    else {
        //mientras no llegue al final
        while(!feof(pFile)){
            //guardamos valores en vectores
            fscanf(pFile, "%s", procesoId);
            fscanf(pFile, "%s", senal);
            fscanf(pFile, "%s", seg);
            
            //duerme
            sleep(atoi(seg));
            printf("%d  %d\n",atoi(procesoId), atoi(senal));
            //mandamos la senal
            status = kill(atoi(procesoId), atoi(senal));
            if(status == -1){
                perror("error xd");
                return -1;
            }
        }
        fclose (pFile);
    } 
    return 0;
}