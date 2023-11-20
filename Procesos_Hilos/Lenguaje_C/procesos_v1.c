/*
   Description
      C Program to demonstrate the use of Fork.
	  syscalls: fork
   Compile
      $ gcc -o procesos_v1 procesos_v1.c
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
	pid_t pid = fork();

	switch(pid){
	  case -1: // ERROR
		       perror("fork");
		       exit(1);
	  case 0: // HIJO
	           printf("Child  PID: %d and Father PID: %d\n", getpid(), getppid() );
			   break;
	  default: // PADRE
		       printf("Father PID: %d\n", getpid() );
	}
	return 0;
}
