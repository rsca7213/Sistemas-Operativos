#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[]){

	/*Se declaran las variables necesarias para medir el tiempo del programa a ejecutar*/
	struct timeval tiempoInicial, tiempoFinal;
    double tiempoTotal;
    
	
	/*Se declara el string que contendra el programa a ejecutar
	junto a sus argumentos*/

	char progYargs[2000];
	
	/*Se separa el programa a ejecutar y sus argumentos para 
	unirlos todos en un solo string(progYargs)*/

	for(int i=1;i<argc;i++){
		strcat(progYargs,argv[i]);
		if(i!=(argc-1))strcat(progYargs," ");

	}
	
	//se inicia el cronometro
	gettimeofday(&tiempoInicial, NULL); 

	/*se ejecuta el nuevo programa con sus respectivos argumentos
	usando el string que contiene dicho programa con sus argumentos*/
	system(progYargs);
	
	//se finaliza el cronometro
	gettimeofday(&tiempoFinal, NULL); 


	/*Se calcula e imprime el tiempo que tardo el programa en ejecutarse*/
	tiempoTotal= (tiempoFinal.tv_sec - tiempoInicial.tv_sec)*1000 + (tiempoFinal.tv_usec - tiempoInicial.tv_usec)/1000.0;
	tiempoTotal= tiempoTotal/1000;
	printf("Timeprog ---> El tiempo en segundos es: %f\n",tiempoTotal);
	
	return 0;
}