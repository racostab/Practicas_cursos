/*
   Description
      C Program for Shared Memory (Writer Process) 
   Compile
      $ gcc -o shmem_write_v2 shmem_write_v2.c
*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h> 
#include <sys/shm.h> 

int main (int argc, char **argv)
{
  int *vector, shmid, valor;
  key_t llave;

     if( argc < 2){
        printf("Sintaxis: shmem_write_v2 valor \n");
        return 0;
     }
     valor = atoi(argv[1]);
     //printf("Valor: %d \n", valor);
     //return 0;

     llave = ftok("shared", 2019);
     shmid = shmget(llave, 25*sizeof(int), IPC_CREAT | 0777);
     vector = (int *) shmat(shmid, (void *)0, 0);
     
     //vector[10]=1234567890;
     vector[10]=valor;
     printf("    array[10]: %d \n", vector[10]);
     
     shmdt(vector);
}


