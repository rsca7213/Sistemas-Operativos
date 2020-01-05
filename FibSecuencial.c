#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

/*Se define randnum(), la cual generara un numero aleatorio en el rango 
establecido por los parametros min max */
#define randnum(min,max)\
    (rand()% (int)(((max)+1))) + (min)

/*Función utilizada para calcular la secuencia de fibonacci, en esta
funcion se generara un numero aleatorio de 0 a 19 que se utilizara para
calcular la sucesion de fibonacci utilizando el metodo del ciclo que ira
sumando los numeros anteriores para calcular la sucesion*/
unsigned long long int serieSum(){    
    int times =randnum(0,19);	
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

//inicio de funcion principal
void main () {
    srand(time(0)); //Se genera una semilla para el randomizador de numeros basandose en el tiempo actual del reloj local
    printf("\tProcesando sucesiones de fibonacci...\n");
    clock_t start_t = clock(); //Se inicia el contador de tiempo de procesamiento del programa
	long long int res=0; //Variable en la que se almacenara la suma de todas las sucesiones calculadas
	/* Ciclo que calculara un millon de sucesiones de fibonacci utilzando la funcion serieSum() y las sumara */
	for (int j=1; j<=1000000; j++) {
		res+=serieSum(); //Se calcula una sucesion de fibonacci y se le suma a la variable de resultado "res"
	}

	clock_t end_t = clock(); //Se finaliza el contador de tiempo de procesamiento del programa
	//Se muestran por pantalla los datos finales del programa
	printf("\n\t\tInformacion Final\n");
	printf("\tNumero Calculado ---> %lli \n",res);
	printf("\tTiempo transcurrido en segundos ---> %.2f \n", (double)(end_t-start_t)/CLOCKS_PER_SEC);
	printf("\tSucesiones calculadas ---> 1000000 \n");
}

