/*
   Description
      Process with wait syscall.
	  A call to wait() blocks the calling process until one of its child processes exits or 
	  a signal is received. After child process terminates, parent continues its execution 
	  after wait system call instruction. 
   Compile
      $ gcc -o procesos_v5_wait procesos_v5_wait.c
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
 #include <sys/wait.h>

#define NUMPROC 5

int main(void)
{
  pid_t child[NUMPROC];
  int status[NUMPROC];
  int i;

    printf("Parent= %d\n", getpid());
    for(i=0;i<NUMPROC;++i) {
      if(fork() == 0) {
        sleep(i);
        printf("i=%d, %d\n",i, getpid());
        _exit(0);
      }
    }

    for(i=0;i<NUMPROC;++i)
      child[i] = wait(&status[i]);

    for(i=0;i<NUMPROC;++i)
      printf("Exit= %d, child= %d\n", WEXITSTATUS(status[i]), child[i]);
}
