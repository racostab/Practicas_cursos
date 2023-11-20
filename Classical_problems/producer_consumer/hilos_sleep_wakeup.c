/*
   Description
      .
   Compile
      $ gcc -w -pthread -o hilos_productor_consumidor_v1 hilos_productor_consumidor_v1.c

      int itemCount=0;

      procedure producer(){
        while (true){
          item = produceItem();
      
          if(itemCount == BUFFER_SIZE){
             sleep();
          }
          
          putItemIntoBuffer(item);
          itemCount= itemCount + 1;
      
          if(itemCount == 1){
             wakeup(consumer);
          }
        }
      }

      procedure consumer(){
        while (true){
      
          if(itemCount == 0){
             sleep();
          }
          
          item= removeItemFromBuffer();
          itemCount= itemCount - 1;
      
          if(itemCount == BUFFER_SIZE - 1){
             wakeup(producer);
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
int itemCount=0;

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

void *productor (void *ptr)
{
  char *productor;

    productor = (char *) ptr;
    initializeQueue(&myQueue);
    while(1){
        if(itemCount == MAX_ITEMS ){
           sleep(1);
           continue;
        }

    putItem(&myQueue,itemCount);
    itemCount= itemCount + 1;
    printQueueProducer(&myQueue);

    // if (isEmpty(&myQueue) == 0){
    // }
    }
}

void *consumidor (void *ptr)
{
  char *consumidor;

    consumidor = (char *) ptr;
    while(1){
       if(itemCount == 0){
          ;
          // sleep(1);
          continue;
       }

       // item= removeItemFromBuffer();
       printQueueConsumer(&myQueue);
       getItem(&myQueue,&itemCount);
       itemCount= itemCount - 1;
       printQueueConsumer(&myQueue);

       //if(itemCount == MAX_ITEMS - 1){
       //}
    }
}

//--------------------------------
//Functions of the Queue
//--------------------------------

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
    if(theQueue->validItems>=MAX_ITEMS)
    {
        printf("The queue is full\n");
        printf("You cannot add items\n");
        return(-1);
    }
    else
    {
        theQueue->validItems++;
        theQueue->data[theQueue->last] = theItemValue;
        theQueue->last = (theQueue->last+1)%MAX_ITEMS;
    }
}


int getItem(circularQueue_t *theQueue, int *theItemValue)
{
    if(isEmpty(theQueue))
    {
        printf("isempty\n");
        return(-1);
    }
    else
    {
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
    while(aux1>0)
    {
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
    while(aux1>0){
        printf("\tConsumer #%d = %d\n", aux, theQueue->data[aux]);
        aux=(aux+1)%MAX_ITEMS;
        aux1--;
    }
    return;
}
