/*
   Description
      Program that verifies the limit of a Pipe.
   Compile
      $ gcc -o pipes_v2 pipes_v2.c
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

//int main (int argc, char **argv)
int main()
{
 int error, fd[2], pid, tam=5;
 char *buf="abcde";

   error = pipe(fd);
   if( error < 0 ){
     printf("Error en la creacion del pipe\n");
     return 1;
   }

   pid = fork();
   switch(pid){
      case -1: // Error
                  printf("Error de creacion");
                  exit(1);
      case 0: // Hijo
                  read(fd[0], buf, tam);
                  printf("H= %s \n", buf);
                  break;
      default:
                  sleep(4);
                  write(fd[1], buf, tam);
                  printf("P= %s \n", buf);
                  break;
   }
   
}
