/*
   Description
      C Program to demonstrate the use of Threads.
   Compile
      $ gcc -w -pthread -o hilos_v1 hilos_v1.c
*/
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>

void thread(void);

int main (int argc, char **argv)
{
 pthread_t tid;
 int status, pid;

   status = pthread_create(&tid, NULL, (void *)&thread, NULL);
   if( status < 0 ){
     printf("Error en la creacion del Thread\n");
     return 1;
   }
   
   usleep(1);
   pid = getpid();
   while(1){
     printf("Tm=%d Th=%d \n", pid, (int)tid );
	 sleep(5);
   }
   // usleep (1000000);

}

void thread(void)
{
   unsigned pid = getpid();

   // Specific for Linux
   // pid_t tid = gettid();
   // POSIX
   unsigned tid = pthread_self();

   while(1){
	  sleep(5);
     printf("\t\t\t Th=%d Thh=%d\n", pid, (int)tid);
   }
   // pthread_exit(NULL);
}

