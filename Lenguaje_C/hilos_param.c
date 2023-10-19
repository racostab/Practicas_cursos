/*
   Description
      C Program to demonstrate the use of Threads and its parameters.
   Compile
      $ gcc -w -pthread -o hilos_param hilos_param.c
*/
#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

void *mensaje (void *ptr);

int main()
{
  pthread_t hilo1, hilo2;
  char *texto1 = "Hilo-1";
  char *texto2 = "Hilo-2";
  int iret1, iret2;

  	iret1 = pthread_create( &hilo1, NULL,mensaje, (void*) texto1);	
	if(iret1){
       printf("Error - pthread_create() codigo: %d\n",iret1);
       exit(EXIT_FAILURE);
	}

    iret2 = pthread_create(&hilo2, NULL, mensaje, (void*) texto2);
    if(iret2){
       printf("Error - pthread_create() codigo: %d\n",iret2);
       exit(EXIT_FAILURE);
	}

	printf("pthread_create() para hilo 1, return=%d\n",iret1);
    printf("pthread_create() para hilo 2, return=%d\n",iret2);

	pthread_join(hilo1, NULL);
    pthread_join(hilo2, NULL);
 
    exit(EXIT_SUCCESS);
}

void *mensaje (void *ptr)
{
     char 	*mensajes;
     mensajes 	= (char *) ptr;
     printf("%s \n", mensajes);
}
