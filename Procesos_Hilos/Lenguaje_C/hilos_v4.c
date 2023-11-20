/*
   Description
      C Program to demonstrate the use of Threads.
   Compile
      $ gcc -pthread -o hilos_v4 hilos_v4.c
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
   
   pid = getpid();
   
   // El padre espera al hilo hijo
   pthread_join(tid, NULL);
   printf("Tm=%d Th=%d \n", pid, (int)tid );

}

void thread(void)
{
   unsigned pid = getpid();
   unsigned tid = pthread_self();

	sleep(6);
   printf("\t\t\t Th=%d Thh=%d\n", pid, (int)tid);
}

