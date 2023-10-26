/*
   Description
      C Program for Shared Memory (Writer Process) 
   Compile
      $ gcc -o shmem_write_v1 shmem_write_v1.c
*/
#include <sys/ipc.h> 
#include <sys/shm.h> 
#include <stdio.h>

int main (void)
{
  int *vector, shmid;
  key_t llave;

     printf("1. Create key\n");
     llave = ftok("shared", 2019);
     
     printf("2. Create memory zone\n");
     // Arreglo de 25 enteros
     shmid = shmget(llave, 25*sizeof(int), IPC_CREAT | 0777);
     
     printf("3. Attach memory to user space\n");
     vector = (int *) shmat(shmid, (void *)0, 0);
     
     // 4. Utilización
     printf("4. Use the memory: write data\n");
     vector[10]=1234567890;
     printf("    array[10]: %d \n", vector[10]);
     
     // 5. Desligar
     printf("5. Deatach memory\n");
     shmdt(vector);
     
}


