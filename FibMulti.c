#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <pthread.h>

/* Funcion que calculara 50000 sucesiones de fibonacci utilizando la ecuacion para
calcular sucesion de Fibonacci y recibira un puntero a una direccion de memoria que contiene
una variable de tipo long long int en donde se almacenara la suma de las sucesiones calculadas */
void *Fibonacci (void *arg) {
	double n; //Variable utilizada para el randomizado de numero de fibonacci de 0 a 19
	long long int x = 0; //Variable en donde se iran sumando los resultados de las sucesiones

	/* Ciclo que calculara 50000 sucesiones de fibonacci y las sumara */
	for (int i=1; i<=50000; i++) {
		//Se randomiza un numero de 0 a 19 para calcular la sucesion de fibonacci
		srand(time(NULL));
		n=rand()%20;
		x += ((pow((1+sqrt(5))/2,n))-(pow((1-sqrt(5))/2,n)))/(sqrt(5)); //Se calcula la sucesion con el numero randomizado y se suma
	}

	*(long long int *)arg = x; //Se almacenara el resultado de la suma de las sucesiones fibonacci en la variable que se le pasa a la funcion
}

int main() {
	printf("\tProcesando sucesiones de fibonacci...\n");

	clock_t start_t, end_t; 
	start_t = clock(); //Inicio de contador de tiempo de procesamiento del programa
	long long int x=0; //Variable en la que se almacenara la suma de todas las sucesiones de fibonacci calculadas
	long long int n[20]; //Variables que utilizara cada hilo para evitar condiciones de carrera
	for (int i=0; i<=19; i++) {n[i]=0;} //Se inicializan las variables que utilizaran los hilos en 0
   
    /* Se crean 20 hilos que trabajaran en paralelo y calcularan 50000 sucesiones cada uno de ellos
       utilizando la funcion Fibonacci*/
	pthread_t hilo[20];
	for (int i=0; i<=19; i++) {
		pthread_create(&hilo[i],NULL,&Fibonacci,&n[i]);	
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