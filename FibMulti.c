#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <pthread.h>
    #define randnum(min,max)\
        (rand()% (int)(((max)+1))) + (min)
unsigned long long int serieSum(int times){
	if (times==0) return 0; 
    if (times==1) return 1;
    if (times==2) return 1; 
    times-=2;
	unsigned long long int count = 0,ant = 1,ant2=0;
    	for (int i=0;i<=times;i++){
        	count=ant+ant2;
        	ant2= ant;
        	ant=count;        
    	}
    return count;
}
void * roll(void * arg){
    unsigned long long int suma = 0;
    int times = 50000; 
    for (int i=0;i<times;i++){	 
       suma+=serieSum(randnum(0,19));
    }
    *(long long int *)arg  = suma;
}


int main() {
	printf("\tProcesando sucesiones de fibonacci...\n");
    srand(time(0));
	clock_t start_t, end_t; 
	start_t = clock(); //Inicio de contador de tiempo de procesamiento del programa
	long long int x=0; //Variable en la que se almacenara la suma de todas las sucesiones de fibonacci calculadas
	long long int n[20]; //Variables que utilizara cada hilo para evitar condiciones de carrera
	for (int i=0; i<=19; i++) {n[i]=0;} //Se inicializan las variables que utilizaran los hilos en 0
    /* Se crean 20 hilos que trabajaran en paralelo y calcularan 50000 sucesiones cada uno de ellos
       utilizando la funcion Fibonacci*/
	pthread_t hilo[20];
	for (int i=0; i<=19; i++) {
		pthread_create(&hilo[i],NULL,&roll,&n[i]);	
	}

	/* Se espera a que terminen los 20 hilos y se van sumando los resultados obtenidos en la variable de resultados x */
	for (int i=0; i<=19; i++) {
		pthread_join(hilo[i],NULL);
		x += n[i];
	}
	end_t = clock(); //Fin de contador de tiempo de procesamiento del programa
	// Se muestran los datos finales en pantalla
	printf("\n\t\tInformacion Final\n");
	printf("\tNumero Calculado ---> %lli \n", x);
	printf("\tTiempo transcurrido en segundos ---> %.2f \n", (double)(end_t-start_t)/CLOCKS_PER_SEC);
	printf("\tSucesiones calculadas ---> 50000 por cada hilo (1000000 total)\n");
    return 0;
}
