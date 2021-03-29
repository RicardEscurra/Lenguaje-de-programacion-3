#include <sys/types.h> 
#include <sys/ipc.h> 
#include <sys/shm.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h>
#include <sys/wait.h>
#include <math.h>
#include <string.h>
// declaración implicita de las funciones
void insertionSort(int arr[], int n); 
void merge(int a[], int l1, int h1, int h2, int tama); 
void procesamiento(int b[],int ini, int fin);
void imprimirarbol(int a[], int len, int proceso);
void mergeSort(int a[], int l, int h,int lengt)
{ 
	int i, len=(h-l+1);
	if (len<=5) 
	{ 
		insertionSort(a+l, len); // Uso de la ordenación por inserción para una matriz de tamaño pequeño 
		return; 
	} 
	pid_t lpid,rpid; 
	lpid = fork(); 
	if (lpid<0) 
	{ 
		perror("Left Child Proc. not created\n"); 
		_exit(-1); 
	} 
	else if (lpid==0) 
	{ 
		mergeSort(a,l,l+len/2-1, lengt);
		_exit(0); 
	} 
	else
	{ 
		rpid = fork(); 
		if (rpid<0) 
		{ 
			perror("Right Child Proc. not created\n"); 
			_exit(-1); 
		} 
		else if(rpid==0) 
		{ 
			mergeSort(a,l+len/2,h, lengt);
			_exit(0); 
		} 
	} 

	int status; 

	//  Espere a que finalicen los procesos secundarios
	waitpid(lpid, &status, 0); 
	waitpid(rpid, &status, 0);
	// Fusionar los subarreglos ordenados
	merge(a, l, l+len/2-1, h, lengt); 
}
void insertionSort(int arr[], int n) 
{ 
    int i, key, j; 
    for (i = 1; i < n; i++) 
    { 
        key = arr[i]; 
        j = i-1; 

        while (j >= 0 && arr[j] > key) 
        { 
            arr[j+1] = arr[j]; 
            j = j-1; 
        } 
        arr[j+1] = key; 
    } 
} 
// Método para fusionar subarreglos ordenados
void merge(int a[], int l1, int h1, int h2, int tama) 
{ 
	int count=h2-l1+1; 
	int sorted[count]; 
	int i=l1, k=h1+1, m=0; 
    if(count!= tama){
		printf("Proceso i lista ordenada: ");
    	procesamiento(a, i, h1);
		printf("\n");	
	}
	if(count!= tama){
		printf("Proceso i lista ordenada: ");
    	procesamiento(a, k, h2);
		printf("\n");	
	}
    printf("Proceso i: lista izquierda ");
    procesamiento(a, i, h1);
    printf(", lista derecha ");
    procesamiento(a, k, h2);
	while (i<=h1 && k<=h2) 
	{ 
		if (a[i]<a[k]) 
			sorted[m++]=a[i++]; 
		else if (a[k]<a[i]) 
			sorted[m++]=a[k++]; 
		else if (a[i]==a[k]) // Para no eliminar los numeros repetidos
		{ 
			sorted[m++]=a[i++]; 
			sorted[m++]=a[k++]; 
		} 
	} 

	while (i<=h1) 
		sorted[m++]=a[i++]; 

	while (k<=h2) 
		sorted[m++]=a[k++]; 

	int arr_count = l1;
    printf(" => ");
    procesamiento(sorted, 0, count-1);
	for (i=0; i<count; i++,l1++)
    {
        a[l1] = sorted[i];
    }
    printf("\n");	 
}
void procesamiento(int b[],int ini, int fin)
{
    printf("{");
    for(int i=ini; i<=fin; i++)
    {
        if(i<fin)
            printf("%d,",b[i]);
        else
            printf("%d",b[i]);
    }
    printf("}");
}

