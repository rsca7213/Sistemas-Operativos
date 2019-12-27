#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <sys/wait.h>

int flag;
int cont1=0;

void recibirAlarma();

int main () {
    int C1,C2;
    int pipeP[2];
    printf("Proceso Padre, ID ---> %i \n",getpid());

    pipe(pipeP);

    C1 = fork();
    if(C1 < 0) exit(1);
    if(C1 == 0) {
        printf("Proceso Hijo C1, ID ---> %i, ID Padre ---> %i \n",getpid(),getppid());
    }
    if(C1 > 0) {
        C2 = fork();
        if(C2 < 0) exit(1);
        if(C2 == 0) {
            printf("Proceso Hijo C2, ID ---> %i, ID Padre ---> %i \n",getpid(),getppid());
        }
    }

    if(C1 == 0 && C2 != 0) {
        alarm(2);
        signal(SIGALRM,recibirAlarma);
        while(1) {
            sleep(1);
            if(flag) {
                printf("C1: Enviando Mensaje #%i a C2. \n",cont1);
                write(pipeP[1],"recibido", strlen("recibido"));
                flag=0;
            }
            else if(cont1 > 9 && flag == 0) {
                break;
            }
        }
    }

    if(C1 != 0 && C2 == 0) {
        int cont2 = 0;
        while (cont2 < 10) {
            char a[9]; 
            read(pipeP[0],a,9);
            printf("C2: He recibido el mensaje de C1: '%s', este es el #%i. \n",a,cont2+1);
            cont2++;
        }
    }

    if(C1 > 0 && C2 > 0) {
        wait(NULL);
    }

    return 0;
}

void recibirAlarma () {
    flag = 1;
    cont1++;
    if(cont1 < 10) alarm(2);
}