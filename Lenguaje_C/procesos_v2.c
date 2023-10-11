/*  
   Description
      Process using functions.
   Compile
      $ gcc -o procesos_v2 procesos_v2.c
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
void hijo();

int main()
{
	pid_t pid = fork();

	switch(pid){
	  case -1: // ERROR
		       perror("fork");
		       exit(1);
	  case 0: // HIJO
	           hijo();
		       exit(1);
	  default: // PADRE
		       printf("Father PID: %d\n", getpid() );
	}
	return 0;
}

void hijo()
{
	printf("Child PID:  %d\n", getpid() );
}