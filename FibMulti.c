#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <pthread.h>

/*Se define randnum(), la cual generara un numero aleatorio en el rango 
establecido por los parametros min max */
#define randnum(min,max)\
    (rand()% (int)(((max)+1))) + (min)

/*Función utilizada para calcular la secuencia de fibonacci, en esta
funcion se recibe un numero entero "times", el cual se utilizara para
calcular la sucesion de fibonacci utilizando el metodo del ciclo que ira
sumando los numeros anteriores para calcular la sucesion*/
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

/*Funcion que generara numeros aleatorios de 0 a 19 y llamara a la funcion serieSum para que
calcule la sucesion de fibonacci con el numero aleatorio generado (esto lo hara 50000 veces), los resultados los ira
almacenando en la variable suma, y al finalizar se pasara a la variable parametro de la funcion "arg", la suma total
de los resultados */
void * roll(void * arg){
    unsigned long long int suma = 0;
    int times = 50000; 
    for (int i=0;i<times;i++){	 
       suma+=serieSum(randnum(0,19));
    }
    *(long long int *)arg  = suma;
}

//inicio de funcion principal
int main() {
	srand(time(0)); //se genera una semilla para el randomizador de numeros, basado en el tiempo local de la maquina
	printf("\tProcesando sucesiones de fibonacci...\n");
	clock_t start_t, end_t; 
	start_t = clock(); //Inicio de contador de tiempo de procesamiento del programa
	long long int x=0; //Variable en la que se almacenara la suma de todas las sucesiones de fibonacci calculadas
	long long int n[20]; //Variables que utilizara cada hilo para evitar condiciones de carrera
	for (int i=0; i<=19; i++) {n[i]=0;} //Se inicializan las variables que utilizaran los hilos en 0
    /* Se crean 20 hilos que trabajaran en paralelo y calcularan 50000 sucesiones cada uno de ellos
       utilizando la funcion roll(void *arg)*/
	pthread_t hilo[20];
	for (int i=0; i<=19; i++) {
		//Se crea un hilo que trabajara con la funcion roll y se le pasa n[i] como parametro
		pthread_create(&hilo[i],NULL,&roll,&n[i]);	
	}

	/* Se espera a que terminen los 20 hilos y se van sumando los resultados obtenidos en la variable de resultados "x" */
	for (int i=0; i<=19; i++) {
		pthread_join(hilo[i],NULL);
		x += n[i];
	}
	end_t = clock(); //Fin de contador de tiempo de procesamiento del programa
	// Se muestran los datos finales en pantalla
	printf("\n\t\tInformacion Final\n");
	printf("\tNumero Calculado ---> %lli \n", x);
	printf("\tTiempo transcurrido en segundos ---> %.2f \n", (double)(end_t-start_t)/CLOCKS_PER_SEC);
	printf("\tSucesiones calculadas ---> 50000 por cada hilo (20 hilos) (1000000 total)\n");
    return 0;
}
