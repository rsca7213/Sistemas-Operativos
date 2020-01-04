#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
    #define randnum(min,max)\
        (rand()% (int)(((max)+1))) + (min)
/* Funcion que utiliza la ecuacion para hallar la sucesion de fibonacci y recibe un parametro n que seria
   el numero de fibonacci a calcular*/
long Fibonacci (double n) {
	return ((pow((1+sqrt(5))/2,n))-(pow((1-sqrt(5))/2,n)))/(sqrt(5));
}
unsigned long long int serieSum(){    
    int times =randnum(0,19);	
    if (times==0) return 0; 
    if (times==1) return 1;
    if (times==2) return 1; 
    times-=2;
    //printf("times2 %lld \n ", times) ;
	unsigned long long int count = 0,ant = 1,ant2=0;
    	for (int i=0;i<=times;i++){
        	count=ant+ant2;
        	ant2= ant;
        	ant=count;        
    	}
    return count;
}
void main () {
    srand(time(0));
    printf("\tProcesando sucesiones de fibonacci...\n");
    clock_t start_t = clock(); //Se inicia el contador de tiempo de procesamiento del programa
	double i; //Variable en la que se almacenara un valor de 0 a 19 randomizado para calcular sucesion de fibonacci
	long long int res=0; //Variable en la que se almacenara la suma de todas las sucesiones calculadas
	/* Ciclo que calculara un millon de sucesiones de fibonacci y las sumara */
	for (int j=1; j<=1000000; j++) {
		//Se randomiza un numero de 0 a 19		
		res+=serieSum(); //Se calcula la sucesion de fibonacci con el numero randomizado y se le suma a la variable de resultado
	}

	clock_t end_t = clock(); //Se finaliza el contador de tiempo de procesamiento del programa
	//Se muestran por pantalla los datos finales del programa
	printf("\n\t\tInformacion Final\n");
	printf("\tNumero Calculado ---> %lli \n",res);
	printf("\tTiempo transcurrido en segundos ---> %.2f \n", (double)(end_t-start_t)/CLOCKS_PER_SEC);
	printf("\tSucesiones calculadas ---> 1000000 \n");
}

