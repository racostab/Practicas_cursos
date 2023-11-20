/*
   Description
      .
      Suspende al proceso:
          Linux: 19 SIGSTOP
          MaxOSX: kill -STOP pid   o -17
      Continua el proceso  18 SIGCONT
          Linux: 18 SIGCONT
          MaxOSX: kill -CONT pid o -19
   Compile
      $ gcc -o signals_v2 signals_v2.c
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void hijo(void);

int main()
{
  pid_t pid;
  int nh;

     pid = fork();
	 switch(pid){
	   case -1: // ERROR
	 	       perror("fork");
	 	       exit(1);
	   case 0: // HIJO
	           hijo();
	 	       exit(1);
	   default: // PADRE
			   sleep(6);
			   if(1){
                  kill(pid, SIGSTOP);
                  sleep(6);
                  kill(pid, SIGCONT);
			   }
	 }
  return 0;
}

void hijo(void)
{
    while(1){
	   printf("%d\n", getpid() );
	   sleep(2);
	}
}
