/*
   Description
      C Program to demonstrate the use of Threads.
   Compile
      $ gcc -pthread -o hilos_v2 hilos_v2.c
*/

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>

void thread(void);

int main (int argc, char **argv)
{
 pthread_t tid1, tid2;
 int status;
 char *texto1 	= "hilo UNO";
 char *texto2 	= "hilo DOS";

   status = pthread_create(&tid1, NULL, (void *)&thread, NULL);
   if( status < 0 ){
     printf("Error en la creacion del Thread 1\n");
     return 1;
   }

   status = pthread_create(&tid2, NULL, (void *)&thread, NULL);
   if( status < 0 ){
     printf("Error en la creacion del Thread 2\n");
     return 1;
   }

   // El padre espera a los 2 hijos
   pthread_join(tid1, NULL);
   pthread_join(tid2, NULL);

	unsigned pid = getpid();
   unsigned tidp = pthread_self();
   printf("Tm=%d Th=%d \n", pid, (int)tidp );
}

void thread(void)
{
   unsigned pid = getpid();
   unsigned tid = pthread_self();

	sleep(5);
   printf("\t\t\t Th=%d Thh=%d\n", pid, (int)tid);
}

