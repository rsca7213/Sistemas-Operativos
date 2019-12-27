#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[]){
	
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
	clock_t begin= clock();

	/*se ejecuta el nuevo programa con sus respectivos argumentos
	usando el string que contiene dicho programa con sus argumentos*/
	system(progYargs);
	
	//se finaliza el cronometro
	clock_t end=clock();


	/*Se calcula e imprime el tiempo que tardo el programa en ejecutarse*/
	double time= (double)(end-begin)/CLOCKS_PER_SEC;
	printf("Timeprog ---> El tiempo en segundos es: %f\n",time);
	
	return 0;
}