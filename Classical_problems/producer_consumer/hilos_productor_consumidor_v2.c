/*
     /*
   Description
      .
   Compile
      $ gcc -w -pthread -o hilos_productor_consumidor_v2 hilos_productor_consumidor_v2.c

     productor()
     {
       while (1){
         if ( buffer_lleno() )
             esperar();
         else {
           aumenta_contador();
           produce_datos();
         }
       }
     }
     
     consumidor()
     {
       while (1){
         if ( buffer_vacio() )
             esperar();
         else {
           leer_datos();
           disminuir_contador();
         }
       }
     }
*/
#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#define MAX_ITEMS    30

void *mensaje (void *ptr);
void *productor (void *ptr);
void *consumidor (void *ptr);
int i,k;
int readValue;

//Struct of the Queue
typedef struct circularQueue_s
{
    int     first;
    int     last;
    int     validItems;
    int     data[MAX_ITEMS];
} circularQueue_t;
  circularQueue_t myQueue;

void initializeQueue(circularQueue_t *theQueue);
int isEmpty(circularQueue_t *theQueue);
int isFull(circularQueue_t *theQueue);
int putItem(circularQueue_t *theQueue, int theItemValue);
int getItem(circularQueue_t *theQueue, int *theItemValue);
void printQueueProducer(circularQueue_t *theQueue);
void printQueueConsumer(circularQueue_t *theQueue);

int main ()
{
	pthread_t	 thread1, thread2;
	char *texto1 	= "thread_one";
	char *texto2 	= "thread_two";
 	int 		iret1, iret2;     
         
  	iret1 = pthread_create( &thread1, NULL, productor, (void*) texto1);	
	if(iret1){
        	printf("Error - pthread_create() codigo: %d\n",iret1);
         	exit(EXIT_FAILURE);
	}

    iret2 = pthread_create(&thread2, NULL, consumidor, (void*) texto2);
    if(iret2){
         	printf("Error - pthread_create() codigo: %d\n",iret2);
         	exit(EXIT_FAILURE);
	}

	printf("pthread_create() thread one, return=  %d the main thread ID is: %d thread ID %d \n",iret1,pthread_self(),thread1);
  printf("pthread_create() thread two, return=  %d the main thread ID is: %d thread ID %d \n",iret2,pthread_self(),thread2);

	pthread_join( thread1, NULL);
  pthread_join( thread2, NULL);
  exit(EXIT_SUCCESS);
}

void *productor(void *ptr)
{
  char *productor;

    productor = (char *) ptr;
    while(1){
       if(isFull(&myQueue) == 1){
         ;
       }else{
         initializeQueue(&myQueue);
         for (i=0;i<MAX_ITEMS+1;i++){
              putItem(&myQueue,i);
         }
         printQueueProducer(&myQueue);
      }
    }
}

void *consumidor(void *ptr)
{
  char *consumidor;

    consumidor = (char *) ptr;
    while(1){
       if (isEmpty(&myQueue) == 1){
          ;
       }else{
          for (i=0;i<MAX_ITEMS/2;i++){
              getItem(&myQueue,&readValue);
//	      printf("\tConsumer =%d\n",readValue);
//              printQueueConsumer(&myQueue);
          }
          printQueueConsumer(&myQueue);
       }
    }
}

//Functions of the Queue
void initializeQueue(circularQueue_t *theQueue)
{
   int i;

    theQueue->validItems  =  0;
    theQueue->first       =  0;
    theQueue->last        =  0;
    for(i=0; i<MAX_ITEMS; i++){
        theQueue->data[i] = 0;
    }        
    return;
}

int isEmpty(circularQueue_t *theQueue)
{
    if(theQueue->validItems==0)
        return(1);
    else
        return(0);
}

int isFull(circularQueue_t *theQueue)
{
    if(theQueue->validItems>=MAX_ITEMS)
        return(1);
    else
        return(0);
}

int putItem(circularQueue_t *theQueue, int theItemValue)
{
    if(theQueue->validItems>=MAX_ITEMS){
        printf("The queue is full\n");
        printf("You cannot add items\n");
        return(-1);
    }else{
        theQueue->validItems++;
        theQueue->data[theQueue->last] = theItemValue;
        theQueue->last = (theQueue->last+1)%MAX_ITEMS;
    }
}


int getItem(circularQueue_t *theQueue, int *theItemValue)
{
    if(isEmpty(theQueue)){
        printf("isempty\n");
        return(-1);
    }else{
        *theItemValue=theQueue->data[theQueue->first];
        theQueue->first=(theQueue->first+1)%MAX_ITEMS;
        theQueue->validItems--;
        return(0);
    }
}
	
void printQueueProducer(circularQueue_t *theQueue)
{
  int aux, aux1;

    aux  = theQueue->first;
    aux1 = theQueue->validItems;
    while( aux1>0 ){
        printf("Producer #%d = %d\n", aux, theQueue->data[aux]);
        aux=(aux+1)%MAX_ITEMS;
        aux1--;
    }
    return;
}

void printQueueConsumer(circularQueue_t *theQueue)
{
    int aux, aux1;
    aux  = theQueue->first;
    aux1 = theQueue->validItems;
    while( aux1>0 ){
        printf("\tConsumer #%d = %d\n", aux, theQueue->data[aux]);
        aux=(aux+1)%MAX_ITEMS;
        aux1--;
    }
    return;
}

/*
productor()
{
  while (1){
    if ( buffer_lleno() )
        esperar();
    else {
      aumenta_contador();
      produce_datos();
    }
  }
}

consumidor()
{
  while (1){
    if ( buffer_vacio() )
        esperar();
    else {
      leer_datos();
      disminuir_contador();
    }
  }
}


*/
