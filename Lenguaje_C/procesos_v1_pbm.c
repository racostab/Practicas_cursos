/*
   Description
      C Program with problems creating process
   Compilar
      $ gcc -o procesos_v1_pbm procesos_v1_pbm.c
   Solution
      $ procesos_v1_pbm | wc -l
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
	pid_t pid;

    //
	  fork();
      fork();
      fork();
	  printf("How many times is this printed?\n");
    //

	/*
	for(int i=0; i<3; i++){
		pid = fork();
		if( pid == -1){
			perror("fork");
		    exit(1);
		}
	    printf("How many times is this printed?\n");
	    //printf("How many times is this printed?  PID: %d\n", getpid());
	}
	*/
	return 0;
}
