/*
   Description
      Process testing sleep and wait.
   Compile
      $ gcc -o procesos_v4 procesos_v4.c
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
 #include <sys/wait.h>

void hijo();

int main()
{
  pid_t pid;
  int status;

     pid = fork();
	 switch(pid){
	   case -1: // ERROR
	 	       perror("fork");
	 	       exit(1);
	   case 0: // HIJO
	 	       //printf("Child PID: %d\n", getpid() );
	           hijo();
	 	       exit(1);
	   default: // PADRE
			   waitpid(pid, &status, 0);
	 	       printf("Father PID: %d\n", getpid() );
	 }
  return 0;
}

void hijo()
{
	sleep(3);
	printf("Child  PID: %d\n", getpid() );
}
