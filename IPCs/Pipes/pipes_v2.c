/*
   Description
      Program that verifies the limit of a Pipe.
   Compile
      $ gcc -o pipes_v2 pipes_v2.c
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

//int main (int argc, char **argv)
int main()
{
 int error, fd[2], pid, tam=5, bytes=0;
 //char *buf="abcde";
 char *buf;

   error = pipe(fd);
   if( error < 0 ){
     printf("Error en la creacion del pipe\n");
     return 1;
   }
   //buf = malloc(50 * sizeof(char));
   buf = calloc(50, sizeof(char));

   pid = fork();
   switch(pid){
      case -1: // Error
                  printf("Error de creacion");
                  exit(1);
      case 0: // Hijo
                  //bytes = read(fd[0], buf, tam);
                  bytes = read(fd[0], buf, 50);
                  printf("H= %s %d\n", buf, bytes);
                  break;
      default:
                  strcpy(buf, "abcde");
                  sleep(4);
                  write(fd[1], buf, tam);
                  printf("P= %s \n", buf);
                  break;
   }
   
}
