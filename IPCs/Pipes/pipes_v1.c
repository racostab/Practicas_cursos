/*
   Description
      Program that verifies the limit of a Pipe.
   Compile
      $ gcc -o pipes_v1 pipes_v1.c
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

//int main (int argc, char **argv)
int main()
{
 int i, error, fd[2];
 char *buf="a";

   error = pipe(fd);
   if( error < 0 ){
     printf("Error en la creacion del pipe\n");
     return 1;
   }

   for(i=1; ;i++){
      write(fd[1], buf, 1);
      printf("%d ", i);
      fflush(stdout); 
   }
   
}
