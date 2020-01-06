#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h> 

#define COPYMORE 0644 
 
 
void error(char *, char *);
int copyFiles(int buff,char *src, char *dest);

/*inicio de funcion principal, tiene 2 argumentos:
  ac = numero de argumentos que se pasaron en consola
  av = arreglo de los argumentos que se pasaron en consola */
int main(int ac, char *av[])
{
    int buff = atoi(av[1]); //Se transforma el string de buffer a un entero y se almacena en la variable buff

    //Se imprime en pantalla los datos recibidos por la consola
    fprintf(stderr, "Buffer: %i\nArchivo Origen: %s\nArchivo destino: %s\n",buff,av[2],av[3]);
    /* Verificacion de buffer */
    if (buff>0 && buff<=16384){
        /* Verificacion de argumentos */
        if(ac != 4)
        {
            fprintf(stderr, "usage: %s source destination\n", *av);
            exit(1);
        } 
 
        char *src = av[2]; //Se almacena la ruta del archivo origen
        char *dest = av[3]; //Se almacena la ruta del archivo destino
 
        if( src[0] != '/' && dest[0] != '/' )//ucp buffer file1.txt file2.txt
        {
            copyFiles(buff ,src ,dest ); //Se llama a la funcion copyFiles con los parametros pasados por consola
        }
        else if( src[0] != '/' && dest[0] == '/' )//ucp buffer file1.txt /dir 
        {
            /* Se realizan los cambios necesarios en la ruta del archivo destino 
            "se elimina el / inicial y se coloca un / al final, luego se concatena el nombre
            del archivo origen"
            */
            int i; 
            for(i=1; i<=strlen(dest); i++)
            {
                dest[(i-1)] = dest[i];
            }
            strcat(dest, "/");
            strcat(dest, src);
            copyFiles(buff,src, dest); //Se llama a la funcion copyFiles con el buffer y las rutas a utilizar
        }
        else //Si hay un error en el archivo origen
        {
            fprintf(stderr, "Modo de uso: ucp Buffer source destination\n");
            exit(1);
        }
    }
    else //Si hay un error en el tamaño del buffer
    {
        fprintf(stderr,"El tamano del buffer : es %i  pero este debe estar entre 1 y 16384",buff);
        exit(1);
    }  
}

/* Funcion que realiza la copia de los archivos y
recibe como parametros el tamaño del buffer y 
las rutas de origen y destino utilizadas */
int copyFiles(int BUFFERSIZE,char *source, char *destination)
{
    int in_fd, out_fd, n_chars; //Declaracion de los file
    /* Declaracion de arreglo a ser utilizado como buffer con el tamaño 
    especificado por el parametro BUFFERSIZE */
    char buf[BUFFERSIZE]; 
 
    /* Se realiza la apertura de los archivos, si se da un error se
    imprime por pantalla */
    if( (in_fd=open(source, O_RDONLY)) == -1 )
    {
        error("No se puede abrir ", source);
    }
    if( (out_fd=creat(destination, COPYMORE)) == -1 )
    {
        error("No se puede leer ", destination);
    }
    /* Se realiza la copia de los archivos */
    while( (n_chars = read(in_fd, buf, BUFFERSIZE)) > 0 )
    {
        if( write(out_fd, buf, n_chars) != n_chars )
        {
            error("Error de escritura en: ", destination);
        }
        if( n_chars == -1 )
        {
            error("Error de lectura de: ", source);
        }
    } 
    /* Se cierran los archivos al terminar de realizar la copia, si se da un error
    se imprime por pantalla */
    if( close(in_fd) == -1 || close(out_fd) == -1 )
    {
      error("Error al cerrar archivo", "");
    }

    return 1;
}
// Fin de funcion para la copia de archivos
 
/* Funcion que imprime por pantalla los errores que han sucedido durante la ejecucion
del programa UCP */
void error(char *s1, char *s2)
{
    fprintf(stderr, "Error: %s ", s1);
    perror(s2);
    exit(1);
}
