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

int mode_isReg(struct stat info);
 
int main(int ac, char *av[])
{
  int buff = atoi(av[1]);

  fprintf(stderr, "Buffer: %i\nArchivo Origen: %s\nArchivo destino: %s\n",buff,av[2],av[3]);
/* Verificacion de buffer*/
  if (buff>0 && buff<=16384){
/* Verificacion de argumentos */
  if(ac != 4)
  {
    fprintf(stderr, "usage: %s source destination\n", *av);
    exit(1);
  } 
 
   char *src = av[2];
   char *dest = av[3]; 
 
   if( src[0] != '/' && dest[0] != '/' )//ucp buffer file1.txt file2.txt
   {
       copyFiles(buff ,src ,dest );
   }
   else if( src[0] != '/' && dest[0] == '/' )//ucp buffer file1.txt /dir 
   {
      int i;
      for(i=1; i<=strlen(dest); i++)
      {
          dest[(i-1)] = dest[i];
      }
      strcat(dest, "/");
      strcat(dest, src);
      copyFiles(buff,src, dest);
  }
  else
  {
      fprintf(stderr, "Modo de uso: ucp Buffer source destination\n");
      exit(1);
  }
  }else {
    fprintf(stderr,"El tamano del buffer : es %i  pero este debe estar entre 1 y 16384",buff);
    exit(1);
  }  
}

 
int copyFiles(int BUFFERSIZE,char *source, char *destination)
{
  int in_fd, out_fd, n_chars;
  char buf[BUFFERSIZE];
 
  /* open files */
  if( (in_fd=open(source, O_RDONLY)) == -1 )
  {
    error("No se puede abrir ", source);
  }
  if( (out_fd=creat(destination, COPYMORE)) == -1 )
  {
    error("No se puede leer ", destination);
  }
  /* copy files */
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
    /* close files */
    if( close(in_fd) == -1 || close(out_fd) == -1 )
    {
      error("Error al cerrar archivo", "");
    }
    return 1;
}
 
void error(char *s1, char *s2)
{
    fprintf(stderr, "Error: %s ", s1);
    perror(s2);
    exit(1);
}
