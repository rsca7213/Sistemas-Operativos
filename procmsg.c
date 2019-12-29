#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <sys/wait.h>

int flag; //Varbiable flag utilizada para el control del SIGALRM
int cont1=0; //contador de veces que se ha recibido el SIGALRM en el proceso hijo C1

void recibirAlarma();

// Inicio de programa
int main () {
    int C1,C2; //declaracion de ambos procesos hijos a crear
    int pipeP[2]; //declaracion del pipe para la comunicacion de los procesos
    printf("Proceso Padre, ID ---> %i \n",getpid()); //Se muestra en pantalla el proceso padre con su PID

    pipe(pipeP); //Se crea el pipe de los procesos utilizando la variable ya declarada

    C1 = fork(); //Se crea el primer proceso hijo C1
    if(C1 < 0) exit(1); //Si hay error al crear el proceso C1 se termina el programa
    if(C1 == 0) {
        //Si el proceso es el hijo (C1 == 0), se muestra en pantalla su PID y el PID del padre
        printf("Proceso Hijo C1, ID ---> %i, ID Padre ---> %i \n",getpid(),getppid());
    }
    if(C1 > 0) {
        //Si el proceso el el padre (C1 > 0), el padre creará otro proceso hijo, el cual será C2
        C2 = fork();
        if(C2 < 0) exit(1); //Si hay error al crear el proceso C1 se termina el programa
        if(C2 == 0) {
            //Si el proceso es el hijo (C2 == 0), se muestra en pantalla su PID y el PID del padre
            printf("Proceso Hijo C2, ID ---> %i, ID Padre ---> %i \n",getpid(),getppid());
        }
    }

    //Si el proceso es el hijo C1 y no el hijo C2
    if(C1 == 0 && C2 != 0) {
        /* Se configurará una alarma en 2 segundos que generará un SIGALRM,
        el cual al ser recibido por C1, ejecutara la función recibirAlarma() */
        alarm(2);
        signal(SIGALRM,recibirAlarma);
        while(1) {
            /* Ciclo que revisara cada segundo si se ha recibido una alarma,
            lo cual es notificado por el flag que cambia la función recibirAlarma() */
            sleep(1);
            if(flag) {
                //Si se recibio una alarma, se envia el mensaje a traves del pipe y se reinicia el flag
                printf("C1: Enviando Mensaje #%i a C2. \n",cont1);
                write(pipeP[1],"recibido", strlen("recibido"));
                flag=0;
            }
            else if(cont1 > 9 && flag == 0) {
                /* Cuando C1 haya enviado 10 mensajes se termina el ciclo y se cierra el proceso C1 */
                break;
            }
        }
    }

    //Si el proceso es el hijo C2 y no el hijo C1
    if(C1 != 0 && C2 == 0) {
        int cont2 = 0; //Se inicializa un contador para llevar la cuenta de cuantas veces C2 ha mostrado por pantalla el mensaje
        while (cont2 < 10) {
            /* Mientras que C2 no haya mostrado por pantalla el mensaje
            10 veces, se ejecutara el ciclo. Dentro de este ciclo, se leera del pipe
            de los procesos y cada vez que se reciba el mensaje de C1, C2 lo
            notificara por pantalla y incrementara su contador de control 1 unidad. */
            char a[9]; 
            read(pipeP[0],a,9);
            printf("C2: He recibido el mensaje de C1: '%s', este es el #%i. \n",a,cont2+1);
            cont2++;
        }
        // Cuando el ciclo termine, el proceso C2 terminara
    }

    //Si el proceso es el PADRE de C1 Y C2
    if(C1 > 0 && C2 > 0) {
        wait(NULL); //El proceso padre esperara hasta que sus dos hijos hayan terminado para terminar su ejecución.
    }

    return 0;
}

// Funcion que gestiona el SIGALRM para C1
void recibirAlarma () {
    /* Cuando la funcion se ejecuta, se señala que se ha recibido un SIGALRM en C1
    colocando flag en 1, al recibir la alarma se incrementa el contador de control de C1 y
    si no ha recibido ya 10 alarmas, se configura otra alarma dentro de 2 segundos. */
    flag = 1;
    cont1++;
    if(cont1 < 10) alarm(2);
}