void imprimirarbol(int a[], int len, int proceso)
{
	printf("====esquema de arbol====\n");
	int poten2,partir,partir2,cont, proce;
	double poten;
	int result = (int)(floor(log(proceso+1) / log(2)) +1);
	//printf("%d",result);
	printf("\t\t\tproceso 0");
	printf("\n");
	printf("\t\t\t");
	for(int j=0 ; j< len; j++){
		printf("%d", a[j]);
	}
	printf("\n");
	printf("\n");
	proce=0;
	for(int i=1; i< result-1; i++){
		poten= pow(2,i);
		poten2= (int)poten;
		partir= len/poten2;
		cont=1;
		partir2= partir;
		for(int j=0 ; j< len; j++){
			if(partir-1==j){
				proce= proce+1;
				cont= cont +1;
				partir= partir2*cont;
				if(proce==1 || proce==2)
					printf("\t       proceso %d",proce);
				else
					printf("\tproceso %d",proce);
			}
		}
		printf("\n");
		poten= pow(2,i);
		poten2= (int)poten;
		partir= len/poten2;
		cont=1;
		partir2= partir;
		if(proce==1 || proce==2)
			printf("\t       ");
		else
			printf("\t    ");
		for(int j=0 ; j< len; j++){
			printf("%d", a[j]);
			if(partir-1==j){
				cont= cont +1;
				partir= partir2*cont;
				if(proce==1 || proce==2)
					printf("\t             ");
				else
					printf("\t    ");
			}
		}
		printf("\n");
		printf("\n");
	}
	printf("====mapeos====\n");
	printf("Proceso 0: ");
	for(int j=0 ; j< len; j++){
		printf("%d,", a[j]);
	}
	proce=1;
	printf("\n");
	for(int i=1; i< result-1; i++){
		poten= pow(2,i);
		poten2= (int)poten;
		partir= len/poten2;
		cont=1;
		partir2= partir;
		printf("Proceso %d: ",proce);
		for(int j=0 ; j< len; j++){
			printf("%d,", a[j]);
			if(partir-1==j){
				proce= proce+1;
				cont= cont +1;
				partir= partir2*cont;
				printf("\n");
				if(j!=len-1)	
					printf("Proceso %d: ",proce);
			}
		}
	}
	
}

// Driver code 
int main() 
{ 
	int shmid; 
	key_t key = IPC_PRIVATE; 
	int *shm_array; 

	// Usando una matriz de tamaño fijo. Podemos descomentar
	//debajo de las líneas para tomar el tamaño del usuario
	int length, indice=0;
	int proce2,conta=0;
	char lectura[100];
	scanf("%[^\n]%*c",lectura);
	char *p;
	p =lectura;
	int proce= (int) strtol(p, NULL, 10);
	while (*p != '\0') {
		if( !(*p == ' '|| *p == ',')) conta++;
		p++;
	}
	length= conta-1;
	//Calcular la longitud del segmento
	size_t SHM_SIZE = sizeof(int)*length; 
	// Crea el segmento
	if ((shmid = shmget(key, SHM_SIZE, IPC_CREAT | 0666)) < 0) 
	{ 
		perror("shmget"); 
		_exit(1); 
	} 

	//  Ahora adjuntamos el segmento a nuestro espacio de datos.
	if ((shm_array = shmat(shmid, NULL, 0)) == (int *) -1) 
	{ 
		perror("shmat"); 
		_exit(1); 
	} 
	proce2= proce;
	char *k;
	k =lectura;
	while (*k != '\0') {
		if( !(*k == ' '|| *k == ',')){
			if(indice< length && ((int) strtol(k, NULL, 10)!= proce2)){
				shm_array[indice]= (int) strtol(k, NULL, 10);
				indice++;
				proce2=-1;
			}
		} 
		k++;
	}
	
	// Ordenar la matriz creada
	imprimirarbol(shm_array, length, proce);
	printf("====procesamiento===\n");
	mergeSort(shm_array, 0, length-1, length); 

	//Compruebe si la matriz está ordenada o no
	printf("\n");
	/* Separarse de la memoria compartida ahora que estamos
    terminado de usarlo */
	if (shmdt(shm_array) == -1) 
	{ 
		perror("shmdt"); 
		_exit(1); 
	} 

	/* Eliminar el segmento de memoria compartida */
	if (shmctl(shmid, IPC_RMID, NULL) == -1) 
	{ 
		perror("shmctl"); 
		_exit(1); 
	} 

	return 0; 
} 